#include <gmock/gmock.h>

#include "PartDocumentImporter.hpp"
#include "StubPartDocument.hpp" 
#include "StubProgressScope.hpp"
#include "ImportTestDoc.hpp"

class DocumentImportTest : public ::testing::Test {

    void SetUp() {
        dest = std::make_unique<PartDocument>(StubPartDocument::partDocument());
        progress = std::move(progressFactory.scope());
    }
    protected:
    std::unique_ptr<PartDocument> dest;
    std::unique_ptr<AbstractProgressScope> progress;
    StubProgressScopeFactory progressFactory;
};

TEST_F(DocumentImportTest, TestTwoAssembliesWithPrototypeImport){
    auto source = TwoAssembliesWithSamePrototypeDoc();
    PartDocumentImporter::import(source.doc, *dest, *progress);
    dest->save("C:/Users/kryst/Documents/Repositories/OcafCAD/tests/unit/OcafKernel/DocumentImport/destDoc.xml");
    EXPECT_EQ(dest->prototypes().size(), 1);
    auto freeParts = dest->freeParts();
    EXPECT_EQ(freeParts.size(), 2);

    Part partA = Part(freeParts[0]);
    Part partB = Part(freeParts[1]);
    EXPECT_TRUE(partA.isAssembly());
    EXPECT_TRUE(partB.isAssembly());
}

// TEST_F(DocumentImportTest, TestTwoAssembliesWithSubAssemblyImport){
//     auto source = TwoAssembliesWithSamePrototypeDoc();
//     PartDocumentImporter::import(source.doc, *dest, *progress);
    
//     EXPECT_EQ(dest->prototypes().size(), 1);
//     EXPECT_EQ(dest->topLevelParts().size(), 2);

//     Part partA = Part(dest->topLevelParts()[0]);
//     Part partB = Part(dest->topLevelParts()[1]);
//     EXPECT_TRUE(partA.isAssembly());
//     EXPECT_TRUE(partB.isAssembly());
//     EXPECT_EQ(partA.childrenComponents(), partB.childrenComponents());
// }