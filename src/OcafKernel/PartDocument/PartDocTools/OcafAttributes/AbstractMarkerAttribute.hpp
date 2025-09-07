#ifndef AbstractMarkerAttribute_hpp
#define AbstractMarkerAttribute_hpp

#include <TDF_Attribute.hxx>
#include <Standard_Handle.hxx>
#include <Standard_GUID.hxx>

class AbstractMarkerAttribute;
DEFINE_STANDARD_HANDLE(AbstractMarkerAttribute, TDF_Attribute)

/**
 * Empty base attribute that does nothing.
 * Derived classes only need to override GetID() to provide a unique GUID.
 */
class AbstractMarkerAttribute : public TDF_Attribute {
  DEFINE_STANDARD_RTTIEXT(AbstractMarkerAttribute, TDF_Attribute)
public:
  AbstractMarkerAttribute() = default;
  virtual ~AbstractMarkerAttribute() = default;

  //! Each derived class must provide its own GUID
  static const Standard_GUID& GetID();

  //! Returns the class GUID
  const Standard_GUID& ID() const override = 0;

  //! Boilerplate OCAF methods (no payload to copy/restore)
  Handle(TDF_Attribute) NewEmpty() const = 0;

  void Restore(const Handle(TDF_Attribute)& /*from*/) override {}
  void Paste(const Handle(TDF_Attribute)& /*into*/,
             const Handle(TDF_RelocationTable)& /*reloc*/) const override {}
};

#endif
