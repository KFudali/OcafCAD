#include <gtest/gtest.h>
#include "StubPartDocument.hpp"
#include "StubPartPrototypes.hpp"
#include "PartDocument.hpp"

class PartDocumentTest : public ::testing::Test {
    protected:   
    void SetUp() override {
        partDocument = std::make_unique<PartDocument>(StubPartDocument::partDocument());
    }
    
    PartPrototype cube = StubPartPrototypes::cube();
    PartPrototype sphere = StubPartPrototypes::sphere();
    std::unique_ptr<PartDocument> partDocument;
};

TEST_F(PartDocumentTest, RootAssemblyIsValidUponCreation){
    ASSERT_TRUE(partDocument->rootAssemblyLabel().isValid());
}


TEST_F(PartDocumentTest, AddedPrototypesAppearsInPrototypes){
    auto cubeProtoLabel = partDocument->addPrototype(cube);
    auto sphereProtoLabel = partDocument->addPrototype(sphere);

    auto prototypes = partDocument->prototypes(); 
    
    std::vector<PrototypeLabel> expected{cubeProtoLabel, sphereProtoLabel};
    EXPECT_TRUE(std::is_permutation(
        prototypes.begin(), prototypes.end(), 
        expected.begin(), expected.end()
    ));
}

TEST_F(PartDocumentTest, AddedEmptyPartAppearsInFreeParts){
    auto cubeProtoLabel = partDocument->addPrototype(cube);
    auto sphereProtoLabel = partDocument->addPrototype(sphere);

    auto cubePartLabel = partDocument->addPart(cubeProtoLabel, Location());
    auto spherePartLabel = partDocument->addPart(sphereProtoLabel, Location());

    auto parts = partDocument->topLevelParts();

    std::vector<PartLabel> expected{cubePartLabel, spherePartLabel};
    EXPECT_TRUE(std::is_permutation(
        parts.begin(), parts.end(), 
        expected.begin(), expected.end()
    ));
}

TEST_F(PartDocumentTest, AddedEmptyAppearInFreeParts){
    auto emtpyPartLabel_a = partDocument->addEmptyPart();
    auto emtpyPartLabel_b = partDocument->addEmptyPart();

    auto emptyAssemblyLabel_a = partDocument->addEmptyAssembly();
    auto emptyAssemblyLabel_b = partDocument->addEmptyAssembly();

    std::vector<PartLabel> expected{
        emtpyPartLabel_a, emtpyPartLabel_b,
        emptyAssemblyLabel_a, emptyAssemblyLabel_b
    };

    auto parts = partDocument->topLevelParts();

    EXPECT_TRUE(std::is_permutation(
        parts.begin(), parts.end(), 
        expected.begin(), expected.end()
    ));
}

TEST_F(PartDocumentTest, CannotAddTheSamePrototypeTwice){
    auto firstCubeLabel = partDocument->addPrototype(cube);
    auto secondCubeLabel = partDocument->addPrototype(cube);

    EXPECT_EQ(firstCubeLabel, secondCubeLabel);
    
    auto prototypes = partDocument->prototypes(); 
    ASSERT_EQ(prototypes.size(), 1);
    EXPECT_EQ(prototypes[0], firstCubeLabel);
}