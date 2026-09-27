#pragma once

#include <string>

#include "observer.hpp"
#include "synced_stream.hpp"

class ConsoleLogger final : public IObserver {
public:
    explicit ConsoleLogger(SyncedStream& output);

    void onEvent(const std::string& message) override;

private:
    SyncedStream* output_;
};
