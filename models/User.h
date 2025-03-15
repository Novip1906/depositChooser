#pragma once
#include <string>

class User {
private:
    int id = 0;
    std::string name = "";
    std::string email = "";
    int salary = 0;
    bool broker = false;
    bool subscription = false;

public:
    User() = default;
    User(int id, std::string name, std::string email, int salary, bool broker, bool subscripton);
    void setName(std::string name) { this->name = name; };
    std::string getName() { return this->name; };

    void setEmail(std::string email) { this->email = email; };
    std::string getEmail() { return this->email; };

    void setSalary(int salary) { this->salary = salary; };
    int getSalary() { return this->salary; };

    void setBroker(bool broker) { this->broker = broker; };
    bool getBroker() { return this->subscription; };

    void setSubscription(bool sub) { this->subscription = sub; };
    bool getSubscription() { return this->subscription; };
};