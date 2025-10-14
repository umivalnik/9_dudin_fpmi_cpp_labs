#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>

const int max1 = 100;

void imputingwithcheck(int& n) {

    setlocale(LC_ALL, "Russian");

    std::cout << "введите количество элементов менее " << max1 << "): ";
    std::cin >> n;

    if (n <= 0 || n > max1) {
        std::cout << "ошибка размера" << std::endl;
        std::exit(1);
    }
}

int main() {
        
    setlocale(LC_ALL, "Russian");

    double arr[max1];
    int n;
    int choice;

    imputingwithcheck(n);

    std::cout << "выберите способ заполнения:" << std::endl;
    std::cout << "1 - ввод с клавиатуры " << std::endl;
    std::cout << "2 - случайное заполнение " << std::endl;
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

    std::cout << "исходный массив: ";
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

    std::cout << "произведение: " << umn << std::endl;

    int N;
    std::cout << "введите количество элементов для удаления: ";
    std::cin >> N;

    if (N > 0 && N <= n) {
        double temp[max1];
        int indices[max1];

        for (int i = 0; i < n; i++) {
            temp[i] = arr[i];
            indices[i] = i;
        }

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (temp[j] > temp[j + 1]) {
                    std::swap(temp[j], temp[j + 1]);
                    std::swap(indices[j], indices[j + 1]);
                }
            }
        }

        bool to_remove[max1] = { false };
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

        std::cout << "после удаления " << N << " наименьших элементов: ";
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (std::fabs(arr[j]) > std::fabs(arr[j + 1])) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }

        std::cout << "после сортировки: ";
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "ошибочное N" << std::endl;
    }

    return 0;
}
