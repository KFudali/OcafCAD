#ifndef StubPartDocument_hpp
#define StubPartDocument_hpp

#include <XCAFApp_Application.hxx>
#include <XmlXCAFDrivers.hxx>

#include "PartDocument.hpp"

namespace StubPartDocument {
    inline PartDocument partDocument() {
        auto app = XCAFApp_Application::GetApplication();
        XmlXCAFDrivers::DefineFormat(app);
        return PartDocument(app);
    }
}

#endif