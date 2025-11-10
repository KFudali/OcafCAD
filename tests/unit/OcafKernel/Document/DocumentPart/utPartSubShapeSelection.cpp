#include <gtest/gtest.h>

#include "PartSubShapeSelection.hpp"

#include <XCAFApp_Application.hxx>
#include <TDocStd_Document.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelSequence.hxx>

#include <gtest/gtest.h>
#include "PartSubShapeSelection.hpp"

// class MockRefTreeLabel : public RefTreeLabel {
// public:
//     MockRefTreeLabel() : RefTreeLabel() {}

//     TDF_LabelSequence references() const override {
//         TDF_LabelSequence seq;
//         return seq;
//     }

//     bool appendReference(const TDF_Label&) override { return true; }
//     bool removeReference(const TDF_Label&) override { return true; }
// };

class PartSubShapeSelectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        app = XCAFApp_Application::GetApplication(); 
        app->NewDocument("XmlXCAF", doc);
        root = doc->Main().NewChild();
    }

    Handle(XCAFApp_Application) app;
    Handle(TDocStd_Document) doc;
    TDF_Label root;
};

TEST_F(PartSubShapeSelectionTest, TestTrue){
    EXPECT_TRUE(true);
}

// TEST_F(PartSubShapeSelectionTest, ConstructorWithLabelSequence) {
//     TDF_LabelSequence seq;
//     PartLabel partLabel;
//     PartSubShapeSelection sel(partLabel, root, seq);

//     ASSERT_NE(sel.label(), nullptr);
// }

// TEST_F(PartSubShapeSelectionTest, ConstructorWithRefTreeLabel) {
//     PartLabel partLabel;
//     MockRefTreeLabel mockLabel;
//     PartSubShapeSelection sel(partLabel, mockLabel);

//     ASSERT_NE(sel.label(), nullptr);
// }

// TEST_F(PartSubShapeSelectionTest, ClearLabel) {
//     TDF_LabelSequence seq;
//     PartLabel partLabel;
//     PartSubShapeSelection sel(partLabel, root, seq);

//     sel.clear();
// }

// TEST_F(PartSubShapeSelectionTest, AppendAndRemove) {
//     TDF_LabelSequence seq;
//     PartLabel partLabel;
//     PartSubShapeSelection sel(partLabel, root, seq);

//     SubShapeId id;
//     bool appended = sel.append(id);
//     bool removed = sel.remove(id);

//     ASSERT_TRUE(appended);
//     ASSERT_TRUE(removed);
// }