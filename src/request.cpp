#include "../header/request.h"
#include <random>
#include <chrono>

int generate_request_time() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(5, 1000);
    return distrib(gen);
}

int generate_request_demand() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(100, 1000);
    return distrib(gen);
}

long long get_current_time_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch()
           ).count();
}

Request::Request() {
    this->ip = generate_random_ip();
    this->request_time_ms = generate_request_time();
    this->request_demand = generate_request_demand();
    this->expiration_time_ms = get_current_time_ms() + request_time_ms;
}

Request::Request(const std::string& ip, int request_time_ms, int request_demand) {
    this->ip = ip;
    this->request_time_ms = request_time_ms;
    this->request_demand = request_demand;
    this->expiration_time_ms = get_current_time_ms() + request_time_ms;
}

std::string Request::getIp() const {
    return ip;
}

int Request::getRequestTimeMs() const {
    return request_time_ms;
}

int Request::getRequestDemand() const {
    return request_demand;
}

long long Request::getExpirationTimeMs() const {
    return expiration_time_ms;
}

std::string Request::generate_random_ip() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(0, 255);

    return std::to_string(distrib(gen)) + "." +
           std::to_string(distrib(gen)) + "." +
           std::to_string(distrib(gen)) + "." +
           std::to_string(distrib(gen));
}
