#ifndef StubImportDocuments_hpp
#define StubImportDocuments_hpp

#include "StubPartPrototypes.hpp"
#include "Location.hpp"

#include <XCAFApp_Application.hxx>
#include <XmlXCAFDrivers.hxx>

#include <XCAFDoc_DocumentTOol.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>

class BaseImportTestDoc {
	public:
	BaseImportTestDoc() {
        app = XCAFApp_Application::GetApplication();
        XmlXCAFDrivers::DefineFormat(app);
		app->NewDocument("XmlXCAF", doc);
		app->InitDocument(doc);
		shapeTool = XCAFDoc_DocumentTool::ShapeTool(doc->Main());
		colorTool = XCAFDoc_DocumentTool::ColorTool(doc->Main());
	}

	bool save(const std::string& aFilePath){
		TCollection_ExtendedString xmlPath(aFilePath.c_str());
		XmlXCAFDrivers::DefineFormat(app);
		if (app->SaveAs(doc, xmlPath) == PCDM_StoreStatus::PCDM_SS_OK) {
			return true;
		}
	}

    Handle(XCAFApp_Application) app;
	Handle(TDocStd_Document) doc;
	Handle(XCAFDoc_ShapeTool) shapeTool;
	Handle(XCAFDoc_ColorTool) colorTool;
};

class TwoAssembliesWithSamePrototypeDoc : public BaseImportTestDoc{
	public:
	TwoAssembliesWithSamePrototypeDoc(){
		mCubeProtoLabel = shapeTool->AddShape(StubPartPrototypes::cube());
		mAssemblyA = shapeTool->NewShape();
		mAssemblyB = shapeTool->NewShape();
		auto labelA = shapeTool->AddComponent(mAssemblyA, mCubeProtoLabel, Location());	
		auto labelB = shapeTool->AddComponent(mAssemblyB, mCubeProtoLabel, Location());	
		save("C:/Users/kryst/Documents/Repositories/OcafCAD/tests/unit/OcafKernel/DocumentImport/testDoc.cpp");
		labelA.IsNull();
		labelB.IsNull();
	};

	TDF_Label mAssemblyA;
	TDF_Label mAssemblyB;
	TDF_Label mCubeProtoLabel;
};

class TwoAssembliesWithSameSubAssembly : public BaseImportTestDoc{
	public:
	TwoAssembliesWithSameSubAssembly(){
		mCubeProtoLabel = shapeTool->AddShape(StubPartPrototypes::cube());
		auto subAssembly = shapeTool->NewShape();
		shapeTool->AddComponent(subAssembly, mCubeProtoLabel, Location());

		auto parentAssemblyA = shapeTool->NewShape();
		auto parentAssemblyB = shapeTool->NewShape();

		shapeTool->AddComponent(parentAssemblyA, subAssembly, Location());
		shapeTool->AddComponent(parentAssemblyB, subAssembly, Location());
	};

	TDF_Label mAssemblyA;
	TDF_Label mAssemblyB;
	TDF_Label mCubeProtoLabel;
};







#endif