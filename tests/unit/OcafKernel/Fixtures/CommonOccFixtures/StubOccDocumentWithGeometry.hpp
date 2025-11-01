
#ifndef StubOccDocumentWithGeometry_hpp 
#define StubOccDocumentWithGeometry_hpp 

#include "StubPartPrototypes.hpp"
#include "Location.hpp"

#include <XCAFApp_Application.hxx>
#include <XmlXCAFDrivers.hxx>

#include <XCAFDoc_DocumentTOol.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>

class BaseOccDoc {
	public:
	BaseOccDoc() {
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
		return false;
	}

	Shape sphere = StubPartPrototypes::sphere();
	Shape cube = StubPartPrototypes::cube();
    Handle(XCAFApp_Application) app;
	Handle(TDocStd_Document) doc;
	Handle(XCAFDoc_ShapeTool) shapeTool;
	Handle(XCAFDoc_ColorTool) colorTool;
};

class OneAssemblyWithTwoPrototypesDoc : public BaseOccDoc{
	public:
	OneAssemblyWithTwoPrototypesDoc(){
		mCubeProtoLabel = shapeTool->AddShape(cube);
		mSphereProtoLabel = shapeTool->AddShape(sphere);
		mAssembly = shapeTool->NewShape();
		shapeTool->AddComponent(mAssembly, mCubeProtoLabel, Location());	
		shapeTool->AddComponent(mAssembly, mSphereProtoLabel, Location());	
	};

	TDF_Label mAssembly;
	TDF_Label mCubeProtoLabel;
	TDF_Label mSphereProtoLabel;
};

class TwoAssembliesWithSamePrototypeDoc : public BaseOccDoc{
	public:
	TwoAssembliesWithSamePrototypeDoc(){
		mCubeProtoLabel = shapeTool->AddShape(cube);
		mAssemblyA = shapeTool->NewShape();
		mAssemblyB = shapeTool->NewShape();
		auto labelA = shapeTool->AddComponent(mAssemblyA, mCubeProtoLabel, Location());	
		auto labelB = shapeTool->AddComponent(mAssemblyB, mCubeProtoLabel, Location());	
	};

	TDF_Label mAssemblyA;
	TDF_Label mAssemblyB;
	TDF_Label mCubeProtoLabel;
};

class TwoAssembliesWithSameSubAssembly : public BaseOccDoc{
	public:
	TwoAssembliesWithSameSubAssembly(){
		mCubeProtoLabel = shapeTool->AddShape(cube);
		mSphereProtoLabel = shapeTool->AddShape(sphere);
		
		auto subAssembly = shapeTool->NewShape();
		shapeTool->AddComponent(subAssembly, mCubeProtoLabel, Location());
		shapeTool->AddComponent(subAssembly, mSphereProtoLabel, Location());

		auto parentAssemblyA = shapeTool->NewShape();
		auto parentAssemblyB = shapeTool->NewShape();

		shapeTool->AddComponent(parentAssemblyA, subAssembly, Location());
		shapeTool->AddComponent(parentAssemblyB, subAssembly, Location());
	};

	TDF_Label sharedSubAssembly;
	TDF_Label mAssemblyA;
	TDF_Label mAssemblyB;
	TDF_Label mCubeProtoLabel;
	TDF_Label mSphereProtoLabel;
};







#endif