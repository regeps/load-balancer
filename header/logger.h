#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>
#include "webserver.h"

namespace Logger {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string CYAN = "\033[36m";
    const std::string MAGENTA = "\033[35m";
    const std::string BLUE = "\033[34m";
    const std::string WHITE = "\033[37m";
    const std::string BOLD = "\033[1m";

    inline void log_status(const std::vector<Webserver>& servers, int total_requests_created, int total_requests_processed, const std::string& event = "") {
        int total_capacity = 0;
        int total_usage = 0;
        int total_active_requests = 0;

        for (const auto& server : servers) {
            total_capacity += server.getRequestCapacity();
            total_usage += server.getCurrentUsage();
            total_active_requests += server.getActiveClientCount();
        }

        double usage_percent = total_capacity > 0 ? ((double)total_usage / (double)total_capacity) * 100.0 : 0.0;

        // Color total usage
        if (usage_percent < 40.0)
            std::cout << GREEN;
        else if (usage_percent < 60.0)
            std::cout << CYAN;
        else if (usage_percent < 80.0)
            std::cout << YELLOW;
        else
            std::cout << RED;

        std::cout << "[Total Usage: " << (int)usage_percent << "%] ";
        std::cout << "[Active: " << total_active_requests << "] ";
        std::cout << "[Processed: " << total_requests_processed << "] " << RESET;

        // Per server usage with rich coloring
        for (size_t i = 0; i < servers.size(); ++i) {
            double server_usage_percent = (double)servers[i].getCurrentUsage() / (double)servers[i].getRequestCapacity() * 100.0;

            if (server_usage_percent < 10.0)
                std::cout << BLUE;        // Very light server load
            else if (server_usage_percent < 30.0)
                std::cout << GREEN;
            else if (server_usage_percent < 60.0)
                std::cout << CYAN;
            else if (server_usage_percent < 85.0)
                std::cout << YELLOW;
            else
                std::cout << RED;          // Danger zone server

            std::cout << "S" << i << ":" << (int)server_usage_percent << "%" << RESET << " ";
        }

        // Event logging
        if (!event.empty()) {
            std::cout << event;
        }

        std::cout << "\n";
    }
}

#endif
