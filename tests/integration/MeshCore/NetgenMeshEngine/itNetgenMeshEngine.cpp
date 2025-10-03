#include "NetgenMeshEngine.hpp"
#include <gmock/gmock.h>

#include "StubMeshObjects.hpp"

class NetgenMeshEngineTest : public ::testing::Test {
    protected:
    void SetUp() {
        engine = std::make_unique<NetgenMeshEngine>();
        cubeObject = std::make_unique<MeshObject>(
            StubMeshObjects::cubeObject()
        );
        sphereObject = std::make_unique<MeshObject>(
            StubMeshObjects::sphereObject()
        );
    }
    std::unique_ptr<AbstractMeshEngine> engine;
    
    std::unique_ptr<MeshObject> cubeObject;
    std::unique_ptr<MeshObject> sphereObject;
};


TEST_F(NetgenMeshEngineTest, TestCubeSurfaceMeshing){
    auto result = engine->generateSurfaceMesh(*cubeObject);
    EXPECT_TRUE(result);
}