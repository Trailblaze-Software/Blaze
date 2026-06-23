#include <QApplication>
#include <QMainWindow>
#include <QMatrix4x4>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <thread>

#include "gl_widget.hpp"
#include "main_3d_window.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/resources.hpp"

#ifndef USE_PDAL
#include "gui/frustum.hpp"
#include "gui/octree_las_data.hpp"
#include "gui/point_octree.hpp"
#include "las/las_file.hpp"
#include "las_reader.hpp"
#endif

#ifdef _WIN32
#include <windows.h>
#endif

struct LaunchOptions {
  std::optional<fs::path> import_path;
  std::optional<fs::path> las_path;
  bool exit_after_load = false;
  bool exit_after_render = false;
  bool bench_mode = false;
  bool probe_las = false;
};

static void print_usage(const char* program) {
  std::cerr
      << "Usage: " << program << " [options] [las_file]\n"
      << "\n"
      << "Options:\n"
      << "  --import-blaze-output <dir>  Import blaze outputs from directory on startup\n"
      << "  --exit-after-load            Exit once all layers finish loading (for automation)\n"
      << "  --exit-after-render          Exit after first full render (for automation)\n"
      << "  --bench                      Load, render 60 frames headless, print stats, exit\n"
      << "  --probe-las <file>           Load first LAS batch and print diagnostics (no GUI)\n"
      << "  --help                       Show this help\n"
      << "\n"
      << "Environment:\n"
      << "  BLAZE3D_IMPORT_OUTPUT        Same as --import-blaze-output\n"
      << "\n"
      << "Examples:\n"
      << "  " << program << " sample.laz\n"
      << "  " << program << " --import-blaze-output assets/out/combined --exit-after-load\n";
}

static LaunchOptions parse_args(int argc, char* argv[]) {
  LaunchOptions opts;

  if (const char* env = std::getenv("BLAZE3D_IMPORT_OUTPUT")) {
    if (env[0] != '\0') {
      opts.import_path = env;
    }
  }

  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    if (arg == "--help" || arg == "-h") {
      print_usage(argv[0]);
      std::exit(0);
    }
    if (arg == "--exit-after-load") {
      opts.exit_after_load = true;
    } else if (arg == "--exit-after-render") {
      opts.exit_after_render = true;
    } else if (arg == "--bench") {
      opts.exit_after_load = true;
      opts.bench_mode = true;
    } else if (arg == "--probe-las") {
      if (i + 1 >= argc) {
        std::cerr << "Missing path after --probe-las\n";
        print_usage(argv[0]);
        std::exit(1);
      }
      opts.probe_las = true;
      opts.las_path = argv[++i];
    } else if (arg == "--import-blaze-output") {
      if (i + 1 >= argc) {
        std::cerr << "Missing path after --import-blaze-output\n";
        print_usage(argv[0]);
        std::exit(1);
      }
      opts.import_path = argv[++i];
    } else if (!arg.empty() && arg[0] == '-') {
      std::cerr << "Unknown option: " << arg << "\n";
      print_usage(argv[0]);
      std::exit(1);
    } else {
      opts.las_path = arg;
    }
  }

  return opts;
}

#ifndef USE_PDAL
static int probe_las_file(const fs::path& filename) {
  const fs::path log_path = filename.parent_path() / "blaze_probe.log";
  std::ofstream log(log_path, std::ios::trunc);
  auto log_line = [&](const std::string& line) {
    std::cout << line << '\n';
    if (log) {
      log << line << '\n';
    }
  };

  laspp::LASReader reader(filename);
  const auto& header = reader.header();
  const Extent3D bounds = as_extent3d(header.bounds());
  const auto& transform = header.transform();
  log_line("LAS probe: " + filename.string());
  log_line("  total_points: " + std::to_string(reader.num_points()));
  log_line("  chunks: " + std::to_string(reader.num_chunks()));
  log_line("  base_point_format: " + std::to_string(header.point_format() & 0x7Fu));
  log_line("  point_record_length: " + std::to_string(header.point_data_record_length()));
  log_line("  scale: (" + std::to_string(transform.scale_factors().x()) + ", " +
           std::to_string(transform.scale_factors().y()) + ", " +
           std::to_string(transform.scale_factors().z()) + ")");
  log_line("  offset: (" + std::to_string(transform.offsets().x()) + ", " +
           std::to_string(transform.offsets().y()) + ", " +
           std::to_string(transform.offsets().z()) + ")");
  log_line("  bounds: " + ([&] {
             std::ostringstream os;
             os << bounds;
             return os.str();
           })());

  if (reader.num_chunks() > 0) {
    const size_t first_chunk_points = reader.points_per_chunk()[0];
    std::vector<laspp::LASPointFormat7> first_chunk(first_chunk_points);
    reader.read_chunks_list(std::span<laspp::LASPointFormat7>(first_chunk), {0});
    int32_t raw_minx = std::numeric_limits<int32_t>::max();
    int32_t raw_maxx = std::numeric_limits<int32_t>::lowest();
    int32_t raw_miny = std::numeric_limits<int32_t>::max();
    int32_t raw_maxy = std::numeric_limits<int32_t>::lowest();
    double world_minx = std::numeric_limits<double>::max();
    double world_maxx = std::numeric_limits<double>::lowest();
    double world_miny = std::numeric_limits<double>::max();
    double world_maxy = std::numeric_limits<double>::lowest();
    const size_t sample_stride = std::max(size_t{1}, first_chunk.size() / 4096);
    for (size_t i = 0; i < first_chunk.size(); i += sample_stride) {
      const auto& pt = first_chunk[i];
      raw_minx = std::min(raw_minx, pt.x);
      raw_maxx = std::max(raw_maxx, pt.x);
      raw_miny = std::min(raw_miny, pt.y);
      raw_maxy = std::max(raw_maxy, pt.y);
      const auto coords = transform.transform_point(pt.x, pt.y, pt.z);
      world_minx = std::min(world_minx, coords.x());
      world_maxx = std::max(world_maxx, coords.x());
      world_miny = std::min(world_miny, coords.y());
      world_maxy = std::max(world_maxy, coords.y());
    }
    log_line("  first_chunk_points: " + std::to_string(first_chunk.size()));
    log_line("  raw_x: [" + std::to_string(raw_minx) + ", " + std::to_string(raw_maxx) + "]");
    log_line("  raw_y: [" + std::to_string(raw_miny) + ", " + std::to_string(raw_maxy) + "]");
    log_line("  world_x: [" + std::to_string(world_minx) + ", " + std::to_string(world_maxx) + "]");
    log_line("  world_y: [" + std::to_string(world_miny) + ", " + std::to_string(world_maxy) + "]");
  }

  size_t load_callbacks = 0;
  AsyncOctreeLASData data(filename, AsyncProgressTracker(), {[&] { ++load_callbacks; }});
  const auto deadline = std::chrono::steady_clock::now() + std::chrono::minutes(30);
  while (!data.load_complete() && std::chrono::steady_clock::now() < deadline) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  log_line("  points_loaded: " + std::to_string(data.points_loaded()));
  log_line("  load_complete: " + std::string(data.load_complete() ? "yes" : "no"));
  log_line("  load_callbacks: " + std::to_string(load_callbacks));

  if (!data.load_complete()) {
    log_line("LAS probe failed: load did not complete within timeout");
    return 1;
  }

  const Coordinate3D<double>& origin = data.coordinate_origin();
  log_line("  coordinate_origin: (" + std::to_string(origin.x()) + ", " +
           std::to_string(origin.y()) + ", " + std::to_string(origin.z()) + ")");

  std::vector<PointOctree::VisibleNode> visible_nodes;
  const auto snap = data.snapshot();
  if (!snap) {
    log_line("LAS probe failed: no snapshot published");
    return 1;
  }
  log_line("  octree_total_points: " + std::to_string(snap->octree.total_points()));
  log_line("  preview_points: " + std::to_string(snap->preview_points.size()));

  size_t nodes_with_points = 0;
  size_t max_node_points = 0;
  size_t points_in_nodes = 0;
  int max_node_depth = 0;
  const std::vector<OctreePoint>& all_points = snap->octree.points();
  std::function<void(const PointOctreeNode&)> walk = [&](const PointOctreeNode& node) {
    max_node_depth = std::max(max_node_depth, node.depth);
    const size_t count = node.point_count();
    if (count > 0) {
      nodes_with_points += 1;
      max_node_points = std::max(max_node_points, count);
      points_in_nodes += count;
    }
    for (const auto& child : node.children) {
      if (child) {
        walk(*child);
      }
    }
  };
  if (snap->octree.root()) {
    walk(*snap->octree.root());
  }
  log_line("  nodes_with_points: " + std::to_string(nodes_with_points));
  log_line("  max_node_points: " + std::to_string(max_node_points));
  log_line("  points_in_nodes: " + std::to_string(points_in_nodes));
  log_line("  max_node_depth: " + std::to_string(max_node_depth));

  float sample_minx = std::numeric_limits<float>::max();
  float sample_maxx = std::numeric_limits<float>::lowest();
  float sample_miny = std::numeric_limits<float>::max();
  float sample_maxy = std::numeric_limits<float>::lowest();
  const PointOctreeNode* mega_node = nullptr;
  std::function<void(const PointOctreeNode&)> find_mega = [&](const PointOctreeNode& node) {
    const size_t count = node.point_count();
    if (count > 0 && (!mega_node || count > mega_node->point_count())) {
      mega_node = &node;
    }
    for (const auto& child : node.children) {
      if (child) {
        find_mega(*child);
      }
    }
  };
  if (snap->octree.root()) {
    find_mega(*snap->octree.root());
  }
  if (mega_node != nullptr && mega_node->point_count() > 0) {
    const size_t mega_count = mega_node->point_count();
    for (size_t i = 0; i < mega_count; i += std::max(size_t{1}, mega_count / 4096)) {
      const OctreePoint& pt = all_points[mega_node->begin_index + i];
      sample_minx = std::min(sample_minx, pt.x);
      sample_maxx = std::max(sample_maxx, pt.x);
      sample_miny = std::min(sample_miny, pt.y);
      sample_maxy = std::max(sample_maxy, pt.y);
    }
    log_line("  mega_node_depth: " + std::to_string(mega_node->depth));
    log_line("  mega_node_bounds: " + ([&] {
               std::ostringstream os;
               os << mega_node->bounds;
               return os.str();
             })());
    log_line("  mega_sample_x: [" + std::to_string(sample_minx) + ", " +
             std::to_string(sample_maxx) + "]");
    log_line("  mega_sample_y: [" + std::to_string(sample_miny) + ", " +
             std::to_string(sample_maxy) + "]");
  }

  const Frustum frustum = Frustum::from_matrix(QMatrix4x4());
  const Coordinate3D<double> scene_offset = origin;
  const Coordinate3D<double> camera_local(0.0, 0.0, 5000.0);
  snap->octree.collect_visible(frustum, 800.0, 1.0, scene_offset, origin, camera_local,
                               visible_nodes);

  size_t drawable_points = 0;
  for (const auto& visible : visible_nodes) {
    if (!visible.node) {
      continue;
    }
    drawable_points += std::min(visible.node->point_count(), visible.chunk_size);
  }
  log_line("  visible_nodes: " + std::to_string(visible_nodes.size()));
  log_line("  approx_drawable_points: " + std::to_string(drawable_points));
  log_line("LAS probe OK");
  return 0;
}
#else
static int probe_las_file(const fs::path& filename) {
  std::cerr << "LAS probe requires las++ (BLAZE_USE_PDAL=OFF)\n";
  (void)filename;
  return 1;
}
#endif

int main(int argc, char* argv[]) {
#ifdef _WIN32
  bool owned_console = false;
  if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
    owned_console = AllocConsole() != FALSE;
  }
  if (GetConsoleWindow() != nullptr) {
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
  }
#endif

  QSurfaceFormat format;
  format.setVersion(3, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  const LaunchOptions opts = parse_args(argc, argv);

  if (opts.probe_las && opts.las_path) {
    return probe_las_file(*opts.las_path);
  }

  QApplication a(argc, argv);

#ifdef _WIN32
  if (owned_console) {
    QObject::connect(&a, &QApplication::aboutToQuit, [] { FreeConsole(); });
  }
#endif

  Main3DWindow window;
  window.set_exit_after_load(opts.exit_after_load);
  window.set_exit_after_render(opts.exit_after_render);
  window.set_bench_mode(opts.bench_mode);

  window.show();

  if (opts.las_path) {
    window.add_layer(std::make_unique<LASLayer>(*opts.las_path, window.add_progress_tracker(),
                                                window.scene_reference_crs()));
  } else if (!opts.import_path) {
    window.add_layer(std::make_unique<LASLayer>(AssetRetriever::get_asset("sample.laz"),
                                                window.add_progress_tracker(),
                                                window.scene_reference_crs()));
  }

  if (opts.import_path) {
    window.set_defer_render_until_loaded(true);
    window.import_blaze_output_from_path(opts.import_path->string());
  }

  return QApplication::exec();
}
