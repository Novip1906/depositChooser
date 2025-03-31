#include "DepositAssistant.h"
#include <cctype>
#include <iostream>
#include <limits>

void DepositAssistant::runAssistant(
    User &user, const std::vector<Deposit> &availableDeposits) {
  std::cout << "\nПривет! Меня зовут Вкладыш, и я виртуальный ассистент этого "
               "банка\n";
  std::cout
      << "Мне ещё многому предстоит научиться, а пока вот, что я умею:\n\n";
  std::cout << "1. Показать информацию о Вашем вкладе\n";
  std::cout << "2. Помочь подобрать идеальный вклад именно для Вас\n";
  std::cout << "0 - Выход\n";

  int choice;
  while (true) {
    std::cout << "Введите Ваш выбор (1-2, 0 - выход): ";
    std::cin >> choice;

    if (choice == 1) {
      std::cout << "Информация о вкладах...\n";
    } else if (choice == 2) {
      DepositChoice(user, availableDeposits);
    } else if (choice == 0) {
      std::cout << "Приятно было поболтать! Возвращаю Вас в основное меню\n";
      return;
    } else {
      std::cout << "Пожалуйста, введите 1, 2 или 0\n";
    }
  }
}

double DepositAssistant::getRateForDuration(double newBet, int duration) {
  if (duration == 1 || duration == 2) {
    return newBet - 3.0;
  } else if (duration == 5 || duration == 6) {
    return newBet;
  } else {
    return newBet - 1.0;
  }
}

void DepositAssistant::printOtherDurations(double newBet) {
  std::cout << "Срок | Ставка\n";
  std::cout << "---------------\n";

  for (int month = 1; month <= 12; ++month) {
    double rate;

    if (month == 1 || month == 2) {
      rate = newBet - 3.0;
    } else if (month == 5 || month == 6) {
      rate = newBet;
    } else {
      rate = newBet - 1.0;
    }

    if (month == 12) {
      std::cout << " 1 год | " << rate << "%\n";
    } else {
      std::cout << month << " мес. | " << rate << "%\n";
    }
  }

  std::cout << std::endl;
}

int DepositAssistant::checkDuration(std::string &input) {
  while (true) {
    if (input.empty()) {
      std::cerr << "Если хотите поменять срок, нужно всё-таки его ввести. Не "
                   "стесняйтесь и вводите!"
                << std::endl;
      std::getline(std::cin,
                   input); // Используем getline для чтения всей строки
      continue;
    }

    input.erase(0, input.find_first_not_of(' '));
    input.erase(input.find_last_not_of(' ') + 1);

    size_t spacePos = input.find(' ');
    if (spacePos != std::string::npos) {
      std::string numberPart = input.substr(0, spacePos);
      std::string unitPart = input.substr(spacePos + 1);

      // Проверяем, что первая часть — это число
      bool isNumber = true;
      for (char ch : numberPart) {
        if (!isdigit(ch)) {
          isNumber = false;
          break;
        }
      }

      if (isNumber) {
        int duration = std::stoi(numberPart);

        // Проверяем единицу измерения (месяц, год, года)
        if (unitPart == "месяц" || unitPart == "месяцев" ||
            unitPart == "месяца") {
          // Ничего не меняем, срок уже в месяцах
        } else if (unitPart == "год" || unitPart == "года" ||
                   unitPart == "лет") {
          duration *= 12; // Переводим годы в месяцы
        } else {
          std::cerr << "Какая-то неизвестная единица измерения. Пожалуйста, "
                       "используйте 'месяц', 'год' или 'года'."
                    << std::endl;
          std::getline(std::cin, input);
          continue;
        }

        if (duration <= 0) {
          std::cerr
              << "Вы живёте по интреесному календарю! Но для наших скромных "
                 "целей, пожалуй, подойдет срок от месяца до года ";
          std::getline(std::cin, input);
          continue;
        }

        // Проверка на слишком большие числа (например, больше 1200 месяцев)
        if (duration > 12) {
          std::cerr << "Ой! Я пока не умею открывать вклады на такие сроки! ";
          std::getline(std::cin, input);
          continue;
        }

        return duration;
      }
    }

    // Если формат не распознан, проверяем, что введено просто число
    bool isValid = true;
    for (size_t i = 0; i < input.length(); ++i) {
      if (!isdigit(input[i])) {
        std::cerr << "Вижу, что Вы хотели написать мне что-то интересное. "
                     "Обязательно пообщаемся позже, а пока напишите мне срок "
                     "вклада в месяцах! ";
        isValid = false;
        break;
      }
    }

    if (!isValid) {
      std::getline(std::cin, input);
      std::cout << std::endl;
      continue;
    }

    int duration = 0;
    try {
      duration = std::stoi(input);
    } catch (const std::invalid_argument &) {
      std::cerr << "Ошибка: Введено некорректное число. Пожалуйста, введите "
                   "целое число."
                << std::endl;
      std::getline(std::cin, input);
      std::cout << std::endl;
      continue;
    } catch (const std::out_of_range &) {
      std::cerr << "Ошибка: Введено слишком большое число. Пожалуйста, введите "
                   "меньшее число."
                << std::endl;
      std::getline(std::cin, input);
      std::cout << std::endl;
      continue;
    }

    if (duration <= 0) {
      std::cerr << "Вы живёте по интреесному календарю! Но для наших скромных "
                   "целей, пожалуй, подойдет срок от месяца до года ";
      std::getline(std::cin, input);
      std::cout << std::endl;
      continue;
    }

    if (duration > 12) {
      std::cerr << "Ой! Я пока не умею открывать вклады на такие сроки! ";
      std::getline(std::cin, input);
      std::cout << std::endl;
      continue;
    }

    return duration;
  }
}

double DepositAssistant::checkSum(std::string &input) {
  while (true) {
    if (input.empty()) {
      std::cerr << "Если хотите открыть вклад, нужно всё-таки ввести сумму. Не "
                   "стесняйтесь и вводите!"
                << std::endl;
      std::cin >> input;
      continue;
    }

    // Проверка на наличие только цифр и одной точки
    bool hasDecimalPoint = false;
    bool isValid = true;
    for (size_t i = 0; i < input.length(); ++i) {
      if (input[i] == '.') {
        if (hasDecimalPoint) {
          std::cerr << "Какое необычное число! Так открывают вклады на Марсе? "
                       "Давайте обойдёмся без точек: ";
          isValid = false;
          break;
        }
        hasDecimalPoint = true;
      } else if (input[0] == '-') {
        std::cerr << "Ну что Вы, не будьте так критичны к себе. Уверен, ваша "
                     "финансовая ситуация невероятно положительная! ";
        isValid = false;
        break;
      } else if (!isdigit(input[i])) {
        std::cerr << "Вижу, что Вы хотели написать мне что-то интересное. "
                     "Обязательно пообщаемся позже, а пока напишите мне сумму "
                     "вклада! ";
        isValid = false;
        break;
      }
    }

    if (!isValid) {
      std::cin >> input;
      std::cout << std::endl;
      continue;
    }

    // Проверка на слишком длинное число
    if (input.length() > 18) { // Ограничение на длину числа
      std::cerr << "Ого, какое большое число! Я пока не умею открывать вклады "
                   "на такие суммы! ";
      std::cin >> input;
      std::cout << std::endl;
      continue;
    }

    double sum = 0.0;
    try {
      sum = std::stod(input);
    } catch (const std::invalid_argument &) {
      std::cerr
          << "Ошибка: Введено некорректное число. Пожалуйста, введите число."
          << std::endl;
      std::cin >> input;
      std::cout << std::endl;
      continue;
    }

    // Проверка на ноль
    if (sum == 0) {
      std::cerr << "Советую ввести цифру, а потом уже сколько угодно нулей. "
                   "Такие суммы мне нравятся! ";
      std::cin >> input;
      std::cout << std::endl;
      continue;
    }

    // Проверка на дробные части (если нужно запретить дроби)
    if (hasDecimalPoint) {
      std::cerr << "Ой! Я не умею открывать вклады на такие суммы. Давайте "
                   "попробуем ввести целое число ";
      std::cin >> input;
      std::cout << std::endl;
      continue;
    }

    return sum;
  }
}

double DepositAssistant::calculateIncome(double sum, double bet, int duration) {
  return sum * (bet / 100) * (duration / 12.0);
}

bool DepositAssistant::lookForOtherDurations(double &newBet) {
  std::string input;

  std::cout << "Хотите посмотреть расчётные ставки для других сроков по этому "
               "вкладу? (да/нет): ";
  std::cin >> input;
  std::cout << std::endl;

  while (true) {
    if (input == "да") {
      printOtherDurations(newBet);
      return true;
    } else if (input == "нет") {
      std::cout << std::endl;
      return true;
    } else {
      std::cout << "Мне кажется, я Вас немного не понял. Пожалуйста, введите "
                   "'да' или 'нет': ";
      std::cin >> input;
      std::cout << std::endl;
    }
  }
}
bool DepositAssistant::checkFirstAnswer(
    std::string &input, User &user,
    const std::vector<Deposit> &availableDeposits, double &sum, int &duration,
    bool &withdrawProcents) {
  if (availableDeposits.empty()) {
    std::cout << "Нет доступных вкладов.\n";
    return false;
  }

  while (true) {
    if (input == "да") {
      std::cout << "Планируете снимать проценты или суммы? (проценты/суммы): ";
      std::cin >> input;

      if (input == "суммы") {
        for (const auto &deposit : availableDeposits) {
          if (deposit.getName() == "Управляй") {
            double newBet = deposit.calculateBet(user);
            std::cout << "Вам подходит вклад " << deposit.getName() << "\n"
                      << "Максимальная ставка: " << deposit.getMaxPercent()
                      << "%\n"
                      << "Расчетная ставка по вкладу: " << newBet << "%\n"
                      << calculateIncome(sum, newBet, duration)
                      << "р. вы получите за " << duration << " м." << "\n"
                      << "С пополнением, со снятием\n"
                      << std::endl;
            lookForOtherDurations(newBet);
            return false;
          }
        }
      } else if (input == "проценты") {
        withdrawProcents = true;
        return true;
      }
    } else if (input == "нет") {
      return true;
    } else {
      std::cout << "Пожалуйста, введите 'да' или 'нет': ";
      std::cin >> input;
    }
  }
}

void DepositAssistant::checkSecondAnswer(std::string& input, User& user,
    const std::vector<Deposit>& availableDeposits,
    double& sum, int& duration,
    bool& withdrawProcents) {
  while (true) {
    // Если пользователь хочет пополнять вклад, выбираем "ПростоВклад"
    if (input == "да") {
      for (const auto &deposit : availableDeposits) {
        if (deposit.getName() == "ПростоВклад") {
          double newBet = deposit.calculateBet(user, withdrawProcents);
          std::cout << "Вам подходит вклад " << deposit.getName() << "\n"
                    << "Максимальная ставка: " << deposit.getMaxPercent()
                    << "%\n"
                    << "Расчетная ставка по вкладу: " << newBet << "%\n"
                    << calculateIncome(sum, newBet, duration)
                    << "р. вы получите за " << duration << " м." << "\n"
                    << "С пополнением, "
                    << (withdrawProcents ? "со снятием процентов"
                                         : "без снятия")
                    << "\n"
                    << std::endl;
          lookForOtherDurations(newBet);
          return;
        }
      }
    } else if (input == "нет") {
      // Если пользователь не хочет пополнять вклад, выбираем "Лучший"
      for (const auto &deposit : availableDeposits) {
        if (deposit.getName() == "Лучший") {
          double newBet = deposit.calculateBet(user, withdrawProcents);
          std::cout << "Вам подходит вклад " << deposit.getName() << "\n"
                    << "Максимальная ставка: " << deposit.getMaxPercent()
                    << "%\n"
                    << "Расчетная ставка по вкладу: " << newBet << "%\n"
                    << calculateIncome(sum, newBet, duration)
                    << "р. вы получите за " << duration << " м." << "\n"
                    << "Без пополнения, "
                    << (withdrawProcents ? "со снятием процентов"
                                         : "без снятия")
                    << "\n"
                    << std::endl;
          lookForOtherDurations(newBet);
          return;
        }
      }
    } else {
      std::cout << "Мне кажется, я Вас немного не понял. Пожалуйста, введите "
                   "'да' или 'нет': ";
      std::cin >> input;
      std::cout << std::endl;
    }
  }
}

double Deposit::calculateBet(const User &user, bool withdrawProcents) const {
  double adjustedBet = percent_max;

  if (!user.getSalary()) {
    adjustedBet -= 1.0;
  }
  if (!user.getBroker()) {
    adjustedBet -= 0.5;
  }
  if (!user.getSubscription()) {
    adjustedBet -= 1.0;
  }

  if (withdrawProcents) {
    adjustedBet -= 0.95;
  }

  return adjustedBet;
}

void DepositAssistant::rechooseSumOrDuration(User& user, double& sum, int& duration,
    Deposit& recommendedDeposit, double& newBet,
    bool& withdrawProcents)  {
  std::string input;
  double rememberBet = newBet;

  std::cout << "Что Вы хотите изменить? Сумму, срок или всё вместе?\n";
  std::cout << "1. Изменить сумму\n";
  std::cout << "2. Изменить срок\n";
  std::cout << "3. Изменить и сумму, и срок\n";
  std::cout << "Вводите скорее! (1, 2, 3): ";
  std::cin >> input;
  std::cout << std::endl;

  while (true) {
    if (input == "1") {
      std::cout << "Какой будет новая сумма? ";
      std::cin >> input;
      std::cout << std::endl;
      sum = checkSum(input);
      break;
    } else if (input == "2") {
      std::cout << "Вот карта сроков и ставок для Вашего вклада, можете "
                   "ориентироваться на неё при выборе: ";
      printOtherDurations(newBet);
      std::cout << "Каким будет срок? ";
      std::cin.ignore();
      std::getline(std::cin, input);
      duration = checkDuration(input);
      newBet = getRateForDuration(newBet, duration);
      std::cout << std::endl;
      break;
    } else if (input == "3") {
      std::cout << "Какой будет новая сумма? ";
      std::cin >> input;
      std::cout << std::endl;
      sum = checkSum(input);

      std::cout << "Вот карта сроков и ставок для Вашего вклада, можете "
                   "ориентироваться на неё при выборе: ";
      printOtherDurations(newBet);
      std::cout << "Каким будет срок? ";
      std::cin.ignore(); // Очистка потока ввода
      std::getline(std::cin, input); // Чтение строки с учётом пробелов
      duration = checkDuration(input);
      newBet = getRateForDuration(newBet, duration);
      std::cout << std::endl;
      break;
    } else {
      std::cout << "Мне кажется, я Вас немного не понял. Пожалуйста, введите "
                   "1, 2 или 3\n\n";
      std::cin >> input;
    }
  }

  // Перерасчёт вклада с новыми параметрами
  std::cout << "Вам подходит вклад " << recommendedDeposit.getName() << "\n"
            << "Максимальная ставка: " << recommendedDeposit.getMaxPercent()
            << "%\n"
            << "Расчетная ставка по вкладу: " << newBet << "%\n"
            << calculateIncome(sum, newBet, duration) << "р. вы получите за "
            << duration << " м." << "\n"
            << "С пополнением, "
            << (withdrawProcents ? "со снятием процентов" : "без снятия")
            << "\n"
            << std::endl;
  duration = 6;
  newBet = rememberBet;
  return;
}

bool DepositAssistant::showIfMenu(User& user, double sum, int duration,
    bool withdrawProcents, Deposit& recommendedDeposit,
    double newBet)  {
  std::string input;

  while (true) {
    std::cout << "Если Вы готовы открыть подобранный мною вклад, то нажмите 1, "
                 "и я всё оформлю\n\n";
    std::cout << "Если нужно перевыбрать срок или сумму, нажмите 2, мигом всё "
                 "сделаем!\n\n";
    std::cout << "Если хотите узнать, как увеличить Вашу процентную ставку, "
                 "нажмите 3\n\n";
    std::cout << "Если желаете посоветоваться со мной ещё раз, нажмите 4, я "
                 "буду рад!\n\n";
    std::cout << "Если работа со мной на сегодня закончена, нажмите 5\n\n";
    std::cin >> input;

    if (input == "1") {
      // Логика оформления вклада
      std::cout << "Ваш вклад успешно оформлен! Спасибо за доверие!\n\n";
      return false; // Возврат в основное меню после оформления
    } else if (input == "2") {
      rechooseSumOrDuration(user, sum, duration, recommendedDeposit, newBet,
                            withdrawProcents);
    } else if (input == "3") {
      // Логика увеличения процентной ставки
      // increaseInterestRate();
    } else if (input == "4") {
      // Повторный совет
      //DepositChoice();
    } else if (input == "5") {
      // Возврат в основное меню Assistant
      std::cout << std::endl;
      std::cout << "Приятно было поработать вместе! Возвращаю Вас в основное "
                   "меню\n\n";
      return true;
    } else {
      std::cout << "Мне кажется, я Вас немного не понял. Пожалуйста, введите "
                   "1, 2, 3, 4 или 5\n\n";
    }
  }
}

void DepositAssistant::DepositChoice(
    User &user, const std::vector<Deposit> &availableDeposits) {
  std::string input;
  bool withdrawProcents = false;
  int duration = 6; // стандартный срок для любого вклада
  Deposit recommendedDeposit; // Для хранения рекомендованного вклада
  double newBet = 0.0;

  while (true) {
    std::cout << "Конечно! Давайте подберем вклад вместе\n";
    std::cout << "Для начала мне нужно задать Вам несколько вопросов\n\n";

    // Ввод суммы
    std::cout << "Какую сумму Вы хотели бы положить? ";
    std::cin >> input;
    std::cout << std::endl;
    double sum = checkSum(input);

    std::cout << "Планируете ли Вы снимать деньги до конца срока? (да/нет): ";
    std::cin >> input;
    std::cout << std::endl;
    bool proceedToSecondAnswer = checkFirstAnswer(
        input, user, availableDeposits, sum, duration, withdrawProcents);
    if (!proceedToSecondAnswer) {
      return; // Выходим в основное меню
    }

    // Если нужно перейти к checkSecondAnswer
    std::cout << "Хотите ли Вы иметь возможность пополнять вклад? (да/нет): ";
    std::cin >> input;
    std::cout << std::endl;
    checkSecondAnswer(input, user, availableDeposits, sum, duration,
                      withdrawProcents);
    // Сохраняем рекомендованный вклад
    for (const auto &deposit : availableDeposits) {
      if (deposit.getName() == "ПростоВклад" || deposit.getName() == "Лучший" ||
          deposit.getName() == "Управляй") {
        recommendedDeposit = deposit;
        newBet = deposit.calculateBet(user, withdrawProcents);
        break;
      }
    }

    // Вызов showIfMenu и проверка возвращаемого значения
    if (showIfMenu(user, sum, duration, withdrawProcents, recommendedDeposit,
                   newBet)) {
      return; // Возврат в Assistant, если пользователь выбрал 5
    }
  }
}
