#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"
#include <vector>
#include <string>

class Webserver {
private:
    std::vector<Request> active_clients;
    std::string ip;
    int request_capacity;
    int current_usage;

public:
    Webserver();
    Webserver(const std::string& ip, int request_capacity);

    bool isIdle() const;
    void process(long long clock_ms, std::vector<Request>& request_queue);

    void remove_dead_connections(long long clock_ms);

    std::string generate_random_ip();
    std::string getIp() const;
    int getRequestCapacity() const;
    int getCurrentUsage() const;
    int getActiveClientCount() const;
};

#endif
