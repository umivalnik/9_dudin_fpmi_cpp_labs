#include <iostream>
#include <random>

int main() {

    setlocale(LC_ALL, "Russian");

    int n, m    ;
    std::cout << "Введите количество строк и столбцов: ";
    std::cin >> n >> m;

    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m];
    }

    int choice;
    std::cout << "Выберите способ заполнения \n ручной - 1 \n случайный - 2 ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Введите элементы матрицы:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cin >> matrix[i][j];
            }
        }
    }
    else {
        double a, b;
        std::cout << "введите границы [a, b]: ";
        std::cin >> a >> b;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(a, b);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                matrix[i][j] = dis(gen);
            }
        }
    }

    std::cout << "Матрица:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    int t = matrix[0][0];
    int count = 0;

    for (int j = 0; j < m; j++) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] == t) {
                found = true;
                break;
            }
        }
        if (!found) count++;
    }

    int max_series = 0;
    int MaxSeries = 0;

    for (int i = 0; i < n; i++) {
        int current_series = 1;
        int max_in_row = 1;

        for (int j = 1; j < m; j++) {
            if (matrix[i][j] == matrix[i][j - 1]) {
                count;
                current_series++;
                if (current_series > max_in_row) {
                    max_in_row = current_series;
                }
            }
            else {
                current_series = 1;
            }
        }

        if (max_in_row > max_series) {
            max_series = max_in_row;
            MaxSeries = i;
        }
    }

    std::cout << "Количество столбцов без элемента " << t << ": " << count << "\n";
    std::cout << "Строка с самой длинной серией одинаковых элементов: " << MaxSeries << "\n";

    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;

