#include <gtest/gtest.h>

#include "config_input/config_input.hpp"

// =============================================================================
// ContourConfigs tests
// =============================================================================

TEST(ContourConfigs, MinInterval) {
  ContourConfigs configs({{"normal", ContourConfig{2.5, 3, RGBColor(0, 0, 0), 0.14}},
                          {"index", ContourConfig{10.0, 5, RGBColor(0, 0, 0), 0.25}}});
  EXPECT_DOUBLE_EQ(configs.min_interval, 2.5);
}

TEST(ContourConfigs, PickFromHeight) {
  ContourConfigs configs({{"normal", ContourConfig{2.5, 3, RGBColor(100, 0, 0), 0.14}},
                          {"index", ContourConfig{10.0, 5, RGBColor(0, 100, 0), 0.25}}});

  // Height 5.0 is multiple of 2.5 but not 10.0 -> should pick "normal"
  const ContourConfig& c1 = configs.pick_from_height(5.0);
  EXPECT_DOUBLE_EQ(c1.interval, 2.5);

  // Height 10.0 is multiple of both 2.5 and 10.0 -> should pick "index" (larger interval)
  const ContourConfig& c2 = configs.pick_from_height(10.0);
  EXPECT_DOUBLE_EQ(c2.interval, 10.0);

  // Height 20.0 is multiple of both -> should pick "index"
  const ContourConfig& c3 = configs.pick_from_height(20.0);
  EXPECT_DOUBLE_EQ(c3.interval, 10.0);

  // Height 2.5 is multiple of 2.5 only -> should pick "normal"
  const ContourConfig& c4 = configs.pick_from_height(2.5);
  EXPECT_DOUBLE_EQ(c4.interval, 2.5);
}

TEST(ContourConfigs, LayerNameFromHeight) {
  ContourConfigs configs({{"normal", ContourConfig{2.5, 3, RGBColor(0, 0, 0), 0.14}},
                          {"index", ContourConfig{10.0, 5, RGBColor(0, 0, 0), 0.25}},
                          {"form_line", ContourConfig{1.25, 2, RGBColor(0, 0, 0), 0.1}}});

  // Height 10.0 matches index (largest interval)
  EXPECT_EQ(configs.layer_name_from_height(10.0), "102_Index_Contour");

  // Height 5.0 matches normal but not index
  EXPECT_EQ(configs.layer_name_from_height(5.0), "101_Contour");

  // Height 2.5 matches normal (interval 2.5) which is bigger than form_line (1.25)
  EXPECT_EQ(configs.layer_name_from_height(2.5), "101_Contour");

  // Height 1.25 matches form_line only
  EXPECT_EQ(configs.layer_name_from_height(1.25), "103_Form_Line");
}

TEST(ContourConfigs, IndexOperator) {
  ContourConfigs configs({{"normal", ContourConfig{2.5, 3, RGBColor(0, 0, 0), 0.14}}});
  const ContourConfig& c = configs["normal"];
  EXPECT_DOUBLE_EQ(c.interval, 2.5);
  EXPECT_EQ(c.min_points, 3u);
}

TEST(ContourConfigs, DefaultConstruction) {
  ContourConfigs configs;
  EXPECT_DOUBLE_EQ(configs.min_interval, std::numeric_limits<double>::max());
}

// =============================================================================
// WaterConfigs tests
// =============================================================================

TEST(WaterConfigs, ConfigFromCatchment) {
  WaterConfigs configs;
  configs.configs["minor"] = WaterConfig{0.01, RGBColor(0, 0, 255), 0.1};
  configs.configs["medium"] = WaterConfig{0.1, RGBColor(0, 0, 255), 0.2};
  configs.configs["major"] = WaterConfig{1.0, RGBColor(0, 0, 255), 0.3};

  // Catchment of 0.5 -> should pick "medium" (0.1 <= 0.5 but 1.0 > 0.5)
  const WaterConfig& c1 = configs.config_from_catchment(0.5);
  EXPECT_DOUBLE_EQ(c1.catchment, 0.1);

  // Catchment of 2.0 -> should pick "major" (all qualify, "major" has largest catchment)
  const WaterConfig& c2 = configs.config_from_catchment(2.0);
  EXPECT_DOUBLE_EQ(c2.catchment, 1.0);

  // Catchment of 0.05 -> should pick "minor" (only one qualifies)
  const WaterConfig& c3 = configs.config_from_catchment(0.05);
  EXPECT_DOUBLE_EQ(c3.catchment, 0.01);
}

TEST(WaterConfigs, MinimumCatchment) {
  WaterConfigs configs;
  configs.configs["minor"] = WaterConfig{0.01, RGBColor(0, 0, 255), 0.1};
  configs.configs["medium"] = WaterConfig{0.1, RGBColor(0, 0, 255), 0.2};
  configs.configs["major"] = WaterConfig{1.0, RGBColor(0, 0, 255), 0.3};

  EXPECT_DOUBLE_EQ(configs.minimum_catchment(), 0.01);
}

// =============================================================================
// VegeHeightConfig tests
// =============================================================================

TEST(VegeHeightConfig, PickFromBlockedProportion) {
  VegeHeightConfig vhc;
  vhc.name = "test";
  vhc.min_height = 2.0;
  vhc.max_height = 100.0;

  BlockingThresholdColorPair green;
  green.blocking_threshold = 0.01;
  green.color = RGBColor(0, 255, 0);

  BlockingThresholdColorPair dark_green;
  dark_green.blocking_threshold = 0.5;
  dark_green.color = RGBColor(0, 128, 0);

  vhc.colors.push_back(green);
  vhc.colors.push_back(dark_green);

  // Below all thresholds -> no color
  auto c1 = vhc.pick_from_blocked_proportion(0.005);
  EXPECT_FALSE(c1.has_value());

  // Above first threshold but below second
  auto c2 = vhc.pick_from_blocked_proportion(0.2);
  ASSERT_TRUE(c2.has_value());
  RGBColor rgb2 = to_rgb(*c2);
  EXPECT_EQ(rgb2.getRed(), 0);
  EXPECT_EQ(rgb2.getGreen(), 255);
  EXPECT_EQ(rgb2.getBlue(), 0);

  // Above both thresholds -> should pick last qualifying (dark_green)
  auto c3 = vhc.pick_from_blocked_proportion(0.8);
  ASSERT_TRUE(c3.has_value());
  RGBColor rgb3 = to_rgb(*c3);
  EXPECT_EQ(rgb3.getRed(), 0);
  EXPECT_EQ(rgb3.getGreen(), 128);
  EXPECT_EQ(rgb3.getBlue(), 0);
}

TEST(VegeHeightConfig, PickFromBlockedProportionEmpty) {
  VegeHeightConfig vhc;
  vhc.name = "empty";
  vhc.min_height = 0.0;
  vhc.max_height = 10.0;
  // No colors configured

  auto c = vhc.pick_from_blocked_proportion(0.5);
  EXPECT_FALSE(c.has_value());
}
