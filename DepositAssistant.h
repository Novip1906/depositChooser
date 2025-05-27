#pragma once

#include "models/User.h"
#include "models/Deposit.h"
#include "Menu.h"
#include <vector>
#include <string>

class DepositAssistant {
private:
    BankSystem& bankSystem;
    // Вспомогательные методы
    double getRateForDuration(double newBet, int duration);
    void printOtherDurations(double newBet);
    int checkDuration(std::string& input);
    double checkSum(std::string& input);
    double calculateIncome(double sum, double bet, int duration);
    bool lookForOtherDurations(double& newBet);

    // Основные методы
    bool checkFirstAnswer(std::string& input, User& user,
                               const std::vector<Deposit>& availableDeposits,
                               double& sum, int& duration,
                               bool& withdrawProcents);
    void checkSecondAnswer(std::string& input, User& user,
                                const std::vector<Deposit>& availableDeposits,
                                double& sum, int& duration,
                                bool& withdrawProcents);
    void rechooseSumOrDuration(User& user, double& sum, int& duration,
                                    Deposit& recommendedDeposit, double& newBet,
                                    bool& withdrawProcents);
    bool showIfMenu(User& user, double sum,
                                        int duration, bool withdrawProcents,
                                        Deposit& recommendedDeposit, double newBet);
    void increaseInterestRate(const User& user) const;

public:
    explicit DepositAssistant(BankSystem& bank);
    void runAssistant(User& user,
                           const std::vector<Deposit>& availableDeposits);
    void DepositChoice(User& user,
                            const std::vector<Deposit>& availableDeposits);
};
                                        
