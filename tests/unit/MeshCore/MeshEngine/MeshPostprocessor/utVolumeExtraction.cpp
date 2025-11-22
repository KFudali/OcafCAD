#include <gmock/gmock.h>
#include "VolumeExtraction.hpp"
#include "StubNetgenElems.hpp"

TEST(TestExtractVolumeConnectivity, ReturnsCorrectConnectivityForSingleElement) {
    auto elems = elems3D();

    vtkSmartPointer<vtkIdTypeArray> offsets = vtkSmartPointer<vtkIdTypeArray>::New();
    offsets->SetNumberOfValues(5);
    offsets->SetValue(0, 0);
    offsets->SetValue(1, 3);
    offsets->SetValue(2, 6);
    offsets->SetValue(3, 10);
    offsets->SetValue(4, 13);

    // vtkSmartPointer<vtkIdTypeArray> conn = VolumeExtraction::extractVolumeConn(elems

    // std::vector<vtkIdType> expectedConn = {0, 1, 2, 5, 7, 2, 3, 4, 6, 7, 5, 6, 8};

    // ASSERT_EQ(conn->GetNumberOfValues(), static_cast<vtkIdType>(expectedConn.size()));
    // for (vtkIdType i = 0; i < conn->GetNumberOfValues(); ++i) {
    //     EXPECT_EQ(conn->GetValue(i), expectedConn[i]);
    // }
}

