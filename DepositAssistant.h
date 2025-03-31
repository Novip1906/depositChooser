#pragma once

#include "models/User.h"
#include "models/Deposit.h"
#include <vector>
#include <string>

class DepositAssistant {
private:
    // Вспомогательные методы
    static double getRateForDuration(double newBet, int duration);
    static void printOtherDurations(double newBet);
    static int checkDuration(std::string& input);
    static double checkSum(std::string& input);
    static double calculateIncome(double sum, double bet, int duration);
    static bool lookForOtherDurations(double& newBet);

    // Основные методы
    static bool checkFirstAnswer(std::string& input, User& user,
                               const std::vector<Deposit>& availableDeposits,
                               double& sum, int& duration,
                               bool& withdrawProcents);
    static void checkSecondAnswer(std::string& input, User& user,
                                const std::vector<Deposit>& availableDeposits,
                                double& sum, int& duration,
                                bool& withdrawProcents);
    static void rechooseSumOrDuration(User& user, double& sum, int& duration,
                                    Deposit& recommendedDeposit, double& newBet,
                                    bool& withdrawProcents);
    static bool showIfMenu(User& user, double sum, int duration,
                         bool withdrawProcents, Deposit& recommendedDeposit,
                         double newBet);

public:
    static void runAssistant(User& user,
                           const std::vector<Deposit>& availableDeposits);
    static void DepositChoice(User& user,
                            const std::vector<Deposit>& availableDeposits);
};
