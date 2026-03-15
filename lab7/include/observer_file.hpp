#pragma once

#include <fstream>
#include <mutex>
#include <string>

#include "observer.hpp"

class FileLogger : public IObserver {
   private:
    std::mutex mutex;

   public:
    void onEvent(const std::string& message) override;
};
