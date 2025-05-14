#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "webserver.h"
#include <vector>

class Loadbalancer {
private:
    std::vector<Webserver> servers;

public:
    Loadbalancer();
    Loadbalancer(int number_of_servers);

    void updateServers(std::vector<Request>& request_queue, long long clock_ms);

    std::vector<Webserver>& getServers();
};

#endif
