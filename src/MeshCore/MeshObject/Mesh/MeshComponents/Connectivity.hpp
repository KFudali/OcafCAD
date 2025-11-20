#ifndef Connectivity_hpp
#define Connectivity_hpp

#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkIdTypeArray.h>
#include <vtkUnsignedCharArray.h>
#include <vtkCellType.h>

struct Connectivity {
    Connectivity() = default;
    Connectivity(
        vtkSmartPointer<vtkCellArray> cells,
        vtkSmartPointer<vtkIdTypeArray> shapeIds,
        vtkSmartPointer<vtkIdTypeArray> domainIds
    ) : cells(cells), 
        shapeIds(shapeIds), 
        domainIds(domainIds){}
    virtual ~Connectivity() = default;

    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkIdTypeArray> shapeIds = vtkSmartPointer<vtkIdTypeArray>::New();
    vtkSmartPointer<vtkIdTypeArray> domainIds = vtkSmartPointer<vtkIdTypeArray>::New();
};

#endif
