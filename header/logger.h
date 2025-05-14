#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <vector>
#include "webserver.h"

namespace Logger {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string CYAN = "\033[36m";
    const std::string YELLOW = "\033[33m";
    const std::string MAGENTA = "\033[35m";
    const std::string BOLD = "\033[1m";

    inline void log_request_added(const std::string& ip) {
        std::cout << GREEN << "[NEW REQUEST] " << RESET << ip << "\n";
    }

    inline void log_request_completed(const std::string& ip) {
        std::cout << RED << "[REQUEST COMPLETED] " << RESET << ip << "\n";
    }

    inline void log_server_loads(const std::vector<Webserver>& servers) {
        std::cout << CYAN << "[SERVER LOADS] " << RESET;
        for (size_t i = 0; i < servers.size(); ++i) {
            std::cout << YELLOW << "S" << i << ":" << servers[i].getCurrentUsage() << "/" << servers[i].getRequestCapacity() << RESET << " ";
        }
        std::cout << "\n";
    }
}

#endif
