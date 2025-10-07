#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>

const int max1 = 100;

int main() {
    double arr[max1];
    int n;
    int choice;

    std::cout << "введите количество элементов менее " << max1 << "): ";
    std::cin >> n;

    if (n <= 0 || n > max1) {
        std::cout << "ошибка размера" << std::endl;
        return 1;
    }

    std::cout << "выберите способ заполнения:";
    std::cout << "1 - ввод с клавиатуры";
    std::cout << "2 - случайное заполнение";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "введите элементы массива: ";
        for (int i = 0; i < n; i++) {
            std::cin >> arr[i];
        }
    }
    else if (choice == 2) {
        double a, b;
        std::cout << "введите границы [a, b]: ";
        std::cin >> a >> b;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(a, b);

        for (int i = 0; i < n; i++) {
            arr[i] = dis(gen);
        }
    }
    else {
        std::cout << "ошибка" << std::endl;
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
    int start = std::min(maxindex, minindex);
    int end = std::max(maxindex, minindex);
    bool elements_between = false;

    for (int i = start + 1; i < end; i++) {
        umn *= arr[i];
        elements_between = true;
    }
    if (!elements_between) {
        umn = 0.0;
    }

    for (int i = 0; i < n; i += 2) {
        for (int k = 0; k < n - i - 2; k += 2) {
            if (arr[k] < arr[k + 2]) {
                std::swap(arr[k], arr[k + 2]);
            }
        }
    }

    std::cout << "сумма положительных: " << sum1 << std::endl;
    std::cout << "произведение: " << umn << std::endl;
    std::cout << "после сортировки: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
