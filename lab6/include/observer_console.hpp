#pragma once

#include <iostream>
#include <string>

#include "observer.hpp"

class ConsoleLogger final : public IObserver {
public:
    explicit ConsoleLogger(std::ostream& os = std::cout);

    void onEvent(const std::string& message) override;

private:
    std::ostream* os_;
};
