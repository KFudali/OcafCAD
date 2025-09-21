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

TEST_F(STEPImporterTest, testImporterInit) {
    std::shared_ptr<AbstractInputSource> source =
        std::make_shared<FileSource>(StubSTEPFileSources::singlePartCube());
    STEPImporter importer(source);
    importer.importIntoDoc(*destDoc, publisher);
}