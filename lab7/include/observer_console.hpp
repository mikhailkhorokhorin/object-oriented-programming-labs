#pragma once

#include <string>

#include "observer.hpp"
#include "thread_safe_cout.hpp"

class ConsoleLogger : public IObserver {
   public:
    void onEvent(const std::string& message) override;
};
