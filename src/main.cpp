#include "../header/main.h"
#include "../header/loadbalancer.h"
#include "../header/request.h"
#include "../header/logger.h"

#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include <thread>
#include <iostream>

int main() {
    int server_count;
    int request_coefficient;

    std::cout << "Enter number of servers (10-1000): ";
    std::cin >> server_count;
    if (server_count < 10 || server_count > 1000) server_count = 10;

    std::cout << "Enter the request load coefficient (1-20): ";
    std::cin >> request_coefficient;
    if (request_coefficient < 1 || request_coefficient > 20) request_coefficient = 10;

    std::unordered_set<std::string> blocked_ips;
    std::ifstream input_file("blocked_ips.json");
    std::string line;
    while (std::getline(input_file, line)) {
        line.erase(0, line.find_first_not_of(" \t\n\r"));
        line.erase(line.find_last_not_of(" \t\n\r") + 1);
        if (line.empty() || line[0] != '\"') continue;
        if (line.back() == ',') line.pop_back();
        if (line.front() == '\"') line.erase(0, 1);
        if (line.back() == '\"') line.pop_back();
        blocked_ips.insert(line);
    }

    Loadbalancer lb(server_count);
    std::vector<Request> request_queue;
    std::vector<std::string> log_output;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> request_chance(0, 100);

    int max_queue_size = lb.getServers().size() * request_coefficient;
    int iteration = 0;
    int total_requests_created = 0;
    int total_requests_processed = 0;
    bool show_servers = server_count <= 10;
    long long clock_ms = 0;

    while (iteration < 10000) {
        std::string event = "";

        if (request_chance(gen) < 30) {
            if (request_queue.size() < max_queue_size) {
                Request r = Request(request_coefficient, clock_ms);
                if (blocked_ips.count(r.getIpIn()) > 0) {
                    std::cout << "[BLOCKED] " << r.getIpIn() << "\n";
                } else {
                    request_queue.push_back(r);
                    total_requests_created++;
                    event = Logger::GREEN + "[NEW " + r.getIpIn() + "]" + Logger::RESET;
                }
            }
        }

        int queue_before = request_queue.size();
        lb.updateServers(request_queue, clock_ms);
        int queue_after = request_queue.size();
        total_requests_processed += (queue_before - queue_after);

        std::ostringstream oss;
        std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());
        Logger::log_status(lb.getServers(), total_requests_created, total_requests_processed, event, show_servers);
        std::cout.rdbuf(old_buf);
        std::cout << oss.str();
        log_output.push_back(oss.str());

        iteration++;
        clock_ms++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::ofstream output_file("iterations.txt");
    for (const auto& line : log_output) {
        output_file << line;
    }
    output_file.close();

    std::cout << "Finished 10000 iterations. Log saved to iterations.txt.\n";

    return 0;
}
