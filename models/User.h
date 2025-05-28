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
  User(int id, std::string name, std::string email, int salary, bool broker,
       bool subscription)
      : id(id), name(name), email(email), salary(salary), broker(broker),
        subscription(subscription) {};

  void setName(std::string name) { this->name = name; };
  std::string getName() const { return this->name; };

  void setEmail(std::string email) { this->email = email; };
  std::string getEmail() const { return this->email; };

  void setSalary(int salary) { this->salary = salary; };
  int getSalary() const { return this->salary; };

  void setBroker(bool broker) { this->broker = broker; };
  bool getBroker() const { return this->broker; };

  void setSubscription(bool sub) { this->subscription = sub; };
  bool getSubscription() const { return this->subscription; };
};