#include <gtest/gtest.h>
#include <gamenge/renderer/renderer.hpp>

TEST(RendererTest, init)
{
    // auto doc = jsonutils::loadJson("/home/pablo/Documents/test.json");

    // ASSERT_TRUE(doc);
    // ASSERT_TRUE(doc->HasWMember("source"));
    // auto source = (*doc)["source"].GetString();
    // ASSERT_STREQ("file", source);
    ASSERT_TRUE(1);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}