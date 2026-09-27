#include "synced_stream.hpp"

SyncedStream::SyncedStream(std::ostream& os) : os_(&os) {
}

void SyncedStream::write(const std::string& text) {
    const std::lock_guard lock(mutex_);
    *os_ << text << std::flush;
}

void SyncedStream::writeLine(const std::string& line) {
    write(line + '\n');
}
