#pragma once

#include <cmath>

#include "IBarLogic.hpp"

template <typename T>
class GenericBarLogic : public IBarLogic<T> {
public:
    GenericBarLogic(T max, T initial_value) 
        : max_(max)
        , value_(initial_value) {}
    
    ~GenericBarLogic() = default;

    void SetValue(T value) override {
        value_ = std::clamp(value, static_cast<T>(0), max_);
    }

    T GetValue() const override { return value_; }
    T GetMax() const override { return max_; }

    float GetProgress() const override {
        return static_cast<float>(value_) / static_cast<float>(max_);
    }

    bool IsFull() const override { return value_ >= max_; }
    bool IsEmpty() const override { return value_ <= static_cast<T>(0); }

private:
    T max_;
    T value_;
};

template <typename T>
class IncreasingBarLogic : public GenericBarLogic<T> {
public:
    // The compiler doesn't search in the base class automatically because it is a template.
    using GenericBarLogic<T>::GetValue;
    using GenericBarLogic<T>::GetMax;
    using GenericBarLogic<T>::SetValue;

    IncreasingBarLogic(T max_value) 
        : GenericBarLogic<T>(max_value, static_cast<T>(0)) {}
    
    void Update(float delta) override {
        SetValue(
            std::clamp(GetValue() + delta, static_cast<T>(0), GetMax()));
    }

    void Reset() override {
        SetValue(static_cast<T>(0));
    }

    bool DidFinish() const override {
        return (GetValue() >= GetMax());
    }
};


template <typename T>
class DecreasingBarLogic : public GenericBarLogic<T> {
public:
    // The compiler doesn't search in the base class automatically because it is a template.
    using GenericBarLogic<T>::GetValue;
    using GenericBarLogic<T>::GetMax;
    using GenericBarLogic<T>::SetValue;

    DecreasingBarLogic(T max_value) 
        : GenericBarLogic<T>(max_value, max_value) {}
    
    void Update(float delta) override {
        SetValue(
            std::clamp(GetValue() - delta, static_cast<T>(0), GetMax()));
    }

    void Reset() override {
        SetValue(GetMax());
    }

    bool DidFinish() const override {
        return (GetValue() <= static_cast<T>(0));
    }
};
/*
template <typename T>
std::unique_ptr<IBarLogic<T>> IncreasingBarLogic(T max_value) {
    return std::make_unique<IncreasingBarLogic<T>>(max_value);
}

template <typename T>
std::unique_ptr<IBarLogic<T>> DeceasingBarLogic(T max_value) {
    return std::make_unique<DeceasingBarLogic<T>>(max_value);
}*/

/*template <typename T>
std::unique_ptr<IBarLogic<T>> IncreasingBarLogic(T max_value) {
    const auto initial_value = static_cast<T>(0);
    return std::make_unique<GenericBarLogic<T>>(
        max_value,
        initial_value,
        [](T current, T delta) { return current + delta; },
        [initial_value]() { return initial_value; });
}

template <typename T>
std::unique_ptr<IBarLogic<T>> DecreasingBarLogic(T max_value) {
    return std::make_unique<GenericBarLogic<T>>(
        max_value,
        max_value,
        [](T current, T delta) { return current - delta; },
        [max_value]() { return max_value; });
}*/
