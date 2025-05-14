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

void Loadbalancer::updateServers(std::vector<Request>& request_queue, long long clock_ms) {
    for (auto& server : servers) {
        server.remove_dead_connections(clock_ms);
        server.process(clock_ms, request_queue);
    }

    if (request_queue.size() > 2 * servers.size()) {
        servers.push_back(Webserver());
    }

    if (servers.size() > 10) {
        servers.erase(std::remove_if(servers.begin(), servers.end(),
            [](const Webserver& ws) { return ws.isIdle(); }), servers.end());
    }
}

std::vector<Webserver>& Loadbalancer::getServers() {
    return servers;
}
