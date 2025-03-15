#include "server.h"
#include <cpr/cpr.h>
#include <iostream>
#include "json.hpp"
#include "models/User.h"
#include "models/Deposit.h"

using json = nlohmann::json;

namespace server {

    Server::Response<User> Server::sign_up(std::string email, std::string name, std::string password) {
        auto r = cpr::Post(cpr::Url{url + "/sign_up"}, cpr::Payload{{"email", email}, {"name", name}, {"password", password}});

        json jResponse = json::parse(r.text);
    
        if (r.status_code == 200) {
            return Response<User>(true, jResponse["code"], User(jResponse["id"], jResponse["name"], jResponse["email"], jResponse["salary"], jResponse["broker"], jResponse["subscription"]));
        } else {
            return Response<User>(false, r.status_code, User());
        }
    }

    Server::Response<User> Server::sign_in(std::string email, std::string name, std::string password) {
        auto r = cpr::Post(cpr::Url{url + "/sign_in"}, cpr::Payload{{"email", email}, {"name", name}, {"password", password}});

        json jResponse = json::parse(r.text);
    
        if (r.status_code == 200) {
            return Response<User>(true, jResponse["code"], User(jResponse["id"], jResponse["name"], jResponse["email"], jResponse["salary"], jResponse["broker"], jResponse["subscription"]));
        } else {
            return Response<User>(false, r.status_code, User());
        }
    }

    Server::Response<std::vector<Deposit>> Server::get_deposits(double duration_min, double duration_max, double percent_min, double percent_max, long long sum_min, bool reqSalary, bool reqBroker, bool reqPremium) {
        auto r = cpr::Get(
            cpr::Url{url + "/get_deposits"},
            cpr::Parameters({
                {"duration_min", std::to_string(duration_min)},
                {"duration_max", std::to_string(duration_max)},
                {"percent_min", std::to_string(percent_min)},
                {"percent_max", std::to_string(percent_max)},
                {"sum_min", std::to_string(sum_min)},
                {"reqSalary", reqSalary ? "true" : "false"},
                {"reqBroker", reqBroker ? "true" : "false"},
                {"reqPremium", reqPremium ? "true" : "false"}
            })
        );
        if (r.status_code == 200) {
            json jResponse = json::parse(r.text);
            std::vector<Deposit> deposits;
            for (auto jDeposit : jResponse["data"]) {
                deposits.push_back(Deposit(jDeposit["id"], jDeposit["name"], jDeposit["description"], jDeposit["duration_min"], jDeposit["duration_max"], jDeposit["percent_min"], jDeposit["percent_max"], jDeposit["sum_min"], jDeposit["reqSalary"], jDeposit["reqBroker"], jDeposit["reqPremium"]));
            }
            return Response<std::vector<Deposit>>(true, 200, deposits);
        } else {
            return Response<std::vector<Deposit>>(false, r.status_code, std::vector<Deposit>());
        }
    }


    

}


int main() {
    cpr::Response r = cpr::Get(cpr::Url{"http://127.0.0.1:5000/get_deposits"});
    std::cout << "Status Code: " << r.status_code << std::endl;
    std::cout << "Response: " << r.text << std::endl;
    return 0;
}