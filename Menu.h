#pragma once

#include "models/User.h"
#include "models/Deposit.h"
#include <vector>
#include <map>
#include <string>
#include "server.h"
#include "UserDepositManager.h"
#include <iostream>

class BankSystem {
private:
    User user = {};
    std::vector<Deposit> deposits = {};
    std::string current_user_email = "";
    server::Server server = server::Server();

    void save_users_to_file();
    void load_users_from_file();
    void save_deposits_to_file();
    void load_deposits_from_file();

public:
BankSystem() = default;
BankSystem(server::Server& srv);
    bool isUser() {return user.getEmail() != ""; };
    bool register_user(const std::string &email, const std::string &name,
                     const std::string &password,
                     const std::string &repeat_password);
    bool login(const std::string &email, const std::string &password);
    void show_profile();
    void edit_profile(bool salary, bool broker, bool premium);
    //void create_deposit(double amount, int duration, bool replenishable);
    void show_user_deposits();
    void show_available_deposits();
    void logout();
    bool is_logged_in() const;
    void callAssistant();
    std::vector<Deposit> get_deposits() const;
    std::string hash_password(const std::string &password);
    bool is_valid_email(const std::string &email);
    std::vector<Deposit> load_available_deposits() {
        return UserDepositManager::getAvailableDeposits(user);
    }
};

void show_main_menu(BankSystem &bank);
void show_profile_menu(BankSystem &bank);
void show_deposit_menu(BankSystem &bank);
