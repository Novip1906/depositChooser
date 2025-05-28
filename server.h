#pragma once

#include "models/Deposit.h"
#include "models/User.h"
#include <string>
#include <vector>

namespace server {

class Server {
private:
  std::string url = "";
  std::string token = "";
  std::string tokenFilename = "";

  void load_token();
  void save_token();
  void set_token(std::string token) {
    this->token = token;
    save_token();
  };

public:
  Server() = default;
  Server(std::string url) : url(url) {};
  Server(std::string url, std::string tokenFilename)
      : url(url), tokenFilename(tokenFilename) {
    load_token();
  };

  template <class T = int> class Response {
  private:
    bool success;
    int code;
    T data;

  public:
    Response(bool success, int code, T data)
        : success(success), code(code), data(data) {};

    T getData() const { return data; };
    int getCode() const { return code; };
    bool isSuccess() const { return success; }
  };

  std::string get_token() const { return token; };

  void sign_out() { set_token(""); };

  Response<User> sign_up(const std::string &email, const std::string &name,
                         const std::string &password);
  Response<User> sign_in(const std::string &email, const std::string &password);
  Response<std::vector<Deposit>>
  get_deposits(double duration_min = 1, double duration_max = 36,
               double percent_min = 0, double percent_max = 1000,
               long long sum_min = 0, bool reqSalary = false,
               bool reqBroker = false, bool reqPremium = false);
  Response<User> load_user();
  Response<> save_user(const User &user);
};
} // namespace server