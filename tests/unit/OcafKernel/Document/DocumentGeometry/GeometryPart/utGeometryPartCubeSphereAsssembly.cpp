#include <gmock/gmock.h>
#include "DocumentGeometryFixture.hpp"
#include "StubPartPrototypes.hpp"
#include "GeometryPart.hpp"

class GeometryPartCubeSphereAssemblyTest : public DocumentGeometryFixture {
    protected:
    void SetUp() {
        DocumentGeometryFixture::SetUp();
        cubeProtoLabel = geoDoc->addPrototype(cubePrototype);
        sphereProtoLabel = geoDoc->addPrototype(spherePrototype);

        auto assemblyPartLabel = geoDoc->addEmptyAssembly(); 
        assemblyPart = std::make_unique<GeometryPart>(assemblyPartLabel);
    }
    Location cubeLocation = LocationUtils::fromCoords(1.0, 2.0, 3.0);
    Location sphereLocation = LocationUtils::fromCoords(4.0, 5.0, 6.0);
    Shape cubePrototype = StubPartPrototypes::cube();
    Shape spherePrototype = StubPartPrototypes::sphere();

    ShapeLabel cubeProtoLabel;
    ShapeLabel sphereProtoLabel;
    std::unique_ptr<GeometryPart> assemblyPart;
};

TEST_F(GeometryPartCubeSphereAssemblyTest, PartCanAddPrototypeLabelAsComponent) {
    ASSERT_TRUE(assemblyPart->isAssembly());
    auto compLabel = assemblyPart->addComponent(
        cubeProtoLabel, cubeLocation
    );
    
    ASSERT_TRUE(compLabel.isValid());
    
    auto compPart = Part(compLabel);
    EXPECT_TRUE(compPart.isComponent());
    EXPECT_TRUE(compPart.prototype().IsEqual(cubePrototype));
    EXPECT_TRUE(
        LocationUtils::LocationTrsfEqual(
            compPart.location(), 
            cubeLocation
        )
    );
}

TEST_F(GeometryPartCubeSphereAssemblyTest, PartCanAddPartLabelAsComponent) {
    ASSERT_TRUE(assemblyPart->isAssembly());
    auto spherePartLabel = geoDoc->addPart(sphereProtoLabel, sphereLocation);
    auto compLabel = assemblyPart->addComponent(spherePartLabel, sphereLocation);
    
    auto compPart = Part(compLabel);
    EXPECT_TRUE(compPart.isComponent());
    EXPECT_TRUE(compPart.prototype().IsEqual(spherePrototype));
    EXPECT_TRUE(
        LocationUtils::LocationTrsfEqual(
            compPart.location(), sphereLocation
        )
    );
}

TEST_F(GeometryPartCubeSphereAssemblyTest, AssemblyPartReturnsItsChildrenComponents) {
    ASSERT_TRUE(assemblyPart->isAssembly());
    
    auto cubeCompLabel = assemblyPart->addComponent(
        cubeProtoLabel, cubeLocation
    );
    auto sphereCompLabel = assemblyPart->addComponent(
        sphereProtoLabel, sphereLocation
    );

    auto cubeCompPart = Part(cubeCompLabel);
    auto sphereCompPart = Part(sphereCompLabel);

    EXPECT_TRUE(cubeCompPart.isComponent());
    EXPECT_TRUE(sphereCompPart.isComponent());
    
    auto compLabels = assemblyPart->childrenComponents();
    std::vector<PartLabel> expected{cubeCompLabel, sphereCompLabel};
    EXPECT_TRUE(std::is_permutation(
        compLabels.begin(), compLabels.end(), 
        expected.begin(), expected.end()
    ));
}

TEST_F(GeometryPartCubeSphereAssemblyTest, AssemblyPartCanRemoveComponentFromItself) {
    ASSERT_TRUE(assemblyPart->isAssembly());
    
    auto cubeCompLabel = assemblyPart->addComponent(
        cubeProtoLabel, cubeLocation
    );
    auto sphereCompLabel = assemblyPart->addComponent(
        sphereProtoLabel, sphereLocation
    );

    auto cubeCompPart = Part(cubeCompLabel);
    auto sphereCompPart = Part(sphereCompLabel);

    EXPECT_TRUE(cubeCompPart.isComponent());
    EXPECT_TRUE(sphereCompPart.isComponent());
    
    EXPECT_TRUE(assemblyPart->removeComponent(cubeCompPart.partLabel()));

    auto comps = assemblyPart->childrenComponents();
    ASSERT_EQ(comps.size(), 1);
    EXPECT_EQ(comps[0], sphereCompPart.partLabel());
}

TEST_F(GeometryPartCubeSphereAssemblyTest, ComponentPartReturnsItsParentAssembly) {
    ASSERT_TRUE(assemblyPart->isAssembly());
    
    auto cubeCompLabel = assemblyPart->addComponent(
        cubeProtoLabel, cubeLocation
    );
    auto sphereCompLabel = assemblyPart->addComponent(
        sphereProtoLabel, sphereLocation
    );

    auto cubeCompPart = Part(cubeCompLabel);
    auto sphereCompPart = Part(sphereCompLabel);

    EXPECT_TRUE(cubeCompPart.isComponent());
    EXPECT_TRUE(sphereCompPart.isComponent());
    
    EXPECT_EQ(cubeCompPart.parentAssembly(), assemblyPart->partLabel());
    EXPECT_EQ(sphereCompPart.parentAssembly(), assemblyPart->partLabel());
}

