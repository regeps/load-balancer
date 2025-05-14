#include "../header/webserver.h"

int generate_request_capacity() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(10000, 100000);
    return distrib(gen);
}

Webserver::Webserver() {
    this->ip = generate_random_ip();
    this->request_capacity = generate_request_capacity();
}

Webserver::Webserver(const std::string& ip, int request_capacity) {
    this->ip = ip;
    this->request_capacity = request_capacity;
}

std::string Webserver::getIp() const {
    return ip;
}

int Webserver::getRequestCapacity() const {
    return request_capacity;
}
