#include "GeometryCore.hpp"
#include "STEPImporter.hpp"

#include "GeometryFileSources.hpp"
#include "GeometryCoreFixture.hpp"
#include "MockGeometryObserver.hpp"

#include "DocLabel.hpp"

#include <gmock/gmock.h>


class ImportSTEPTest : public GeometryCoreFixture {
    protected:
    MockGeometryObserver mockObserver;
};

TEST_F(ImportSTEPTest, TestImportCube) {
    using ::testing::_;
    using ::testing::Exactly;

    EXPECT_CALL(mockObserver, onPartAdded(_)).Times(Exactly(1));
    geometryCore->events()->appendObserver(&mockObserver);

    std::shared_ptr<AbstractInputSource> source =
        std::make_shared<FileSource>(STEPFiles::singlePartCube());
    STEPImporter importer(source);

    geometryCore->import(importer);
    ASSERT_EQ(geometryCore->view()->topLevelPartLabels().size(), 1);
    ASSERT_EQ(geometryCore->view()->topLevelParts().size(), 1);
    ASSERT_EQ(geometryCore->view()->geometryObjects().size(), 1);
}

// TEST_F(GeometryCoreImportSTEPIntegrationTest, TestUndoImportCube) {
//     using ::testing::_;
//     using ::testing::Exactly;

//     auto mockObserver = std::make_unique<MockGeometryObserver>();

//     EXPECT_CALL(*mockObserver, onPartAdded(_)).Times(Exactly(1));
//     EXPECT_CALL(*mockObserver, onPartRemoved(_)).Times(Exactly(1));
    
//     core->events()->appendObserver(mockObserver.get());

//     std::shared_ptr<AbstractInputSource> source =
//         std::make_shared<FileSource>(StubSTEPFileSources::singlePartCube());
//     STEPImporter importer(source);

//     core->import(importer);
//     core->commands().undo();

//     ASSERT_EQ(core->view()->topLevelPartLabels().size(), 0);
//     ASSERT_EQ(core->view()->topLevelParts().size(), 0);
//     ASSERT_EQ(core->view()->geometryObjects().size(), 0);
// }

// TEST_F(GeometryCoreImportSTEPIntegrationTest, TestRedoImportCube) {
//     using ::testing::_;
//     using ::testing::Exactly;

//     auto mockObserver = std::make_unique<MockGeometryObserver>();

//     EXPECT_CALL(*mockObserver, onPartAdded(_)).Times(Exactly(2));
//     EXPECT_CALL(*mockObserver, onPartRemoved(_)).Times(Exactly(1));
    
//     core->events()->appendObserver(mockObserver.get());

//     std::shared_ptr<AbstractInputSource> source =
//         std::make_shared<FileSource>(StubSTEPFileSources::singlePartCube());
//     STEPImporter importer(source);

//     core->import(importer);
//     core->commands().undo();
//     core->commands().redo();

//     ASSERT_EQ(core->view()->topLevelPartLabels().size(), 1);
//     ASSERT_EQ(core->view()->topLevelParts().size(), 1);
//     ASSERT_EQ(core->view()->geometryObjects().size(), 1);
// }