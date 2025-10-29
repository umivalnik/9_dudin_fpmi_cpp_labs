#include <iostream>
#include <random>
#include <iomanip>

bool comparison1(int first_number, int second_number) {
    return first_number > second_number;
}

bool comparison2(int first_number, int second_number) {
    return first_number < second_number;
}

int GetChoice() {
    int variant;
    if (!(std::cin >> variant)) {
        std::cout << "Неверное число";
    }

    return variant;
}

void input_sides(int& n, int& m) {
    std::cout << "введите размерномть матрицы n и m ";
    if (!(std::cin >> n) || n < 1) {
        std::cout << "Неверное число";
    }
    if (!(std::cin >> m) || m < 1) {
        std::cout << "Неверное число";
    }
}

void CMatrix(int**& matrices, int n, int m) {
    matrices = new int* [n];
    for (int i = 0; i < n; i++) {
        matrices[i] = new int[m];
    }
}

void Borders(int& lower, int& upper) {
    std::cout << "\n Введи границы";
    if (!(std::cin >> lower >> upper)) {
        std::cout << "Неверное число";
    }

    if (lower > upper) {
        std::swap(lower, upper);
    }
}

void RandomMatrix(int** matr, int n, int m, std::mt19937* gen) {
    int lower, upper;
    Borders(lower, upper);

    std::uniform_int_distribution<int> dist(lower, upper);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matr[i][j] = dist(*gen);
        }
    }
}

void manMatrix(int** matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!(std::cin >> matr[i][j])) {
                std::cout << "Неверное число";
            }
        }
    }
}

void printing_matrices(int** matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << std::setw(5) << matr[i][j];
        }
        std::cout << "\n";
    }
}

void InputVariant(int** matrices, int n, int m) {
    std::cout << "\nРандомные числа - 1\n Ручное заполнение - 2\n";
    int choice = GetChoice();
    if (choice == 1) {
        std::random_device rd;
        std::mt19937 gen(rd());

        RandomMatrix(matrices, n, m, &gen);

        std::cout << "\n матрица:\n";
        printing_matrices(matrices, n, m);
    }
    else if (choice == 2) {

        std::cout << "\n ВВедите элементы\n";
        manMatrix(matrices, n, m);

    }
    else {
        std::cout << "\nНеверное число";
        std::exit(404);
    }
}

void bubble_sort(int** matrix, int m, int n) {
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (matrix[k][j] > matrix[k][j + 1]) {
                    std::swap(matrix[k][j], matrix[k][j + 1]);
                }
            }
        }
    }
}

int MaxElement(int* array, int length_of_array) {
    int max_element = array[0];

    for (int i = 0; i < length_of_array; i++) {
        if (array[i] > max_element) {
            max_element = array[i];
        }
    }

    return max_element;
}

int MinElement(int* array, int length) {
    int min_element = array[0];

    for (int i = 0; i < length; i++) {
        if (array[i] < min_element) {
            min_element = array[i];
        }
    }

    return min_element;
}


void counting_sort(int* array, int length, bool (*comparison)(int a, int b)) {
    int min = MinElement(array, length);
    int max = MaxElement(array, length);

    int amount_of_element_value = max - min + 1;
    int* count = new int[amount_of_element_value] {};


    for (int j = 0; j < length; j++) {
        count[array[j] - min]++;
    }


    int k{ 0 };
    if (comparison == comparison1) {
        for (int i = 0; i < amount_of_element_value; i++) {
            for (int j = 0; j < count[i]; j++) {
                array[k] = (i + min);
                ++k;
            }
        }
    }
    else {
        for (int i = amount_of_element_value - 1; i >= 0; i--) {
            for (int j = 0; j < count[i]; j++) {
                array[k] = (i + min);
                ++k;
            }
        }
    }

    delete[] count;
}

void quick_sort(int* array, int left, int right, bool (*comparison)(int a, int b)) {
    if (comparison1(left, right)) {
        return;
    }

    int i = left, j = right;
    int midle = array[(left + right) / 2];

    while (!comparison1(i, j)) {
        while (comparison(midle, array[i])) {
            ++i;
        }
        while (comparison(array[j], midle)) {
            --j;
        }
        if (!comparison1(i, j)) {
            std::swap(array[i], array[j]);
            ++i; --j;
        }
    }

    quick_sort(array, left, j, comparison);
    quick_sort(array, i, right, comparison);
}

void addding_result_in_array(int* array, int* result, int k) {
    for (int i = 0; i < k; i++) {
        array[i] = result[i];
    }
}

void merge(int* array, int m, int begin, int end, bool (*comparison)(int a, int b)) {
    int i = begin, midle = begin + (end - begin) / 2, j = midle + 1, k = 0;

    int* result = new int[m];

    while (!comparison1(i, midle) && !comparison1(j, end)) {
        if (!comparison(array[i], array[j])) {
            result[k] = array[i];
            ++i;
        }
        else {
            result[k] = array[j];
            ++j;
        }
        ++k;
    }

    while (!comparison1(i, midle)) {
        result[k] = array[i];
        ++i; ++k;
    }

    while (!comparison1(j, end)) {
        result[k] = array[j];
        ++j; ++k;
    }

    addding_result_in_array(array, result, k);

    delete[] result;
}

void merge_sort(int* array, int m, int left, int right, bool (*comparison)(int a, int b)) {
    int temp;
    if (comparison1(right, left)) {
        if (right - left == 1) {
            if (comparison(array[left], array[right])) {
                std::swap(array[left], array[right]);
            }
        }
        else {
            merge_sort(array, m, left, left + (right - left) / 2, comparison);
            merge_sort(array, m, left + (right - left) / 2 + 1, right, comparison);
            merge(array, m, left, right, comparison);
        }
    }
}

void input_sort(int* array, int m, bool (*comparison)(int a, int b)) {
    for (int i = 1; i < m; i++) {
        int element = array[i];
        int j = i - 1;
        for (j; j >= 0 && comparison(array[j], element); j--) {
            array[j + 1] = array[j];
        }
        array[j + 1] = element;
    }

}

int finding_index_of_element(int* array, int i, int m, bool (*comparison)(int a, int b)) {
    int index = i;
    for (i; i < m; i++) {
        if (comparison(array[index], array[i])) {
            index = i;
        }
    }

    return index;
}

void choise_sort(int* array, int m, bool (*comparison)(int a, int b)) {
    for (int i = 0; i < m; i++) {
        int max_index = finding_index_of_element(array, i, m, comparison);
        std::swap(array[i], array[max_index]);
    }
}


bool (*typeorder())(int, int) {
    std::cout << "\n По убыванию или возрастанию? \n По взрастанию - 1 \n по убыванию - 2 ";
    int choice = GetChoice();
    if (choice == 1) {
        return comparison1;
    }
    else if (choice == 2) {
        return comparison2;
    }
    else {
        std::cout << "Неверное число";
    }
}

void TypeSort(int** matrices, int n, int m) {
    bool(*type_of_comparison)(int, int) = typeorder();


    std::cout << "\n Какую сортировку использовать? \n bubble sort - 1 \n counting sort - 2 \n quick sort - 3 \n merge sort - 4 \n input sort - 5 \n choise sort - 6\n";
    switch (int choice = GetChoice()) {
    case 1: {
        for (int i = 0; i < n; i++) {
            bubble_sort(matrices[i], m, type_of_comparison);
        }
        break;
    }
    case 2: {
        for (int i = 0; i < n; i++) {
            counting_sort(matrices[i], m, type_of_comparison);
        }
        break;
    }
    case 3: {
        for (int i = 0; i < n; i++) {
            quick_sort(matrices[i], 0, m - 1, type_of_comparison);
        }
        break;
    }
    case 4: {
        for (int i = 0; i < n; i++) {
            merge_sort(matrices[i], m, 0, m - 1, type_of_comparison);
        }
        break;
    }
    case 5: {
        for (int i = 0; i < n; i++) {
            input_sort(matrices[i], m, type_of_comparison);
        }
        break;
    }
    case 6: {
        for (int i = 0; i < n; i++) {
            choise_sort(matrices[i], m, type_of_comparison);
        }
        break;
    }
    default: {
        std::cout << "Неверное число";
    }
    }
}

void DelMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


int main() {

    setlocale(LC_ALL, "Russian");

    int n, m;
    input_sides(n, m);

    int** matrix;
    CMatrix(matrix, n, m);

    InputVariant(matrix, n, m);

    TypeSort(matrix, n, m);

    std::cout << "\n Получившаяся матрица:\n";
    printing_matrices(matrix, n, m);

    DelMatrix(matrix, n);

    return 0;
}
