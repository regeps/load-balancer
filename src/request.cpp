#include "../header/request.h"
#include <random>
#include <chrono>

int generate_request_time(int request_coefficient) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(100 * request_coefficient, 700 * request_coefficient);
    return distrib(gen);
}

int generate_request_demand() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(100, 800);
    return distrib(gen);
}

Request::Request(int request_coefficient, long long clock_ms) {
    this->ip_in = generate_random_ip();
    this->ip_out = generate_random_ip();
    this->request_time_ms = generate_request_time(request_coefficient);
    this->request_demand = generate_request_demand();
    this->expiration_time_ms = clock_ms + request_time_ms;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> job_type_dist(0, 1);
    this->job_type = (job_type_dist(gen) == 0) ? 'S' : 'P';
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

std::string Request::getIpIn() const {
    return ip_in;
}

std::string Request::getIpOut() const {
    return ip_out;
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

char Request::getJobType() const {
    return job_type;
}
