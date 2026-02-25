#include <gtest/gtest.h>

#include "config_input/config_input.hpp"

#ifdef _WIN32
#define ABS_CONFIG_DIR "C:/some/config/dir"
#define ABS_CONFIG_DIR2 "C:/config/dir"
#define ABS_OUTPUT "C:/absolute/output"
#define ABS_FILE1 "C:/absolute/file1.las"
#define ABS_FILE2 "C:/absolute/file2.laz"
#else
#define ABS_CONFIG_DIR "/some/config/dir"
#define ABS_CONFIG_DIR2 "/config/dir"
#define ABS_OUTPUT "/absolute/output"
#define ABS_FILE1 "/absolute/file1.las"
#define ABS_FILE2 "/absolute/file2.laz"
#endif

// =============================================================================
// Config output_path tests
// =============================================================================

TEST(ConfigPaths, OutputPathAbsolute) {
  Config config;
  config.relative_path_to_config = ABS_CONFIG_DIR;
  config.set_output_directory(ABS_OUTPUT);

  fs::path result = config.output_path();
  EXPECT_TRUE(result.is_absolute());
  EXPECT_EQ(result, fs::path(ABS_OUTPUT));
}

TEST(ConfigPaths, OutputPathRelative) {
  Config config;
  config.relative_path_to_config = ABS_CONFIG_DIR;
  config.set_output_directory("relative/output");

  fs::path result = config.output_path();
  EXPECT_EQ(result, fs::path(ABS_CONFIG_DIR) / "relative/output");
}

TEST(ConfigPaths, SetOutputDirectory) {
  Config config;
  config.set_output_directory("test_output");
  EXPECT_EQ(config.output_directory, fs::path("test_output"));

  config.set_output_directory("another/path");
  EXPECT_EQ(config.output_directory, fs::path("another/path"));
}

// =============================================================================
// Config las_filepaths tests
// =============================================================================

TEST(ConfigPaths, LasFilepathsAbsolute) {
  Config config;
  config.relative_path_to_config = ABS_CONFIG_DIR2;
  config.las_files = {fs::path(ABS_FILE1), fs::path(ABS_FILE2)};

  auto paths = config.las_filepaths();
  EXPECT_EQ(paths.size(), 2u);
  EXPECT_EQ(paths[0], fs::path(ABS_FILE1));
  EXPECT_EQ(paths[1], fs::path(ABS_FILE2));
}

TEST(ConfigPaths, LasFilepathsRelative) {
  Config config;
  config.relative_path_to_config = ABS_CONFIG_DIR2;
  config.las_files = {fs::path("data/file1.las"), fs::path("data/file2.laz")};

  auto paths = config.las_filepaths();
  EXPECT_EQ(paths.size(), 2u);
  EXPECT_EQ(paths[0], fs::path(ABS_CONFIG_DIR2) / "data/file1.las");
  EXPECT_EQ(paths[1], fs::path(ABS_CONFIG_DIR2) / "data/file2.laz");
}

TEST(ConfigPaths, LasFilepathsEmpty) {
  Config config;
  auto paths = config.las_filepaths();
  EXPECT_TRUE(paths.empty());
}

TEST(ConfigPaths, LasFilepathsMixed) {
  Config config;
  config.relative_path_to_config = ABS_CONFIG_DIR2;
  config.las_files = {fs::path(ABS_FILE1), fs::path("relative/file2.laz")};

  auto paths = config.las_filepaths();
  EXPECT_EQ(paths.size(), 2u);
  EXPECT_EQ(paths[0], fs::path(ABS_FILE1));
  EXPECT_EQ(paths[1], fs::path(ABS_CONFIG_DIR2) / "relative/file2.laz");
}

// =============================================================================
// ContourConfigs additional edge cases
// =============================================================================

TEST(ContourConfigs, PickFromHeightNegative) {
  ContourConfigs configs({{"normal", ContourConfig{2.5, 3, RGBColor(0, 0, 0), 0.14}},
                          {"index", ContourConfig{10.0, 5, RGBColor(0, 0, 0), 0.25}}});

  // Negative heights should also work since pick_from_height uses std::abs
  const ContourConfig& c = configs.pick_from_height(-10.0);
  EXPECT_DOUBLE_EQ(c.interval, 10.0);

  const ContourConfig& c2 = configs.pick_from_height(-5.0);
  EXPECT_DOUBLE_EQ(c2.interval, 2.5);
}

TEST(ContourConfigs, MinimumIntervalStatic) {
  std::map<std::string, ContourConfig> configs_map;
  configs_map["a"] = ContourConfig{5.0, 1, RGBColor(0, 0, 0), 0.1};
  configs_map["b"] = ContourConfig{2.5, 1, RGBColor(0, 0, 0), 0.1};
  configs_map["c"] = ContourConfig{10.0, 1, RGBColor(0, 0, 0), 0.1};

  double min = ContourConfigs::minimum_interval(configs_map);
  EXPECT_DOUBLE_EQ(min, 2.5);
}

// =============================================================================
// ContourConfigs layer_name edge cases
// =============================================================================

TEST(ContourConfigs, LayerNameDefaultForUnknown) {
  // If configs don't have form_line/index/normal names, layer_name stays "Contour"
  ContourConfigs configs({{"custom", ContourConfig{5.0, 1, RGBColor(0, 0, 0), 0.1}}});
  std::string name = configs.layer_name_from_height(5.0);
  EXPECT_EQ(name, "Contour");
}

// =============================================================================
// WaterConfigs edge cases
// =============================================================================

TEST(WaterConfigs, ConfigFromCatchmentExact) {
  WaterConfigs configs;
  configs.configs["minor"] = WaterConfig{0.01, RGBColor(0, 0, 255), 0.1};
  configs.configs["major"] = WaterConfig{1.0, RGBColor(0, 0, 255), 0.3};

  // Exact match at threshold
  const WaterConfig& c = configs.config_from_catchment(1.0);
  EXPECT_DOUBLE_EQ(c.catchment, 1.0);

  const WaterConfig& c2 = configs.config_from_catchment(0.01);
  EXPECT_DOUBLE_EQ(c2.catchment, 0.01);
}
