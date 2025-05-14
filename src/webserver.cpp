#include "../header/webserver.h"
#include <random>
#include <chrono>

int generate_request_capacity() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(10000, 100000);
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

void Webserver::push(const Request& new_request) {
    for (auto& client : active_clients) {
        if (client.getRequestDemand() == 0) {
            client = new_request;
            current_usage += new_request.getRequestDemand();
            return;
        }
    }

    active_clients.push_back(new_request);
    current_usage += new_request.getRequestDemand();
}

void Webserver::remove_dead_connections() {
    long long now = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch()
                    ).count();
    
    for (auto it = active_clients.begin(); it != active_clients.end(); ) {
        if (it->getExpirationTimeMs() <= now) {
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
