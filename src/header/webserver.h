#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <random>
#include "scripts.h"

class Webserver {
private:
    std::string ip;
    int request_capacity;

public:
    Webserver();
    Webserver(const std::string& ip, int request_capacity);

    std::string getIp() const;
    int getRequestCapacity() const;
};

#endif