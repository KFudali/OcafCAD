#include "DocumentGeometryFixture.hpp"
#include "StubPartPrototypes.hpp"

#include "GeometryObject.hpp"
#include "MeshObject.hpp"
#include "MeshInput.hpp"
#include "Dim.hpp"

#include <gmock/gmock.h>

class MeshInputTest : public DocumentGeometryFixture {
    protected:
    void SetUp() {
        DocumentGeometryFixture::SetUp();
        auto cubeShapeLabel = geoDoc->addShape(cubeShape);
        auto cubePartLabel = geoDoc->addPart(cubeShapeLabel, Location());

        geoObject = std::make_shared<GeometryObject>(cubePartLabel);
        meshObject = std::make_unique<MeshObject>(geoObject);

        // input = std::make_unique<MeshInput>(
        //     meshObject->geometry().rootShape(),
        //     DomainId(1, Dim::D3)
        // );
    }

    std::unique_ptr<MeshInput> input;    
    Shape cubeShape = StubPartPrototypes::cube();
    
    std::shared_ptr<GeometryObject> geoObject;
    std::unique_ptr<MeshObject> meshObject;

};

TEST_F(MeshInputTest, TestTrue) {
    // input->applyNamedSelection();
}