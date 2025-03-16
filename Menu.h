#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "User.h"
#include "Deposit.h"

namespace BankSystem {

    std::string hash_password(const std::string& password);
    bool is_valid_email(const std::string& email);

    // Класс для управления пользователями и вкладами
    class BankSystem {
    private:
        std::map<std::string, User> users;  // Хранение пользователей по email
        std::vector<Deposit> deposits;      // Список вкладов
        std::string current_user_email;     // Email текущего пользователя

    public:
        BankSystem();
        bool register_user(const std::string& email, const std::string& name, const std::string& password, const std::string& repeat_password);
        bool login(const std::string& email, const std::string& password);
        void show_profile();
        void edit_profile(int salary, bool broker, bool subscription);
        void create_deposit(const std::string& name, const std::string& description, int duration, int duration_max, double percent_min, double percent_max, double sum_min, bool req_salary, bool req_broker, bool req_premium);
        void show_user_deposits();
        void show_available_deposits();
        void logout();
        bool is_logged_in() const;
    };

    void show_main_menu(BankSystem& bank);
    void show_profile_menu(BankSystem& bank);
    void show_deposit_menu(BankSystem& bank);
}
