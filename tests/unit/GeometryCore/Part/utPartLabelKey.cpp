#include <gtest/gtest.h>
#include "PartLabelKey.hpp"
#include <TColStd_ListOfInteger.hxx>

#include <ranges>
#include <tuple>

TEST(TestTrue, Test){
    EXPECT_TRUE(true);
}

TEST(PartLabelKeyTest, PartLabelKeyCanBeCreatedFromString){
    std::string tagListString = "0:4:2:4";
    PartLabelKey key(tagListString);

    EXPECT_EQ(key.toStdVector(), (std::vector<int>{0, 4, 2, 4}));

    tagListString = "0";
    key = PartLabelKey(tagListString);
    EXPECT_EQ(key.toStdVector(), std::vector<int>{0});
}

TEST(PartLabelKeyTest, PartLabelKeyCanBeCreatedFromOccList){
    TColStd_ListOfInteger tagList;
    tagList.Append(0);
    tagList.Append(4);
    tagList.Append(2);
    tagList.Append(4);
    PartLabelKey key(tagList);

    EXPECT_EQ(key.toStdVector(), (std::vector<int>{0, 4, 2, 4}));

    tagList.Clear();
    tagList.Append(0); 
    key = PartLabelKey(tagList);
    EXPECT_EQ(key.toStdVector(), std::vector<int>{0});
}

TEST(PartLabelKeyTest, PartLabelKeyToStringReturnsTagsSeparatedByDelis){
    PartLabelKey key({1,4,3,4});
    EXPECT_EQ(key.toString(), "1:4:3:4");

    key = PartLabelKey({0});
    EXPECT_EQ(key.toString(), "0");
}

TEST(PartLabelKeyTest, PartLabelKeyToOccListReturnsCorrectListOfTags){
    PartLabelKey key({1,4,3,4});
    auto tagList = key.toOccList();
    for(auto [vectorValue, tagListValue] : std::views::zip(tagList, key.toStdVector())){
        EXPECT_EQ(vectorValue, tagListValue);
    }
}