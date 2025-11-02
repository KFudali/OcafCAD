#include <gmock/gmock.h>
#include "DocumentGeometryFixture.hpp"
#include "StubPartPrototypes.hpp"

#include "Part.hpp"

class PartSingleCubeTest : public DocumentGeometryFixture {
    protected:
    void SetUp() {
        DocumentGeometryFixture::SetUp();
        auto cubeShapeLabel = geoDoc->addShape(cubePrototype);
        auto cubePartLabel = geoDoc->addPart(cubeShapeLabel, Location());
        cubePart = std::make_unique<Part>(cubePartLabel);
    }
    Shape cubePrototype = StubPartPrototypes::cube();
    std::unique_ptr<Part> cubePart;
};

TEST_F(PartSingleCubeTest, PartUponCreationHasDefaultNameAndColor) {
    EXPECT_TRUE(cubePart->attributes().color().IsEqual(Part::defaultColor));
    EXPECT_EQ(cubePart->attributes().name(), Part::defaultName);
}

TEST_F(PartSingleCubeTest, PartHasCorrectPrototype) {
    EXPECT_TRUE(cubePart->shape().IsEqual(cubePrototype));
}