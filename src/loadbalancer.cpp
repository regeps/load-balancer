#include "../header/loadbalancer.h"

Loadbalancer::Loadbalancer() {
    for (int i = 0; i < 10; ++i) {
        servers.push_back(Webserver());
    }
}

Loadbalancer::Loadbalancer(int number_of_servers) {
    for (int i = 0; i < number_of_servers; ++i) {
        servers.push_back(Webserver());
    }
}

void Loadbalancer::updateServers() {
    for (auto& server : servers) {
        server.remove_dead_connections();
    }
}

std::vector<Webserver>& Loadbalancer::getServers() {
    return servers;
}

int Loadbalancer::push(const Request& new_request) {
    if (servers.empty()) return 1;

    Webserver* best_server = &servers[0];

    for (auto& server : servers) {
        if (server.getCurrentUsage() < best_server->getCurrentUsage()) {
            best_server = &server;
        }
    }

    if (best_server->getCurrentUsage() + new_request.getRequestDemand() > best_server->getRequestCapacity()) {
        return 1;
    }

    best_server->push(new_request);
    return 0;
}

