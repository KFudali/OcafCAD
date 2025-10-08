#ifndef StubOccDocument_hpp
#define StubOccDoucment_hpp

#include <Standard_Handle.hxx>
#include <XCAFApp_Application.hxx>
#include <TDocStd_Document.hxx>

class StubOccDocument {
    public: 
    Handle(TDocStd_Document) doc () {
        mApp = XCAFApp_Application::GetApplication();
        Handle(TDocStd_Document) doc;
        mApp->NewDocument("XmlXCAF", doc);
        mApp->InitDocument(doc);
        return doc;
    }

    private:
    Handle(XCAFApp_Application) mApp;
};

#endif