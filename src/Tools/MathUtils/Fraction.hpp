#ifndef Fraction_hpp
#define Fraction_hpp

#include <algorithm>
#include <cmath>
#include <compare>
#include <stdexcept>

class Fraction {
public:
    explicit Fraction(float value = 0.0f) { set(value); }

    void set(float value) {
        if (std::isnan(value) || std::isinf(value))
            throw std::invalid_argument("Fraction cannot be NaN or Inf");
        mValue = std::clamp(value, 0.0f, 1.0f);
    }

    float value() const { return mValue; }
    Fraction toGo() const { return Fraction(1.0f - mValue); }

    bool isZero(float eps = 1e-6f) const { return std::fabs(mValue) <= eps; }
    bool isOne(float eps = 1e-6f) const { return std::fabs(mValue - 1.0f) <= eps; }

    Fraction operator+(const Fraction& other) const { return Fraction(mValue + other.mValue); }
    Fraction operator-(const Fraction& other) const { return Fraction(mValue - other.mValue); }
    Fraction operator*(float scale) const { return Fraction(mValue * scale); }

    Fraction& operator+=(const Fraction& other) { set(mValue + other.mValue); return *this; }
    Fraction& operator-=(const Fraction& other) { set(mValue - other.mValue); return *this; }
    Fraction& operator*=(float scale) { set(mValue * scale); return *this; }

    auto operator<=>(const Fraction& other) const = default;

private:
    float mValue;
};

inline Fraction operator*(float lhs, const Fraction& rhs) { return rhs * lhs; }


#endif // Fraction_hpp
