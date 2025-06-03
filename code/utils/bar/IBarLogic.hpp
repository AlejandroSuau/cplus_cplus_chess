#pragma once

template <typename T>
class IBarLogic {
public:
    virtual ~IBarLogic() = default;
    virtual void Update(T delta) = 0;
    virtual void SetValue(T value) = 0;
    virtual void Reset() = 0;
    virtual T GetValue() const = 0;
    virtual T GetMax() const = 0;
    virtual float GetProgress() const = 0;
    virtual bool IsFull() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual bool DidFinish() const = 0;
};

