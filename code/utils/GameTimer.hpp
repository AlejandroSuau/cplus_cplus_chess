#pragma once

#include <chrono>

class GameTimer {
public:
    GameTimer(float duration_in_millisecs) 
        : duration_in_millisecs_(duration_in_millisecs)
        , elapsed_time_in_millisecs_(0.f)
        , is_running_(false) {}

    void Start() {
        is_running_ = true;
        elapsed_time_in_millisecs_ = 0;
    }

    void Reset(bool is_running = false) {
        is_running_ = is_running;
        elapsed_time_in_millisecs_ = 0;
    }

    bool Update(float dt) {
        elapsed_time_in_millisecs_ += dt;
        const bool did_finish = DidFinish();
        if (did_finish) {
            Reset();
        }
        return did_finish;
    }

    float ElapsedTime() const { return elapsed_time_in_millisecs_; }
    bool DidFinish() const { return elapsed_time_in_millisecs_ >= duration_in_millisecs_; }
    bool IsRunning() const { return is_running_; }
    void SetDuration(float duration_in_millisecs) { duration_in_millisecs_ = duration_in_millisecs; }

private:
    float duration_in_millisecs_;
    float elapsed_time_in_millisecs_;
    bool is_running_;
};
