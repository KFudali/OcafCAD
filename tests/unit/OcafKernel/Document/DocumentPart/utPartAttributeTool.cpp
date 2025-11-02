#include <gmock/gmock.h>

#include "DocumentGeometryFixture.hpp"
#include "StubPartPrototypes.hpp"

#include "PartAttributeTool.hpp"

class PartAttributeToolTest : public DocumentGeometryFixture {
    protected:
    void SetUp() {
        DocumentGeometryFixture::SetUp();
        cubeShapeLabel = geoDoc->addShape(cubeShape);
        auto cubeLabel = geoDoc->addPart(cubeShapeLabel, Location());
        attrTool = std::make_unique<PartAttributeTool>(cubeLabel);
    }
    Shape cubeShape = StubPartPrototypes::cube();
    ShapeLabel cubeShapeLabel;
    std::unique_ptr<PartAttributeTool> attrTool;
};

TEST_F(PartAttributeToolTest, SetName) {
    std::string newName("newName");
    std::string anotherName("anotherName");

    attrTool->setName(newName);
    EXPECT_EQ(attrTool->name(), newName);

    attrTool->setName(anotherName);
    EXPECT_EQ(attrTool->name(), anotherName);

}

TEST_F(PartAttributeToolTest, SetColor) {
    ColorRGBA newColor(1.0, 1.0, 1.0, 1.0);
    attrTool->setColor(newColor);
    EXPECT_EQ(attrTool->color(), newColor);

    ColorRGBA anotherColor(0.5, 0.5, 0.5, 1.0);
    attrTool->setColor(anotherColor);
    EXPECT_EQ(attrTool->color(), anotherColor);
}