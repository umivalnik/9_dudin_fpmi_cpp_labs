#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <cctype>
#include <algorithm>

int main() {
    setlocale(LC_ALL, "ru");

    std::ifstream file("input.txt");

    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::vector<int> maxLengths;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);

        int maxLen = 0;
        int currentLen = 0;
        char currentChar = '\0';

        for (char c : line) {
            if (std::isalpha(c)) {
                char lowC = std::tolower(c);

                if (lowC == currentChar) {
                    currentLen++;
                }
                else {
                    currentChar = lowC;
                    currentLen = 1;
                }

                if (currentLen > maxLen) {
                    maxLen = currentLen;
                }
            }
            else {
                currentChar = '\0';
                currentLen = 0;
            }
        }
        maxLengths.push_back(maxLen);
    }

    file.close();

    int globalMax = 0;
    for (int len : maxLengths) {
        if (len > globalMax) {
            globalMax = len;
        }
    }


    int count = 0;
    for (size_t i = 0; i < lines.size() && count < 10; i++) {
        if (maxLengths[i] == globalMax && globalMax > 0) {
            std::cout << "cnрока " << (i + 1) << " " << lines[i] << std::endl;
            count++;
        }
    }

    if (count == 0) {
        std::cout << "подстрок не найдено" << std::endl;
    }

    return 0;
}
