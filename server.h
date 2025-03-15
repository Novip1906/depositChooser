#pragma once

#include <vector>
#include <string>
#include "models/User.h"
#include "models/Deposit.h"

namespace server {
    class Server {
        private:
            std::string url;

        public:
            Server(std::string url) : url(url) {};

            template <class T = int>
            class Response {
            private:
                bool success;
                int code;
                T data;
            public:
                Response(bool success, int code, T data) : success(success), code(code), data(data) {};
            };
            
            Response<User> sign_up(std::string email, std::string name, std::string password);
            Response<User> sign_in(std::string email, std::string name, std::string password);
            Response<std::vector<Deposit>> get_deposits(double duration_min, double duration_max, double percent_min = 0, double percent_max = 1000, long long sum_min = 0, bool reqSalary = false, bool reqBroker = false, bool reqPremium = false);

    };
}