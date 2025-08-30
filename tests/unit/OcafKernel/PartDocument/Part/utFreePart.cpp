#include <gtest/gtest.h>

#include "StubPartDocument.hpp"
#include "StubPartPrototypes.hpp"
#include "PartLabel.hpp"
#include "Part.hpp"


class FreePartTest : public ::testing::Test {
    protected:   
    void SetUp() override {
        partDocument = std::make_unique<PartDocument>(StubPartDocument::partDocument());

    }
    std::unique_ptr<PartDocument> partDocument;
};

TEST_F(FreePartTest, PartUponCreationHasDefaultNameAndColor) {
    auto cubePrototype = StubPartPrototypes::cube();
    auto prototypeLabel = partDocument->addPrototype(cubePrototype);
    auto partLabel = partDocument->addPart(prototypeLabel, Location());
    auto part = Part(partLabel);
    
    EXPECT_EQ(part.color(), Part::defaultPartColor);
    EXPECT_EQ(part.name(), Part::defaultPartName);
}

TEST_F(FreePartTest, PartHasCorrectPrototype) {
    auto cubePrototype = StubPartPrototypes::cube();
    auto prototypeLabel = partDocument->addPrototype(cubePrototype);
    auto partLabel = partDocument->addPart(prototypeLabel, Location());
    auto part = Part(partLabel);

    EXPECT_TRUE(part.prototype().IsEqual(cubePrototype));
}

TEST_F(FreePartTest, FreePartIsNotAssemblyNorComponent) {
    auto cubePrototype = StubPartPrototypes::cube();
    auto prototypeLabel = partDocument->addPrototype(cubePrototype);
    auto partLabel = partDocument->addPart(prototypeLabel, Location());
    auto part = Part(partLabel);

    EXPECT_FALSE(part.isAssembly());
    EXPECT_FALSE(part.isComponent());
   
    auto assemblyLabel = part.parentAssembly(); 
    auto components = part.childrenComponents(); 

    EXPECT_FALSE(assemblyLabel.isValid());
    EXPECT_TRUE(components.empty());
}

TEST_F(FreePartTest, FreePartCanSetNameColorAndLocation) {
    auto cubePrototype = StubPartPrototypes::cube();
    auto prototypeLabel = partDocument->addPrototype(cubePrototype);
    auto partLabel = partDocument->addPart(prototypeLabel, Location());
    auto part = Part(partLabel);
    
    std::string newName = "NewPartName";
    ColorRGBA newColor(Quantity_NOC_RED);

    part.setName("NewPartName");
    part.setColor(newColor);

    EXPECT_EQ(part.name(), newName);
    EXPECT_EQ(part.color(), newColor);
}