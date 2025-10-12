#include "GeometryCore.hpp"
#include "STEPImporter.hpp"

#include "GeometryFileSources.hpp"
#include "GeometryCoreFixture.hpp"
#include "MockGeometryObserver.hpp"

#include "DocLabel.hpp"

#include <gmock/gmock.h>


class ImportSTEPTest : public GeometryCoreFixture {
    protected:
    void SetUp() {
        GeometryCoreFixture::SetUp();
    }
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

    kernel->commands().openCommand();    
    geometryCore->import(importer);
    kernel->commands().commitCommand();    
    ASSERT_EQ(geometryCore->view()->topLevelPartLabels().size(), 1);
    ASSERT_EQ(geometryCore->view()->topLevelParts().size(), 1);
    ASSERT_EQ(geometryCore->view()->geometryObjects().size(), 1);
}

TEST_F(ImportSTEPTest, TestUndoImportCube) {
    using ::testing::_;
    using ::testing::Exactly;

    EXPECT_CALL(mockObserver, onPartAdded(_)).Times(Exactly(1));
    EXPECT_CALL(mockObserver, onPartRemoved(_)).Times(Exactly(1));
    geometryCore->events()->appendObserver(&mockObserver);

    std::shared_ptr<AbstractInputSource> source =
        std::make_shared<FileSource>(STEPFiles::singlePartCube());
    STEPImporter importer(source);
    kernel->commands().openCommand();    
    geometryCore->import(importer);
    kernel->commands().commitCommand();    

    kernel->commands().undo();

    ASSERT_EQ(geometryCore->view()->topLevelPartLabels().size(), 0);
    ASSERT_EQ(geometryCore->view()->topLevelParts().size(), 0);
    ASSERT_EQ(geometryCore->view()->geometryObjects().size(), 0);
}

TEST_F(ImportSTEPTest, TestRedoImportCube) {
    using ::testing::_;
    using ::testing::Exactly;

    EXPECT_CALL(mockObserver, onPartAdded(_)).Times(Exactly(2));
    EXPECT_CALL(mockObserver, onPartRemoved(_)).Times(Exactly(1));
    
    geometryCore->events()->appendObserver(&mockObserver);
    
    std::shared_ptr<AbstractInputSource> source =
        std::make_shared<FileSource>(STEPFiles::singlePartCube());
    STEPImporter importer(source);

    kernel->commands().openCommand();    
    geometryCore->import(importer);
    kernel->commands().commitCommand();    
    kernel->commands().undo();
    
    kernel->commands().redo();

    ASSERT_EQ(geometryCore->view()->topLevelPartLabels().size(), 1);
    ASSERT_EQ(geometryCore->view()->topLevelParts().size(), 1);
    ASSERT_EQ(geometryCore->view()->geometryObjects().size(), 1);
}