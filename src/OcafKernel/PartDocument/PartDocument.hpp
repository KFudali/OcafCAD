#ifndef PartDocument_hpp
#define PartDocument_hpp

#include <StandardHandle.hxx>
#include <TDocStd_Document.hxx>

class PartDocument {
    public:
    PartDocument(Handle(TDocStd_Document) aDocument);
   
    std::unique_ptr<PartDocumentView> view() const;
    std::unique_ptr<PartDocumentRegistry> registry() const;
    Handle(TDocStd_Document) data();
    
    private:
    Handle(TDocStd_Document) mDocument;
    std::unique_ptr<PartDocumentView> mView;
    std::unique_ptr<PartDocumentRegistry> mRegistry;
};

#endif