#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <vector>
#include "request.h"

class Webserver {
private:
    std::vector<Request> active_clients;
    std::string ip;
    int request_capacity;
    int current_usage;

public:
    Webserver();
    Webserver(const std::string& ip, int request_capacity);

    void push(const Request& new_request);
    void remove_dead_connections();

    std::string getIp() const;
    int getRequestCapacity() const;
    int getCurrentUsage() const;

    static std::string generate_random_ip();
};

#endif
