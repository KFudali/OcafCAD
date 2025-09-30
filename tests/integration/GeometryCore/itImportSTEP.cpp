#include "GeometryCore.hpp"
#include "STEPImporter.hpp"
#include "StubSTEPFileSources.hpp"

#include <gmock/gmock.h>

class MockGeometryObserver : public GeometryObserver {
public:
    MOCK_METHOD(void, onPartAdded, (const DocLabel& aLabel), (override));
    MOCK_METHOD(void, onPartRemoved, (const DocLabel& aLabel), (override));
    MOCK_METHOD(void, onPartModified, (), (override));
    MOCK_METHOD(void, onComponentAddedToAssembly, (const DocLabel& aLabel), (override));
    MOCK_METHOD(void, onComponentRemovedFromAssembly, (const DocLabel& aLabel), (override));
};

class GeometryCoreImportSTEPIntegrationTest : public ::testing::Test {
    protected:
    void SetUp() {
        core = std::make_unique<GeometryCore>();
    }
    std::unique_ptr<GeometryCore> core;
};

TEST_F(GeometryCoreImportSTEPIntegrationTest, TestImportCube) {
    using ::testing::_;
    using ::testing::Exactly;

    auto mockObserver = std::make_unique<MockGeometryObserver>();

    EXPECT_CALL(*mockObserver, onPartAdded(_)).Times(Exactly(1));
    core->events()->appendObserver(mockObserver.get());

    std::shared_ptr<AbstractInputSource> source =
        std::make_shared<FileSource>(StubSTEPFileSources::singlePartCube());
    STEPImporter importer(source);

    core->import(importer);
    ASSERT_EQ(core->view()->topLevelPartLabels().size(), 1);
}