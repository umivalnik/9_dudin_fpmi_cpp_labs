#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

int main() {
    setlocale(LC_ALL, "Russian");

    std::string input;
    std::cout << "Введите строку: ";
    std::getline(std::cin, input);

    std::istringstream InputString(input);
    std::vector<std::string> digitWords;
    std::vector<std::string> otherWords;
    std::string word;

    while (InputString >> word) {
        bool isDigitOnly = true;

        for (char c : word) {
            if (!std::isdigit(c)) {
                isDigitOnly = false;
                break;
            }
        }

        if (isDigitOnly) {
            digitWords.push_back(word);
        }
        else {
            otherWords.push_back(word);
        }
    }

    std::string result;

    for (const auto& w : digitWords) {
        if (!result.empty()) result += " ";
        result += w;
    }

    for (const auto& w : otherWords) {
        if (!result.empty()) result += " ";
        result += w;
    }

    std::cout << "Результат: " << result << std::endl;

    return 0;
}
