#ifndef GeometryNamedSelectionAttribute_hpp
#define GeometryNamedSelectionAttribute_hpp

#include <TDataStd_GenericExtString.hxx>
#include <Standard_GUID.hxx>
#include <TCollection_ExtendedString.hxx>


class GeometryNamedSelectionAttribute;
DEFINE_STANDARD_HANDLE(GeometryNamedSelectionAttribute, TDataStd_GenericExtString)

class GeometryNamedSelectionAttribute : public TDataStd_GenericExtString
{
public:
  Standard_EXPORT static const Standard_GUID& GetID();
  Standard_EXPORT const Standard_GUID& ID() const Standard_OVERRIDE;
  Standard_EXPORT void SetName(const TCollection_ExtendedString& theName);
  Standard_EXPORT const TCollection_ExtendedString& GetName() const;

  Standard_EXPORT GeometryNamedSelectionAttribute();

  DEFINE_DERIVED_ATTRIBUTE(GeometryNamedSelectionAttribute, TDataStd_GenericExtString)
};

#endif // GeometryNamedSelectionAttribute_hpp

