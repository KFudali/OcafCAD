#include <gmock/gmock.h>

#include "DocumentGeometryFixture.hpp"
#include "StubPartPrototypes.hpp"

#include "PartAssemblyTool.hpp"
#include "PartShapeTool.hpp"

class PartAssemblyToolCubeSphereAssemblyTest : public DocumentGeometryFixture {
    protected:
    void SetUp() {
        DocumentGeometryFixture::SetUp();
        cubeProtoLabel = geoDoc->addShape(cubePrototype);
        sphereProtoLabel = geoDoc->addShape(spherePrototype);

        auto assemblyPartLabel = geoDoc->addEmptyAssembly(); 
        assemblyTool = std::make_unique<PartAssemblyTool>(assemblyPartLabel);
    }
    Location cubeLocation = LocationUtils::fromCoords(1.0, 2.0, 3.0);
    Location sphereLocation = LocationUtils::fromCoords(4.0, 5.0, 6.0);
    Shape cubePrototype = StubPartPrototypes::cube();
    Shape spherePrototype = StubPartPrototypes::sphere();

    ShapeLabel cubeProtoLabel;
    ShapeLabel sphereProtoLabel;
    std::unique_ptr<PartAssemblyTool> assemblyTool;
};

TEST_F(PartAssemblyToolCubeSphereAssemblyTest, PartCanAddPrototypeLabelAsComponent) {
    ASSERT_TRUE(assemblyTool->isAssembly());
    auto compLabel = assemblyTool->addComponent(
        cubeProtoLabel, cubeLocation
    );
    
    ASSERT_TRUE(compLabel.isValid());
    
    auto compAssTool = PartAssemblyTool(compLabel);
    auto compShapeTool = PartShapeTool(compLabel);
    EXPECT_TRUE(compAssTool.isComponent());
    EXPECT_TRUE(compShapeTool.shape().IsEqual(cubePrototype));
    EXPECT_TRUE(
        LocationUtils::LocationTrsfEqual(
            compShapeTool.location(), 
            cubeLocation
        )
    );
}

TEST_F(PartAssemblyToolCubeSphereAssemblyTest, PartCanAddPartLabelAsComponent) {
    ASSERT_TRUE(assemblyTool->isAssembly());
    auto spherePartLabel = geoDoc->addPart(sphereProtoLabel, sphereLocation);
    auto compLabel = assemblyTool->addComponent(spherePartLabel, sphereLocation);
    
    auto compAssTool = PartAssemblyTool(compLabel);
    auto compShapeTool = PartShapeTool(compLabel);
    EXPECT_TRUE(compAssTool.isComponent());
    EXPECT_TRUE(compShapeTool.shape().IsEqual(spherePrototype));
    EXPECT_TRUE(
        LocationUtils::LocationTrsfEqual(
            compShapeTool.location(), 
            sphereLocation
        )
    );
}

TEST_F(PartAssemblyToolCubeSphereAssemblyTest, AssemblyPartReturnsItsChildrenComponents) {
    ASSERT_TRUE(assemblyTool->isAssembly());
    
    auto cubeCompLabel = assemblyTool->addComponent(
        cubeProtoLabel, cubeLocation
    );
    auto sphereCompLabel = assemblyTool->addComponent(
        sphereProtoLabel, sphereLocation
    );

    auto cubeCompTool = PartAssemblyTool(cubeCompLabel);
    auto sphereCompTool = PartAssemblyTool(sphereCompLabel);

    EXPECT_TRUE(cubeCompTool.isComponent());
    EXPECT_TRUE(sphereCompTool.isComponent());
    
    auto compLabels = assemblyTool->childrenComponents();
    std::vector<PartLabel> expected{cubeCompLabel, sphereCompLabel};
    EXPECT_TRUE(std::is_permutation(
        compLabels.begin(), compLabels.end(), 
        expected.begin(), expected.end()
    ));
}

TEST_F(PartAssemblyToolCubeSphereAssemblyTest, AssemblyPartCanRemoveComponentFromItself) {
    ASSERT_TRUE(assemblyTool->isAssembly());
    
    auto cubeCompLabel = assemblyTool->addComponent(
        cubeProtoLabel, cubeLocation
    );
    auto sphereCompLabel = assemblyTool->addComponent(
        sphereProtoLabel, sphereLocation
    );

    auto cubeCompTool = PartAssemblyTool(cubeCompLabel);
    auto sphereCompTool = PartAssemblyTool(sphereCompLabel);

    EXPECT_TRUE(cubeCompTool.isComponent());
    EXPECT_TRUE(sphereCompTool.isComponent());
    
    EXPECT_TRUE(assemblyTool->removeComponent(cubeCompLabel));

    auto comps = assemblyTool->childrenComponents();
    ASSERT_EQ(comps.size(), 1);
    EXPECT_EQ(comps[0], sphereCompLabel);
}

TEST_F(PartAssemblyToolCubeSphereAssemblyTest, ComponentPartReturnsItsParentAssembly) {
    ASSERT_TRUE(assemblyTool->isAssembly());
    
    auto cubeCompLabel = assemblyTool->addComponent(
        cubeProtoLabel, cubeLocation
    );
    auto sphereCompLabel = assemblyTool->addComponent(
        sphereProtoLabel, sphereLocation
    );

    auto cubeCompTool = PartAssemblyTool(cubeCompLabel);
    auto sphereCompTool = PartAssemblyTool(sphereCompLabel);

    EXPECT_TRUE(cubeCompTool.isComponent());
    EXPECT_TRUE(sphereCompTool.isComponent());
    
    EXPECT_EQ(cubeCompTool.parentAssembly(), assemblyTool->label());
    EXPECT_EQ(sphereCompTool.parentAssembly(), assemblyTool->label());
}

