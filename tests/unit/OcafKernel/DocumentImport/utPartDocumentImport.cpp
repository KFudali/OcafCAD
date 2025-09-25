#include <gmock/gmock.h>

#include "AbstractProgressPublisher.hpp"
#include "PartDocumentImporter.hpp"
#include "StubPartDocument.hpp" 
#include "ImportTestDoc.hpp"

class DocumentImportTest : public ::testing::Test {

    void SetUp() {
        dest = std::make_unique<PartDocument>(StubPartDocument::partDocument());
    }
    protected:
    IdleProgressPublisher progress;
    std::unique_ptr<PartDocument> dest;
};

TEST_F(DocumentImportTest, TestOneAssemblyWithTwoPrototypes){
    auto source = OneAssemblyWithTwoPrototypesDoc();
    PartDocumentImporter::import(source.doc, *dest, progress);
    EXPECT_EQ(dest->prototypes().size(), 3);
    auto freeParts = dest->freeParts();
    EXPECT_EQ(freeParts.size(), 1);
    Part assembly = Part(freeParts[0]);
    EXPECT_TRUE(assembly.isAssembly());

    auto comps = assembly.childrenComponents();

    ASSERT_EQ(comps.size(), 2);

    EXPECT_TRUE(Part(comps[0]).prototype().IsEqual(source.cube));
    EXPECT_TRUE(Part(comps[1]).prototype().IsEqual(source.sphere));
}

TEST_F(DocumentImportTest, TestTwoAssembliesWithPrototypeImport){
    auto source = TwoAssembliesWithSamePrototypeDoc();
    PartDocumentImporter::import(source.doc, *dest, progress);
    EXPECT_EQ(dest->prototypes().size(), 3);
    auto freeParts = dest->freeParts();
    EXPECT_EQ(freeParts.size(), 2);

    Part partA = Part(freeParts[0]);
    Part partB = Part(freeParts[1]);
    EXPECT_TRUE(partA.isAssembly());
    EXPECT_TRUE(partB.isAssembly());

    auto compsA = partA.childrenComponents();
    auto compsB = partB.childrenComponents();

    ASSERT_EQ(compsA.size(), 1);
    ASSERT_EQ(compsB.size(), 1);

    EXPECT_TRUE(Part(compsA[0]).prototype().IsEqual(source.cube));
    EXPECT_TRUE(Part(compsB[0]).prototype().IsEqual(source.cube));
}

TEST_F(DocumentImportTest, TestTwoAssembliesWithSubAssemblyImport){
    auto source = TwoAssembliesWithSameSubAssembly();
    PartDocumentImporter::import(source.doc, *dest, progress);
    
    EXPECT_EQ(dest->prototypes().size(), 6);
    ASSERT_EQ(dest->topLevelParts().size(), 3);
    
    Part partA = Part(dest->topLevelParts()[1]);
    Part partB = Part(dest->topLevelParts()[2]);
    EXPECT_TRUE(partA.isAssembly());
    EXPECT_TRUE(partB.isAssembly());

    ASSERT_EQ(partA.childrenComponents().size(), 1);
    ASSERT_EQ(partB.childrenComponents().size(), 1);
}