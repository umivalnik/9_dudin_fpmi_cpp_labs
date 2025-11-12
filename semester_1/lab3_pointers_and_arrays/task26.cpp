#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>

void imputingwithcheck(int& n) {
    setlocale(LC_ALL, "Russian");

    std::cout << "Введите количество элементов: ";
    std::cin >> n;

    if (std::cin.fail() || n <= 0) {
        std::cout << "Ошибка: некорректное количество элементов.\n";
        std::exit(1);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n;
    int choice;

    imputingwithcheck(n);

    double* arr = new double[n];

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
            std::cout << "Границы перепутаны. Меняю местами: a = " << a << ", b = " << b << std::endl;
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

    std::cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    int maxindex = 0;
    int minindex = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[maxindex]) {
            maxindex = i;
        }
        if (arr[i] < arr[minindex]) {
            minindex = i;
        }
    }

    double umn = 1.0;
    for (int i = std::min(minindex, maxindex) + 1; i < std::max(minindex, maxindex); i++) {
        umn *= arr[i];
    }

    std::cout << "Произведение элементов между min и max: " << umn << std::endl;

    int N;
    std::cout << "Введите количество элементов для удаления: ";
    std::cin >> N;

    if (std::cin.fail() || N <= 0 || N > n) {
        std::cout << "Ошибка: некорректное значение N.\n";
        return 1;
    }

    double* temp = new double[n];
    int* indices = new int[n];

    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
        indices[i] = i;
    }

    // сортировка по возрастанию
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                std::swap(temp[j], temp[j + 1]);
                std::swap(indices[j], indices[j + 1]);
            }
        }
    }

    bool* to_remove = new bool[n];
    for (int i = 0; i < n; i++) {
        to_remove[i] = false;
    }

    for (int i = 0; i < N; i++) {
        to_remove[indices[i]] = true;
    }

    int new_index = 0;
    for (int i = 0; i < n; i++) {
        if (!to_remove[i]) {
            arr[new_index] = arr[i];
            new_index++;
        }
    }

    n = new_index;

    std::cout << "После удаления " << N << " наименьших элементов: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // сортировка по модулю
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (std::fabs(arr[j]) > std::fabs(arr[j + 1])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }

    std::cout << "После сортировки по модулю: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}