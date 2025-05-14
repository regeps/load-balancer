#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
private:
    std::string ip_in;
    std::string ip_out;
    int request_time_ms;
    int request_demand;
    long long expiration_time_ms;
    char job_type; 

public:
    Request(int request_coefficient, long long clock_ms);

    std::string getIpIn() const;
    std::string getIpOut() const;
    int getRequestTimeMs() const;
    int getRequestDemand() const;
    long long getExpirationTimeMs() const;
    char getJobType() const;

    static std::string generate_random_ip();
};

#endif
