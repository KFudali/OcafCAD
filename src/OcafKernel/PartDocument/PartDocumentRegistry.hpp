#ifndef PartRegistry_hpp
#define PartRegistry_hpp

class PartDocumentView{
    public:
    const PartView part(const PartId& aPartId) const = 0;
    std::vector<PartId> freePartsIdList() const = 0;
    std::vector<PartId> allPartsIdList() const = 0;
}


class PartDocumentRegistry {
    public:
    bool importDocument(const PartDocument& aPartDocument) = 0;

    Part createFreePart(const PartPrototype& aPartPrototype) = 0;
    Part createFreeAssembly(const PartPrototype& aPartPrototype) = 0;

    Part createFreeEmptyPart() = 0;
    Part createFreeEmptyAssembly() = 0;
    PartDocument exportDocument() const;

    PartDocumentView view() = 0;
};

#endif