#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
private:
    std::string ip;
    int request_time_ms;
    int request_demand;
    long long expiration_time_ms;

public:
    Request();
    Request(const std::string& ip, int request_time_ms, int request_demand);

    std::string getIp() const;
    int getRequestTimeMs() const;
    int getRequestDemand() const;
    long long getExpirationTimeMs() const;

    static std::string generate_random_ip();
};

#endif
