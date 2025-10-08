#include "StubPartLabels.hpp"
#include "Part.hpp"

class PartTest : public ::testing::Test {
    protected:   
    Part cubePart = Part{StubPartLabels::cube()};
};

TEST_F(PartTest, SetName) {
    std::string newName("newName");
    EXPECT_NE(cubePart.attributes().name(), newName);

    cubePart.attributes().setName(newName);
    EXPECT_EQ(cubePart.attributes().name(), newName);
}

TEST_F(PartTest, SetColor) {
    ColorRGBA newColor(0.5, 0.5, 0.5, 0.5,);
    EXPECT_NE(cubePart.attributes().color(), newColor);

    cubePart.attributes()..setColor(newColor);
    EXPECT_EQ(cubePart.attributes()..color(), newColor);
}