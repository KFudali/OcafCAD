#include <gmock/gmock.h>

#include "SurfaceExtraction.hpp"
#include "StubNetgenElems.hpp"

TEST(TestComputeConnectivity, ReturnsCorrectConnectivityForSingleElement) {
    auto elems = elems2D();

    vtkSmartPointer<vtkIdTypeArray> offsets = vtkSmartPointer<vtkIdTypeArray>::New();
    offsets->SetNumberOfValues(5);
    offsets->SetValue(0, 0);
    offsets->SetValue(1, 3);
    offsets->SetValue(2, 6);
    offsets->SetValue(3, 10);
    offsets->SetValue(4, 13);

    vtkSmartPointer<vtkIdTypeArray> conn = MeshExtractionUtils::computeConn(elems, offsets);

    std::vector<vtkIdType> expectedConn = {0, 1, 2, 5, 7, 2, 3, 4, 6, 7, 5, 6, 8};

    ASSERT_EQ(conn->GetNumberOfValues(), static_cast<vtkIdType>(expectedConn.size()));
    for (vtkIdType i = 0; i < conn->GetNumberOfValues(); ++i) {
        EXPECT_EQ(conn->GetValue(i), expectedConn[i]);
    }
}

TEST(TestExtractPoints, ExtractedPointsContainerHasAllMeshPoints) {
    std::vector<netgen::Point3d> expectedPoints;
    vtkSmartPointer<vtkPoints> points;
    {
        auto mesh = std::make_shared<netgen::Mesh>();
        for(double i = 0.001; i < 10.0; i += 1.001) {
            netgen::Point3d p(i, i, i);
            mesh->AddPoint(p);
            expectedPoints.push_back(p);
        }
        points = MeshExtractionUtils::extractPoints(mesh);
    }
    ASSERT_EQ(points->GetNumberOfPoints(), 10);
    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
        double coords[3];
        points->GetPoint(i, coords);

        double expected = 0.001 + static_cast<double>(i) * 1.001;

        EXPECT_NEAR(coords[0], expected, 1e-9);
        EXPECT_NEAR(coords[1], expected, 1e-9);
        EXPECT_NEAR(coords[2], expected, 1e-9);
    }
}
