#include <gmock/gmock.h>
#include "DocumentGeometryFixture.hpp"
#include "StubPartPrototypes.hpp"

#include "GeometryPart.hpp"

class GeometryPartSingleCubeTest : public DocumentGeometryFixture {
    protected:
    void SetUp() {
        DocumentGeometryFixture::SetUp();
        auto cubeProtoLabel = geoDoc->addPrototype(cubePrototype);
        auto cubePartLabel = geoDoc->addPart(cubeProtoLabel, Location());
        cubePart = std::make_unique<GeometryPart>(cubePartLabel);
    }
    PartPrototype cubePrototype = StubPartPrototypes::cube();
    std::unique_ptr<GeometryPart> cubePart;
};

TEST_F(GeometryPartSingleCubeTest, PartUponCreationHasDefaultNameAndColor) {
    EXPECT_EQ(cubePart->attributes().color(), Part::defaultPartColor);
    EXPECT_EQ(cubePart->attributes().name(), Part::defaultPartName);
}

TEST_F(GeometryPartSingleCubeTest, PartHasCorrectPrototype) {
    EXPECT_TRUE(cubePart->prototype().IsEqual(cubePrototype));
}

TEST_F(GeometryPartSingleCubeTest, FreePartIsNotAssemblyNorComponent) {
    EXPECT_FALSE(cubePart->isAssembly());
    EXPECT_FALSE(cubePart->isComponent());
   
    auto assemblyLabel = cubePart->parentAssembly(); 
    auto components = cubePart->childrenComponents(); 

    EXPECT_FALSE(assemblyLabel.isValid());
    EXPECT_TRUE(components.empty());
}

TEST_F(GeometryPartSingleCubeTest, FreePartCanSetNameColorAndLocation) {
    std::string newName = "NewPartName";
    ColorRGBA newColor(Quantity_NOC_RED);

    cubePart->attributes().setName("NewPartName");
    cubePart->attributes().setColor(newColor);

    EXPECT_EQ(cubePart->attributes().name(), newName);
    EXPECT_EQ(cubePart->attributes().color(), newColor);
}