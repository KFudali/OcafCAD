#include <gtest/gtest.h>
#include "Fraction.hpp"

TEST(FractionTest, ConstructionAndClamp) {
    Fraction f1;
    EXPECT_FLOAT_EQ(f1.value(), 0.0f);
    EXPECT_TRUE(f1.isZero());

    Fraction f2(0.5f);
    EXPECT_FLOAT_EQ(f2.value(), 0.5f);

    Fraction f3(-1.0f);
    EXPECT_FLOAT_EQ(f3.value(), 0.0f);
    EXPECT_TRUE(f3.isZero());

    Fraction f4(2.0f);
    EXPECT_FLOAT_EQ(f4.value(), 1.0f);
    EXPECT_TRUE(f4.isOne());

    EXPECT_THROW(Fraction(NAN), std::invalid_argument);
    EXPECT_THROW(Fraction(INFINITY), std::invalid_argument);
}

TEST(FractionTest, Set) {
    Fraction f(0.3f);
    f.set(0.7f);
    EXPECT_FLOAT_EQ(f.value(), 0.7f);

    f.set(-1.0f);
    EXPECT_TRUE(f.isZero());

    f.set(2.0f);
    EXPECT_TRUE(f.isOne());
}

TEST(FractionTest, ToGo) {
    Fraction f(0.3f);
    EXPECT_FLOAT_EQ(f.toGo().value(), 0.7f);

    f.set(-1.0f);
    EXPECT_FLOAT_EQ(f.toGo().value(), 1.0f);

    f.set(2.0f);
    EXPECT_FLOAT_EQ(f.toGo().value(), 0.0f);
}


TEST(FractionTest, ArithmeticOperators) {
    Fraction f1(0.3f);
    Fraction f2(0.5f);

    Fraction f3 = f1 + f2;
    EXPECT_FLOAT_EQ(f3.value(), 0.8f);

    Fraction f4 = f2 - f1;
    EXPECT_FLOAT_EQ(f4.value(), 0.2f);

    Fraction f5 = f1 * 2.0f;
    EXPECT_FLOAT_EQ(f5.value(), 0.6f);

    Fraction f6(0.9f);
    f6 += Fraction(0.2f);
    EXPECT_FLOAT_EQ(f6.value(), 1.0f);

    Fraction f7(0.5f);
    f7 -= Fraction(0.6f);
    EXPECT_FLOAT_EQ(f7.value(), 0.0f);

    Fraction f8(0.4f);
    f8 *= 3.0f;
    EXPECT_FLOAT_EQ(f8.value(), 1.0f);
}

TEST(FractionTest, ComparisonOperators) {
    Fraction f1(0.3f);
    Fraction f2(0.7f);

    EXPECT_LT(f1, f2);
    EXPECT_LE(f1, f2);
    EXPECT_GT(f2, f1);
    EXPECT_GE(f2, f1);
    EXPECT_NE(f1, f2);
    EXPECT_EQ(f1, Fraction(0.3f));
}

TEST(FractionTest, HelperFunctions) {
    Fraction f1(0.0f);
    EXPECT_TRUE(f1.isZero());
    EXPECT_FALSE(f1.isOne());

    Fraction f2(1.0f);
    EXPECT_TRUE(f2.isOne());
    EXPECT_FALSE(f2.isZero());

    Fraction f3(0.000001f);
    EXPECT_TRUE(f3.isZero(1e-5f));
}

TEST(FractionTest, FloatMultiplication) {
    Fraction f1(0.4f);
    Fraction f2 = 2.0f * f1;
    EXPECT_FLOAT_EQ(f2.value(), 0.8f);

    Fraction f3 = f1 * 3.0f;
    EXPECT_FLOAT_EQ(f3.value(), 1.0f);
}



