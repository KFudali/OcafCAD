#ifndef NamedSelectionAttribute_hpp
#define NamedSelectionAttribute_hpp

#include <TDataStd_GenericExtString.hxx>
#include <Standard_GUID.hxx>
#include <TCollection_ExtendedString.hxx>


class NamedSelectionAttribute;
DEFINE_STANDARD_HANDLE(NamedSelectionAttribute, TDataStd_GenericExtString)

class NamedSelectionAttribute : public TDataStd_GenericExtString
{
public:
  Standard_EXPORT static const Standard_GUID& GetID();
  Standard_EXPORT const Standard_GUID& ID() const Standard_OVERRIDE;
  Standard_EXPORT void SetName(const TCollection_ExtendedString& theName);
  Standard_EXPORT const TCollection_ExtendedString& GetName() const;

  Standard_EXPORT NamedSelectionAttribute();

  DEFINE_DERIVED_ATTRIBUTE(NamedSelectionAttribute, TDataStd_GenericExtString)
};

#endif // GeometryNamedSelectionAttribute_hpp

