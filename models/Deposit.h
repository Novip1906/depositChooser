#pragma once

#include <string>

class Deposit {
private:
  int id;
  std::string name;
  std::string description;
  int duration;
  int duration_max;
  double percent_min;
  double percent_max;
  double sum_min;
  bool req_salary;
  bool req_broker;
  bool req_premium;

public:
  Deposit() = default;
  Deposit(int id, const std::string &name, const std::string &description,
          int duration, int duration_max, double percent_min,
          double percent_max, double sum_min, bool req_salary, bool req_broker,
          bool req_premium)
      : id(id), name(name), description(description), duration(duration),
        duration_max(duration_max), percent_min(percent_min),
        percent_max(percent_max), sum_min(sum_min), req_salary(req_salary),
        req_broker(req_broker), req_premium(req_premium) {};

  int getId() const { return id; }
  std::string getName() const { return name; }
  std::string getDescription() const { return description; }
  int getDuration() const { return duration; }
  int getDurationMax() const { return duration_max; }
  double getMinPercent() const { return percent_min; }
  double getMaxPercent() const { return percent_max; }
  double getMinSum() const { return sum_min; }
  bool isReqSalary() const { return req_salary; }
  bool isReqBroker() const { return req_broker; }
  bool isReqPremium() const { return req_premium; }

  void setId(int id) { this->id = id; }
  void setName(const std::string &name) { this->name = name; }
  void setDescription(const std::string &description) { this->description = description; }
  void setDuration(int duration) { this->duration = duration; }
  void setDurationMax(int duration_max) { this->duration_max = duration_max; }
  void setMinPercent(double percent_min) { this->percent_min = percent_min; }
  void setMaxPercent(double percent_max) { this->percent_max = percent_max; }
  void setMinSum(double sum_min) { this->sum_min = sum_min; }
  void setReqSalary(bool req_salary) { this->req_salary = req_salary; }
  void setReqBroker(bool req_broker) { this->req_broker = req_broker; }
  void setReqPremium(bool req_premium) { this->req_premium = req_premium; }

  double calculateBet(const class Client &client,
                      bool withdrawProcents = false) const;
};
