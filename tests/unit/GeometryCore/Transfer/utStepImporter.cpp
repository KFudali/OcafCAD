#include "STEPImporter.hpp"
#include "StubPartDocument.hpp"
#include "StubSTEPFileSources.hpp"
#include <gmock/gmock.h>

class STEPImporterTest : public ::testing::Test {
    protected:
    void SetUp() {
        destDoc = std::make_unique<PartDocument>(
            StubPartDocument::partDocument()
        );
    }
    IdleProgressPublisher publisher;
    std::unique_ptr<PartDocument> destDoc;
};

TEST_F(STEPImporterTest, ImportCubeSTEPFile) {
    std::shared_ptr<AbstractInputSource> source =
        std::make_shared<FileSource>(StubSTEPFileSources::singlePartCube());
    STEPImporter importer(source);
    importer.importIntoDoc(*destDoc, publisher);
    auto free = destDoc->freeParts();
    auto protos = destDoc->prototypes();

    ASSERT_EQ(free.size(), 0);
    ASSERT_EQ(protos.size(), 1);   
}

TEST_F(STEPImporterTest, ImportJointAssemblySTEPFile) {
    std::shared_ptr<AbstractInputSource> source =
        std::make_shared<FileSource>(StubSTEPFileSources::singleAssemblyJoint());
    STEPImporter importer(source);
    importer.importIntoDoc(*destDoc, publisher);
    auto free = destDoc->freeParts();
    auto protos = destDoc->prototypes();

    ASSERT_EQ(free.size(), 1);
    ASSERT_EQ(protos.size(), 3);   
}