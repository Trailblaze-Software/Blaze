

# File point\_octree.cpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**point\_octree.cpp**](point__octree_8cpp.md)

[Go to the documentation of this file](point__octree_8cpp.md)


```C++
#include "gui/point_octree.hpp"

#include <omp.h>

#include <chrono>
#include <thread>

namespace {

struct BuildJob {
  PointOctreeNode* node = nullptr;
  size_t begin = 0;
  size_t end = 0;
};

constexpr size_t PARALLEL_BUILD_MIN_POINTS = 64'000;

void partition_range(PointOctreeNode& node, std::vector<OctreePoint>& points, size_t begin,
                     size_t end, std::array<size_t, 9>& child_ends) {
  // Count buckets.
  std::array<size_t, 8> bucket_counts{};
  for (size_t i = begin; i < end; ++i) {
    ++bucket_counts[static_cast<size_t>(node.child_index(points[i]))];
  }
  // Compute bucket boundaries.
  child_ends[0] = begin;
  for (int i = 0; i < 8; ++i) {
    child_ends[static_cast<size_t>(i + 1)] =
        child_ends[static_cast<size_t>(i)] + bucket_counts[static_cast<size_t>(i)];
  }
  // In-place 8-way partition: walk each bucket's final range and swap
  // misplaced elements into their correct buckets. Each swap fixes one
  // element, so at most N swaps total. No temp buffer needed.
  std::array<size_t, 8> write_pos = {child_ends[0], child_ends[1], child_ends[2], child_ends[3],
                                     child_ends[4], child_ends[5], child_ends[6], child_ends[7]};
  for (int b = 0; b < 8; ++b) {
    for (size_t i = write_pos[static_cast<size_t>(b)]; i < child_ends[static_cast<size_t>(b + 1)];
         ++i) {
      int c;
      while ((c = node.child_index(points[i])) != b) {
        std::swap(points[i], points[write_pos[static_cast<size_t>(c)]]);
        ++write_pos[static_cast<size_t>(c)];
      }
    }
  }
}

void split_subtree_job(PointOctreeNode& node, size_t begin, size_t end,
                       std::vector<OctreePoint>& points, std::vector<BuildJob>& out_jobs) {
  // Shuffle is deferred to shuffle_leaves() after build — per-level shuffles
  // are redundant since children will be shuffled again at lower levels.
  node.begin_index = 0;
  node.end_index = 0;

  std::array<size_t, 9> child_ends{};
  partition_range(node, points, begin, end, child_ends);

  for (int i = 0; i < 8; ++i) {
    const size_t child_begin = child_ends[static_cast<size_t>(i)];
    const size_t child_end = child_ends[static_cast<size_t>(i + 1)];
    if (child_begin == child_end) {
      continue;
    }
    node.ensure_child(i);
    out_jobs.push_back({node.children[static_cast<size_t>(i)].get(), child_begin, child_end});
  }
}

void build_subtree_sequential(PointOctreeNode& node, size_t begin, size_t end,
                              std::vector<OctreePoint>& points, std::atomic<size_t>& processed,
                              const std::atomic<bool>* cancel) {
  if (end <= begin || (cancel && cancel->load(std::memory_order_relaxed))) {
    return;
  }

  const size_t count = end - begin;
  if (count <= PointOctreeNode::MAX_POINTS || node.depth >= PointOctreeNode::MAX_DEPTH) {
    node.begin_index = begin;
    node.end_index = end;
    processed.fetch_add(count, std::memory_order_relaxed);
    return;
  }

  std::vector<BuildJob> child_jobs;
  child_jobs.reserve(8);
  split_subtree_job(node, begin, end, points, child_jobs);
  for (auto& child_job : child_jobs) {
    build_subtree_sequential(*child_job.node, child_job.begin, child_job.end, points, processed,
                             cancel);
  }
}

}  // namespace

void PointOctree::insert_batch(std::vector<OctreePoint>&& points,
                               const std::function<void(size_t, size_t)>& progress,
                               const std::atomic<bool>* cancel) {
  m_points = std::move(points);
  m_total_points = m_points.size();
  if (m_points.empty() || !m_root) {
    return;
  }

  std::atomic<size_t> processed{0};
  const size_t total = m_total_points;

  // Expand the root into roughly target_jobs independent subtrees so the build
  // below parallelises well. This phase is fast; only the build phase reports
  // progress (via the poll thread driven by the processed atomic).
  std::vector<BuildJob> jobs;
  jobs.reserve(256);
  jobs.push_back({m_root.get(), 0, m_total_points});

  const size_t target_jobs = static_cast<size_t>(std::max(1, omp_get_max_threads())) * 4;
  size_t expand_idx = 0;
  while (expand_idx < jobs.size() && jobs.size() < target_jobs) {
    if (cancel && cancel->load(std::memory_order_relaxed)) {
      return;
    }
    BuildJob& job = jobs[expand_idx];
    if (job.end <= job.begin || job.end - job.begin <= PARALLEL_BUILD_MIN_POINTS ||
        job.node->depth >= PointOctreeNode::MAX_DEPTH ||
        job.end - job.begin <= PointOctreeNode::MAX_POINTS) {
      ++expand_idx;
      continue;
    }
    BuildJob split_job = job;
    jobs[expand_idx] = std::move(jobs.back());
    jobs.pop_back();
    split_subtree_job(*split_job.node, split_job.begin, split_job.end, m_points, jobs);
  }

  std::atomic<bool> build_done{false};
  std::thread progress_thread;
  if (progress) {
    progress_thread = std::thread([&]() {
      while (!build_done.load(std::memory_order_acquire)) {
        progress(processed.load(std::memory_order_relaxed), total);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
    });
  }

#pragma omp parallel for schedule(dynamic)
  for (ptrdiff_t job_idx = 0; job_idx < static_cast<ptrdiff_t>(jobs.size()); ++job_idx) {
    BuildJob job = jobs[static_cast<size_t>(job_idx)];
    if (job.end <= job.begin) {
      continue;
    }
    build_subtree_sequential(*job.node, job.begin, job.end, m_points, processed, cancel);
  }

  build_done.store(true, std::memory_order_release);
  if (progress_thread.joinable()) {
    progress_thread.join();
  }
  if (progress && !(cancel && cancel->load(std::memory_order_relaxed))) {
    progress(total, total);
  }
}
```


