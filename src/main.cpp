#include "../header/main.h"
#include "../header/loadbalancer.h"
#include "../header/request.h"
#include "../src/logger.h"

#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <iostream>

void print_summary(Loadbalancer& lb, const std::vector<Request>& request_queue, int iteration) {
    std::cout << Logger::MAGENTA << "\n=== SUMMARY AFTER " << iteration << " ITERATIONS ===\n" << Logger::RESET;
    const auto& servers = lb.getServers();
    
    for (size_t i = 0; i < servers.size(); ++i) {
        double usage_percent = (double)servers[i].getCurrentUsage() / (double)servers[i].getRequestCapacity() * 100.0;
        std::cout << "Server " << i << ": " 
                  << servers[i].getCurrentUsage() << "/" 
                  << servers[i].getRequestCapacity()
                  << " (" << (int)usage_percent << "%)" << "\n";
    }

    std::cout << "Pending requests in queue: " << request_queue.size() << "\n";
    std::cout << "===============================\n\n";
}

int main() {
    Loadbalancer lb(10); // 10 servers
    std::vector<Request> request_queue;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> request_chance(0, 100);

    int max_queue_size = lb.getServers().size() * 20;
    int iteration = 0;

    while (true) {
        if (request_chance(gen) < 30) {
            if (request_queue.size() < max_queue_size) {
                Request r;
                request_queue.push_back(r);
                Logger::log_request_added(r.getIp());
            }
        }

        if (!request_queue.empty()) {
            Request& next_request = request_queue.front();
            int result = lb.push(next_request);

            if (result == 0) {
                Logger::log_request_completed(next_request.getIp());
                request_queue.erase(request_queue.begin());
            }
        }

        lb.updateServers(); // remove dead connections

        if (++iteration % 1000 == 0) {
            print_summary(lb, request_queue, iteration);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}
