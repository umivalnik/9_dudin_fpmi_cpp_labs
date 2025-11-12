
// solve task with usage of
// static arrays

#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>

const int max1 = 100;

void InputWithCheck(int& n) {
    setlocale(LC_ALL, "Russian");

    std::cout << "Введите количество элементов (менее " << max1 << "): ";
    std::cin >> n;

    if (std::cin.fail()) {
        std::cout << "Ошибка: введено не число.\n";
        std::exit(1);
    }

    if (n <= 0 || n > max1) {
        std::cout << "Ошибка: размер должен быть от 1 до " << max1 << ".\n";
        std::exit(1);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    double arr[max1];
    int n;
    int choice;

    InputWithCheck(n);

    std::cout << "Выберите способ заполнения:\n";
    std::cout << "1 - ввод с клавиатуры\n";
    std::cout << "2 - случайное заполнение\n";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cout << "Ошибка: введено не число.\n";
        return 1;
    }

    if (choice == 1) {
        std::cout << "Введите элементы массива:\n";
        for (int i = 0; i < n; i++) {
            std::cin >> arr[i];
            if (std::cin.fail()) {
                std::cout << "Ошибка: введено не число.\n";
                return 1;
            }
        }
    }
    else if (choice == 2) {
        double a, b;
        std::cout << "Введите границы [a, b]: ";
        std::cin >> a >> b;

        if (std::cin.fail()) {
            std::cout << "Ошибка: введены некорректные значения.\n";
            return 1;
        }

        if (a > b) {
            std::swap(a, b);
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(a, b);

        for (int i = 0; i < n; i++) {
            arr[i] = dis(gen);
        }
    }
    else {
        std::cout << "Ошибка: нужно выбрать 1 или 2.\n";
        return 1;
    }

    double sum1 = 0.0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            sum1 += arr[i];
        }
    }

    int maxindex = 0;
    double maxnum = std::fabs(arr[0]);
    for (int i = 1; i < n; i++) {
        if (std::fabs(arr[i]) > maxnum) {
            maxnum = std::fabs(arr[i]);
            maxindex = i;
        }
    }

    int minindex = 0;
    double minnum = std::fabs(arr[0]);
    for (int i = 1; i < n; i++) {
        if (std::fabs(arr[i]) <= minnum) {
            minnum = std::fabs(arr[i]);
            minindex = i;
        }
    }

    double umn = 1.0;
    for (int i = std::min(minindex, maxindex) + 1; i < std::max(minindex, maxindex); i++) {
        umn *= arr[i];
    }

    for (int i = 0; i < n; i += 2) {
        for (int k = 0; k < n - i - 2; k += 2) {
            if (arr[k] < arr[k + 2]) {
                std::swap(arr[k], arr[k + 2]);
            }
        }
    }

    std::cout << "\nСумма положительных: " << sum1 << std::endl;
    std::cout << "Произведение элементов между min и max: " << umn << std::endl;
    std::cout << "После сортировки: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
