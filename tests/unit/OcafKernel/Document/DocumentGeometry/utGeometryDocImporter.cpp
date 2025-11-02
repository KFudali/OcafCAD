#include <gmock/gmock.h>

#include "AbstractProgressPublisher.hpp"
#include "GeometryDocImporter.hpp"

#include "StubOccDocumentWithGeometry.hpp"
#include "StubOccDocument.hpp"
#include "DocumentGeometry.hpp"

using ::testing::Eq;
using ::testing::SizeIs;

class GeometryDocImporterTest : public ::testing::Test {
protected:
    void SetUp() override {
        dest = std::make_unique<DocumentGeometry>(mDoc.doc());
    }

    IdleProgressPublisher progress;
    std::unique_ptr<DocumentGeometry> dest;
    StubOccDocument mDoc;
};

TEST_F(GeometryDocImporterTest, ImportsAssemblyWithTwoPrototypes) {
    OneAssemblyWithTwoPrototypesDoc source;

    GeometryDocImporter::import(source.doc, *dest, progress);

    EXPECT_THAT(dest->prototypes(), SizeIs(3));

    auto freeParts = dest->freeParts();
    ASSERT_THAT(freeParts, SizeIs(1));

    Part assembly(freeParts[0]);
    EXPECT_TRUE(assembly.isAssembly());

    auto components = assembly.assembly().childrenComponents();
    ASSERT_THAT(components, SizeIs(2));

    EXPECT_TRUE(PartShapeTool(components[0]).shape().IsEqual(source.cube));
    EXPECT_TRUE(PartShapeTool(components[1]).shape().IsEqual(source.sphere));
}

TEST_F(GeometryDocImporterTest, ImportsTwoAssembliesWithSamePrototype) {
    TwoAssembliesWithSamePrototypeDoc source;

    GeometryDocImporter::import(source.doc, *dest, progress);

    EXPECT_THAT(dest->prototypes(), SizeIs(3));

    auto freeParts = dest->freeParts();
    ASSERT_THAT(freeParts, SizeIs(2));

    Part assemblyA(freeParts[0]);
    Part assemblyB(freeParts[1]);
    EXPECT_TRUE(assemblyA.isAssembly());
    EXPECT_TRUE(assemblyB.isAssembly());

    auto compsA = assemblyA.assembly().childrenComponents();
    auto compsB = assemblyB.assembly().childrenComponents();

    ASSERT_THAT(compsA, SizeIs(1));
    ASSERT_THAT(compsB, SizeIs(1));

    EXPECT_TRUE(PartShapeTool(compsA[0]).shape().IsEqual(source.cube));
    EXPECT_TRUE(PartShapeTool(compsB[0]).shape().IsEqual(source.cube));
}

TEST_F(GeometryDocImporterTest, ImportsTwoAssembliesWithSharedSubAssembly) {
    TwoAssembliesWithSameSubAssembly source;

    GeometryDocImporter::import(source.doc, *dest, progress);

    EXPECT_THAT(dest->prototypes(), SizeIs(3));
    ASSERT_THAT(dest->topLevelParts(), SizeIs(2));

    Part assemblyA(dest->topLevelParts()[0]);
    Part assemblyB(dest->topLevelParts()[1]);

    EXPECT_TRUE(assemblyA.isAssembly());
    EXPECT_TRUE(assemblyB.isAssembly());

    ASSERT_THAT(assemblyA.assembly().childrenComponents(), SizeIs(1));
    ASSERT_THAT(assemblyB.assembly().childrenComponents(), SizeIs(1));
}
