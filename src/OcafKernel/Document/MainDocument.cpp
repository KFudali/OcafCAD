#include "MainDocument.hpp"
#include <XmlDrivers.hxx>
#include <XmlXCAFDrivers.hxx>

MainDocument::MainDocument(Handle(XCAFApp_Application) aApp)
 : mApp(aApp) {
    mApp->NewDocument("XmlXCAF", mDoc);
    mApp->InitDocument(mDoc);
    mGeometry = std::make_unique<DocumentGeometry>(mDoc);
    mMesh = std::make_unique<DocumentMesh>();
}

bool MainDocument::save(const std::string& aSaveFilePath) const {
    TCollection_ExtendedString xmlPath(aSaveFilePath.c_str());
    XmlXCAFDrivers::DefineFormat(mApp);
    XmlDrivers::DefineFormat(mApp);
    if (mApp->SaveAs(mDoc, xmlPath) == PCDM_StoreStatus::PCDM_SS_OK) {
        return true;
    }
    return false;
}

