#ifndef RootAssemblyAttribute_hpp
#define RootAssemblyAttribute_hpp

#include <TDF_Attribute.hxx>
#include <Standard_Handle.hxx>
#include <Standard_GUID.hxx>

class RootAssemblyAttribute;
DEFINE_STANDARD_HANDLE(RootAssemblyAttribute, TDF_Attribute)
class RootAssemblyAttribute : public TDF_Attribute {
	DEFINE_STANDARD_RTTIEXT(RootAssemblyAttribute, TDF_Attribute)
	public:
	RootAssemblyAttribute() = default;
	virtual ~RootAssemblyAttribute() = default;

	static const Standard_GUID& GetID();
	const Standard_GUID& ID() const override;

	void Restore (const Handle(TDF_Attribute)& anAttribute) override;
	void Paste (
		const Handle(TDF_Attribute)& intoAttribute, 
		const Handle(TDF_RelocationTable)& aRelocationTable
	) const override;
	Handle(TDF_Attribute) NewEmpty() const override;
};

#endif