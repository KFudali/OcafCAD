#include <gmock/gmock.h>
#include <vector>

#include <occgeom.hpp>
#include <meshing.hpp>

#include <vtkType.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkIdTypeArray.h>

#include "MeshExtractionUtils.hpp"
#include "StubNetgenElems.hpp"

TEST(TestComputeOffsets, ReturnsCorrectOffsetsForMultipleElements) {
    auto elems = elems2D();
    vtkSmartPointer<vtkIdTypeArray> offsets = MeshExtractionUtils::computeOffsets(elems);
    
    std::vector<vtkIdType> expectedOffsets = {0, 3, 6, 10, 13};

    ASSERT_EQ(offsets->GetNumberOfValues(), static_cast<vtkIdType>(expectedOffsets.size()));
    for (vtkIdType i = 0; i < offsets->GetNumberOfValues(); ++i) {
        EXPECT_EQ(offsets->GetValue(i), expectedOffsets[i]);
    }
}

TEST(TestComputeOffsets, ReturnsCorrectOffsetsForEmptyInput) {
    Elem2DContainer elems(0);
    vtkSmartPointer<vtkIdTypeArray> offsets = MeshExtractionUtils::computeOffsets(elems);
    std::vector<vtkIdType> expectedOffsets = {0};

    ASSERT_EQ(offsets->GetNumberOfValues(), static_cast<vtkIdType>(expectedOffsets.size()));
    for (vtkIdType i = 0; i < offsets->GetNumberOfValues(); ++i) {
        EXPECT_EQ(offsets->GetValue(i), expectedOffsets[i]);
    }
}

TEST(TestComputeOffsets, ReturnsCorrectOffsetsForSingleElement) {
    netgen::Element2d elem(1, 2, 3);
    Elem2DContainer elems(1);
    elems[0] = elem;
    vtkSmartPointer<vtkIdTypeArray> offsets = MeshExtractionUtils::computeOffsets(elems);
    std::vector<vtkIdType> expectedOffsets = {0, 3};

    ASSERT_EQ(offsets->GetNumberOfValues(), static_cast<vtkIdType>(expectedOffsets.size()));
    for (vtkIdType i = 0; i < offsets->GetNumberOfValues(); ++i) {
        EXPECT_EQ(offsets->GetValue(i), expectedOffsets[i]);
    }
}
