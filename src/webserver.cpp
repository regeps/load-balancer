#include "../header/webserver.h"
#include <random>
#include <chrono>

int generate_request_capacity() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(40000, 60000);
    return distrib(gen);
}

Webserver::Webserver() {
    this->ip = generate_random_ip();
    this->request_capacity = generate_request_capacity();
    this->current_usage = 0;
}

Webserver::Webserver(const std::string& ip, int request_capacity) {
    this->ip = ip;
    this->request_capacity = request_capacity;
    this->current_usage = 0;
}

bool Webserver::isIdle() const {
    return current_usage == 0;
}

void Webserver::process(long long clock_ms, std::vector<Request>& request_queue) {
    if (request_queue.empty()) return;

    Request& r = request_queue.front();
    if (current_usage + r.getRequestDemand() <= request_capacity) {
        active_clients.push_back(r);
        current_usage += r.getRequestDemand();
        request_queue.erase(request_queue.begin());
    }
}

void Webserver::remove_dead_connections(long long clock_ms) {
    for (auto it = active_clients.begin(); it != active_clients.end();) {
        if (it->getExpirationTimeMs() <= clock_ms) {
            current_usage -= it->getRequestDemand();
            it = active_clients.erase(it);
        } else {
            ++it;
        }
    }
}

std::string Webserver::generate_random_ip() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(0, 255);

    return std::to_string(distrib(gen)) + "." +
           std::to_string(distrib(gen)) + "." +
           std::to_string(distrib(gen)) + "." +
           std::to_string(distrib(gen));
}

std::string Webserver::getIp() const {
    return ip;
}

int Webserver::getRequestCapacity() const {
    return request_capacity;
}

int Webserver::getCurrentUsage() const {
    return current_usage;
}

int Webserver::getActiveClientCount() const {
    return active_clients.size();
}
