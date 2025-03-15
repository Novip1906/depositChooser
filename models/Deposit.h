#pragma once

#include <string>

class Deposit {
    private:
        std::string name;
        double bet;
        int duration;
        std::string description;
        double percent_max;
        double percent_min;
        double sum_min;
    public:
        std::string getName() const { return name; }
        double getBet() const { return bet; }
        int getDuration() const { return duration; }
        std::string getDescription() const { return description; }
        double getMaxPercent() const {return percent_max; }
        double getMinPercent() const {return percent_min; }
        double getMinSum() const { return sum_min; }

        void setName(const std::string& n) { name = n; }
        void setBet(double b) { bet = b; }
        void setDuration(int d) { duration = d; }
        void setDescription(const std::string& des) { description = des; }
        void setMaxPercent(double p_max) { percent_max = p_max; }
        void setMinPercent(double p_min) { percent_min = p_min; }
        void setMinSum(int s) { sum_min = s; }

        double calculateBet(const class Client& client, bool withdrawProcents = false) const;
};
