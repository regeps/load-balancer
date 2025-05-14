#include "../header/main.h"
#include "../header/loadbalancer.h"
#include "../header/request.h"
#include "../header/logger.h"

#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <iostream>

int main() {
    Loadbalancer lb(10);
    std::vector<Request> request_queue;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> request_chance(0, 100);

    int max_queue_size = lb.getServers().size() * 20;
    int iteration = 0;
    int total_requests_created = 0;
    int total_requests_processed = 0;

    while (true) {
        std::string event = "";

        if (request_chance(gen) < 30) {
            if (request_queue.size() < max_queue_size) {
                Request r;
                request_queue.push_back(r);
                total_requests_created++;
                event = Logger::GREEN + "[NEW " + r.getIp() + "]" + Logger::RESET;
            }
        }

        if (!request_queue.empty()) {
            Request& next_request = request_queue.front();
            int result = lb.push(next_request);

            if (result == 0) {
                total_requests_processed++;
                event = Logger::RED + "[DONE " + next_request.getIp() + "]" + Logger::RESET;
                request_queue.erase(request_queue.begin());
            }
        }

        lb.updateServers();

        Logger::log_status(lb.getServers(), total_requests_created, total_requests_processed, event);

        iteration++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}
