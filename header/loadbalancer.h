#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include "webserver.h"

class Loadbalancer {
private:
    std::vector<Webserver> servers;

public:
    Loadbalancer();
    Loadbalancer(int number_of_servers);

    int push(const Request& new_request);
    void updateServers(); // move this to public

    std::vector<Webserver>& getServers();
};

#endif
