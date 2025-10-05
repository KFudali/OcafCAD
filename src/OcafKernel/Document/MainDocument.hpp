#ifndef MainDocument_hpp
#define MainDocument_hpp

#include "DocumentGeometry.hpp"
#include "DocumentMesh.hpp"

#include <Standard_Handle.hxx>
#include <XCAFApp_Application.hxx>
#include <TDocStd_Document.hxx>

class MainDocument {
    public:
    MainDocument(Handle(XCAFApp_Application) aApp);

    inline Handle(TDocStd_Document) data() const {return mDoc;}
    bool save(const std::string& aSaveFilePath) const;

    inline DocumentGeometry& geometry() const { return *mGeometry;}
    inline DocumentMesh& mesh() const { return *mMesh;}

    private:
    Handle(XCAFApp_Application) mApp;
    Handle(TDocStd_Document) mDoc;
    std::unique_ptr<DocumentGeometry> mGeometry;
    std::unique_ptr<DocumentMesh> mMesh;
};

#endif