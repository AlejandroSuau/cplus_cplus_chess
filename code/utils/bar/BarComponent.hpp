#pragma once

#include <SDL2/SDL.h>

#include "utils/Vec2.hpp"
#include "utils/bar/IBarLogic.hpp"
#include "utils/bar/BarRenderer.hpp"

#include <memory>

template <typename T>
class BarComponent {
public:
    BarComponent(std::unique_ptr<IBarLogic<T>> logic, BarRenderer renderer)
        : logic_(std::move(logic)), renderer_(std::move(renderer)) {}
    
    void Update(T dt) {
        logic_->Update(dt);
        renderer_.UpdateVisual(logic_->GetProgress());
    }

    void Render(Renderer& renderer, SDL_Color bg, SDL_Color fill) {
        renderer_.Render(renderer, bg, fill);
    }

    void SetPosition(Vec2<float> pos) { renderer_.SetPosition(pos); }
    void Reset() { logic_->Reset(); }

    bool DidFinish() const { return logic_->DidFinish(); }
    bool IsFull() const { return logic_->IsFull(); }
    bool IsEmpty() const { return logic_->IsEmpty(); }

private:
    std::unique_ptr<IBarLogic<T>> logic_;
    BarRenderer renderer_;
};
