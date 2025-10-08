#include <gtest/gtest.h>

#include "StubPartDocument.hpp"
#include "StubPartPrototypes.hpp"
#include "StubPartAttrs.hpp"

#include "PartLabel.hpp"
#include "Part.hpp"

#include <TopoDS_Compound.hxx>

class AssemblyPartTest : public ::testing::Test {
    protected:   
    void SetUp() override {
        partDocument = std::make_unique<PartDocument>(
            StubPartDocument::partDocument()
        );
        assemblyPartLabel = partDocument->addEmptyAssembly();
        
        cubePrototypeLabel = partDocument->addPrototype(cube);
        spherePrototypeLabel = partDocument->addPrototype(sphere);
        
        spherePartLabel = partDocument->addPart(spherePrototypeLabel, Location());
        cubePartLabel = partDocument->addPart(cubePrototypeLabel, Location());
    }
    PartPrototype cube = StubPartPrototypes::cube();
    PartPrototype sphere = StubPartPrototypes::sphere();
    PartLabel assemblyPartLabel;
    PartLabel spherePartLabel;
    PartLabel cubePartLabel;
    PrototypeLabel cubePrototypeLabel;
    PrototypeLabel spherePrototypeLabel;
    std::unique_ptr<PartDocument> partDocument;
};

TEST_F(AssemblyPartTest, PartCanAddPrototypeLabelAsComponent) {
    auto assemblyPart = Part(assemblyPartLabel);
    ASSERT_TRUE(assemblyPart.isAssembly());
    auto location = StubPartAttrs::location(1.0, 2.0, 3.0);
    
    auto compLabel = assemblyPart.addComponent(
        spherePrototypeLabel, location
    );
    
    ASSERT_TRUE(compLabel.isValid());
    
    auto compPart = Part(compLabel);
    EXPECT_TRUE(compPart.isComponent());
    
    EXPECT_TRUE(compPart.prototype().IsEqual(sphere));
    EXPECT_TRUE(LocationUtils::LocationTrsfEqual(compPart.location(), location));
}

TEST_F(AssemblyPartTest, PartCanAddPartLabelAsComponent) {
    auto assemblyPart = Part(assemblyPartLabel);
    ASSERT_TRUE(assemblyPart.isAssembly());
    auto location = StubPartAttrs::location(1.0, 2.0, 3.0);
    
    auto compLabel = assemblyPart.addComponent(spherePartLabel, location);

    auto compPart = Part(compLabel);
    EXPECT_TRUE(compPart.isComponent());
    
    EXPECT_TRUE(compPart.prototype().IsEqual(sphere));
    EXPECT_TRUE(LocationUtils::LocationTrsfEqual(compPart.location(), location));
}

TEST_F(AssemblyPartTest, AssemblyPartReturnsItsChildrenComponents) {
    auto assemblyPart = Part(assemblyPartLabel);
    ASSERT_TRUE(assemblyPart.isAssembly());
    
    auto cubeLocation = StubPartAttrs::location(1.0, 2.0, 3.0);
    auto sphereLocation = StubPartAttrs::location(4.0, 5.0, 6.0);
    
    auto cubeCompLabel = assemblyPart.addComponent(cubePartLabel, cubeLocation);
    auto sphereCompLabel = assemblyPart.addComponent(spherePartLabel, sphereLocation);

    auto cubeCompPart = Part(cubeCompLabel);
    auto sphereCompPart = Part(sphereCompLabel);

    EXPECT_TRUE(cubeCompPart.isComponent());
    EXPECT_TRUE(sphereCompPart.isComponent());
    
    auto compLabels = assemblyPart.childrenComponents();
    std::vector<PartLabel> expected{cubeCompLabel, sphereCompLabel};
    EXPECT_TRUE(std::is_permutation(
        compLabels.begin(), compLabels.end(), 
        expected.begin(), expected.end()
    ));
}

TEST_F(AssemblyPartTest, AssemblyPartCanRemoveComponentFromItself) {
    auto assemblyPart = Part(assemblyPartLabel);
    ASSERT_TRUE(assemblyPart.isAssembly());
    
    auto cubeLocation = StubPartAttrs::location(1.0, 2.0, 3.0);
    auto sphereLocation = StubPartAttrs::location(4.0, 5.0, 6.0);
    
    auto cubeCompLabel = assemblyPart.addComponent(cubePartLabel, cubeLocation);
    auto sphereCompLabel = assemblyPart.addComponent(spherePartLabel, sphereLocation);

    auto cubeCompPart = Part(cubeCompLabel);
    auto sphereCompPart = Part(sphereCompLabel);

    EXPECT_TRUE(cubeCompPart.isComponent());
    EXPECT_TRUE(sphereCompPart.isComponent());
    
    EXPECT_TRUE(assemblyPart.removeComponent(cubeCompPart.partLabel()));

    auto comps = assemblyPart.childrenComponents();
    ASSERT_EQ(comps.size(), 1);
    EXPECT_EQ(comps[0], sphereCompPart.partLabel());
}

TEST_F(AssemblyPartTest, ComponentPartReturnsItsParentAssembly) {
    auto assemblyPart = Part(assemblyPartLabel);
    ASSERT_TRUE(assemblyPart.isAssembly());
    
    auto cubeLocation = StubPartAttrs::location(1.0, 2.0, 3.0);
    auto sphereLocation = StubPartAttrs::location(4.0, 5.0, 6.0);
    
    auto cubeCompLabel = assemblyPart.addComponent(cubePartLabel, cubeLocation);
    auto sphereCompLabel = assemblyPart.addComponent(spherePartLabel, sphereLocation);

    auto cubeCompPart = Part(cubeCompLabel);
    auto sphereCompPart = Part(sphereCompLabel);

    EXPECT_TRUE(cubeCompPart.isComponent());
    EXPECT_TRUE(sphereCompPart.isComponent());
    
    EXPECT_EQ(cubeCompPart.parentAssembly(), assemblyPartLabel);
    EXPECT_EQ(sphereCompPart.parentAssembly(), assemblyPartLabel);
}

