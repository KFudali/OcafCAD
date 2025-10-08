#ifndef StubAttribute_hpp
#define StubAttribute_hpp

#include <TDF_Attribute.hxx>
#include <Standard_Type.hxx>
#include <Standard_GUID.hxx>
#include <TDF_RelocationTable.hxx>

class StubAttribute;
DEFINE_STANDARD_HANDLE(StubAttribute, TDF_Attribute)

class StubAttribute : public TDF_Attribute {
public:
    DEFINE_STANDARD_RTTIEXT(StubAttribute, TDF_Attribute)

    StubAttribute() = default;
    ~StubAttribute() override = default;
    static Handle(StubAttribute) New() { return new StubAttribute(); }

    const Standard_GUID& ID() const override {
        static Standard_GUID guid("12345678-90AB-CDEF-1234-567890ABCDEF");
        return guid;
    }

    void Restore(const Handle(TDF_Attribute)&) override {}
    Handle(TDF_Attribute) NewEmpty() const override { return new StubAttribute; }
    void Paste(const Handle(TDF_Attribute)&, const Handle(TDF_RelocationTable)&) const override {}
};

#endif
