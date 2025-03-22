#include "server.h"
#include <cpr/cpr.h>
#include <iostream>
#include <sstream>
#include "json.hpp"
#include "models/User.h"
#include "models/Deposit.h"

using json = nlohmann::json;

namespace server {

    void Server::load_token() {
        std::ifstream file(tokenFilename);
        if (file.is_open()) {
            std::getline(file, token);
            file.close();
        }
    }
    void Server::save_token() {
        std::ofstream file(tokenFilename);
        if (file.is_open()) {
            file << token;
            file.close();
        }
    }

    Server::Response<User> Server::sign_up(const std::string& email, const std::string& name, const std::string& password) {
        try {
            json requestBody = {
                {"email", email},
                {"name", name},
                {"password", password}
            };
    
            auto r = cpr::Post(
                cpr::Url{url + "/sign_up"},
                cpr::Header{{"Content-Type", "application/json"}},
                cpr::Body{requestBody.dump()}
            );
        
            if (r.status_code == 200) {
                json jResponse = json::parse(r.text);

                if (jResponse["code"] == 0) {
                    json jUser = jResponse["data"]["user"];
                    set_token(jResponse["data"]["auth_token"]);
                    User user(
                        jUser["id"],
                        jUser["name"],
                        jUser["email"],
                        jUser["salary"],
                        jUser["broker"],
                        jUser["sub"]
                    );
                    return Response<User>(true, jResponse["code"], user);
                } else {
                    return Response<User>(true, jResponse["code"], User());
                }
            } else {
                return Response<User>(false, r.status_code, User());
            }
        } catch (const std::exception& e) {
            std::cerr << "Server error occurred: " << e.what() << std::endl;
            return Response<User>(false, 500, User());
        }
    }

    Server::Response<User> Server::sign_in(const std::string& email, const std::string& password) {
        try {
            json requestBody = {
                {"email", email},
                {"password", password}
            };
    
            auto r = cpr::Post(
                cpr::Url{url + "/sign_in"},
                cpr::Header{{"Content-Type", "application/json"}},
                cpr::Body{requestBody.dump()}
            );
        
            if (r.status_code == 200) {
                json jResponse = json::parse(r.text);

                if (jResponse["code"] == 0) {
                    json jUser = jResponse["data"]["user"];
                    set_token(jResponse["data"]["auth_token"]);
                    User user(
                        jUser["id"],
                        jUser["name"],
                        jUser["email"],
                        jUser["salary"],
                        jUser["broker"],
                        jUser["sub"]
                    );
                    return Response<User>(true, jResponse["code"], user);
                } else {
                    return Response<User>(true, jResponse["code"], User());
                }
            } else {
                return Response<User>(false, r.status_code, User());
            }
        } catch (const std::exception& e) {
            std::cerr << "Server error occurred: " << e.what() << std::endl;
            return Response<User>(false, 500, User());
        }
    }

    Server::Response<std::vector<Deposit>> Server::get_deposits(double duration_min, double duration_max, double percent_min, double percent_max, long long sum_min, bool reqSalary, bool reqBroker, bool reqPremium) {
        try {
            auto r = cpr::Get(
                cpr::Url{url + "/get_deposits"},
                cpr::Header{{"Content-Type", "application/json"}},
                cpr::Parameters({
                    {"duration_min", std::to_string(duration_min)},
                    {"duration_max", std::to_string(duration_max)},
                    {"percent_min", std::to_string(percent_min)},
                    {"percent_max", std::to_string(percent_max)},
                    {"sum_min", std::to_string(sum_min)},
                    {"req_salary", reqSalary ? "true" : "false"},
                    {"req_broker", reqBroker ? "true" : "false"},
                    {"req_premium", reqPremium ? "true" : "false"}
                })
            );
            if (r.status_code == 200) {
                json jResponse = json::parse(r.text);
                std::vector<Deposit> deposits;
                for (auto jDeposit : jResponse["data"]) {
                    deposits.push_back(Deposit(jDeposit["id"], jDeposit["name"], jDeposit["description"], jDeposit["duration_min"], jDeposit["duration_max"], jDeposit["percent_min"], jDeposit["percent_max"], jDeposit["sum_min"], jDeposit["req_salary"], jDeposit["req_broker"], jDeposit["req_premium"]));
                }
                return Response<std::vector<Deposit>>(true, jResponse["code"], deposits);
            } else {
                return Response<std::vector<Deposit>>(false, r.status_code, std::vector<Deposit>());
            }
        }
        catch(const std::exception& e) {
            std::cerr << "Server error occurred: " << e.what() << std::endl;
            return Response<std::vector<Deposit>>(false, 500, std::vector<Deposit>());
        }
    }

    Server::Response<User> Server::load_user() {
        try {
            auto r = cpr::Get(
                cpr::Url{url + "/get_user"},
                cpr::Header{{"Authorization", "Bearer " + token}}
            );
    
            if (r.status_code == 200) {
                json jResponse = json::parse(r.text);
                if (jResponse["code"] == 0) {
                    json user = jResponse["data"];
                    return Response<User>(true, 0, User(
                        user["id"],
                        user["name"],
                        user["email"],
                        user["salary"],
                        user["broker"],
                        user["sub"]
                    ));
                } else {
                    return Response<User>(true, 1, User());
                }
            } else {
                return Response<User>(false, r.status_code, User());
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Server error occurred: " << e.what() << std::endl;
            return Response<User>(false, 500, User());
        }
    }
    
    Server::Response<> Server::save_user(const User& user) {
        try {

            json requestBody = {
                {"name", user.getName()},
                {"salary", user.getSalary()},
                {"broker", user.getBroker()},
                {"sub", user.getSubscription()}
            };

            auto r = cpr::Post(
                cpr::Url{url + "/update_user"},
                cpr::Header{{"Authorization", "Bearer " + token}, {"Content-Type", "application/json"}},
                cpr::Body{requestBody.dump()}
            );
    
            if (r.status_code == 200) {
                json jResponse = json::parse(r.text);
                return Response<>(true, jResponse["code"], 0);
            } else {
                return Response<>(false, r.status_code, 0);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Server error occurred: " << e.what() << std::endl;
            return Response<>(false, 500, 0);
        }
    }


    

}