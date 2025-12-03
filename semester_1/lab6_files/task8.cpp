НЕ РАБОЧИЙ
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

int main() {
    std::ifstream file("input.txt");

    if (!file.is_open()) {
       
        std::cerr << "Ошибка открытия файла!" << std::endl;

    }

    std::queue<std::string> stringQueue;

    std::string line;
    while (std::getline(file, line)) {
        stringQueue.push(line);
    }

    file.close();

    while (!stringQueue.empty()) {
        std::string currentLine = stringQueue.front();

        for (int i = 0; i < currentLine.size(); ++i) {
            std::cout << currentLine[i];
            if (i != currentLine.size() - 1) {
                std::cout << '|';
            }
        }
        std::cout
        stringQueue.pop();
    }

    return 0;
}
