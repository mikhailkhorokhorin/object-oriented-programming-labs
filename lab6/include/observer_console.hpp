#pragma once

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include "observer.hpp"

class ConsoleLogger : public IObserver {
   public:
    void onEvent(const std::string& msg) override;
};
