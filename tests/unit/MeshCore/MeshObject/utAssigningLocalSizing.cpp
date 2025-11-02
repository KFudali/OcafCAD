#include <gmock/gmock.h>

#include "MeshObject.hpp"
#include "StubMeshObjects.hpp"

class MeshObjectTest : public ::testing::Test {
    protected:
    void SetUp () {
        cubeObject = std::make_unique<MeshObject>(StubMeshObjects::cubeObject());
    }
    
    std::unique_ptr<MeshObject> cubeObject;
};

TEST_F(MeshObjectTest, AssignLocalMeshSizing) {

    auto faceIdList = cubeObject->geometry().faces();
    SubShapeId faceId = SubShapeId(
        faceIdList.idsInParent[0], faceIdList.shapeType
    );
    cubeObject->localSettings().addFaceSizing(faceId, 0.1, 1.);
}