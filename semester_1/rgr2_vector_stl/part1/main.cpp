НЕ КОНЕЧНАЯ ПРОГИРАММА


#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iterator>

int main() {
    std::vector<int> numbers;
    
    // Ввод чисел
    std::cout << "Введите целые числа:\n";
    std::copy(std::istream_iterator<int>(std::cin),
              std::istream_iterator<int>(),
              std::back_inserter(numbers));
    
    // Очистка флага ошибок ввода
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // 1. Сумма чисел
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Сумма всех чисел: " << sum << std::endl;
    
    // 2. Общее количество чисел
    std::cout << "Количество чисел: " << numbers.size() << std::endl;
    
    // 3. Количество чисел, равных заданному
    int target;
    std::cout << "Введите число для поиска: ";
    std::cin >> target;
    int count_target = std::count(numbers.begin(), numbers.end(), target);
    std::cout << "Количество чисел равных " << target << ": " << count_target << std::endl;
    
    // 4. Количество чисел, больших чем n
    int n;
    std::cout << "Введите число n для сравнения: ";
    std::cin >> n;
    int count_greater = std::count_if(numbers.begin(), numbers.end(),
                                      [n](int x) { return x > n; });
    std::cout << "Количество чисел больших чем " << n << ": " << count_greater << std::endl;
    
    // 5. Заменить все нули средним арифметическим (целая часть)
    std::vector<int> numbers_copy1 = numbers; // Копия для изменений
    if (!numbers_copy1.empty()) {
        int average = sum / numbers_copy1.size();
        std::replace(numbers_copy1.begin(), numbers_copy1.end(), 0, average);
        std::cout << "Замена всех нулей " << std::endl;
        for (int num : numbers_copy1) std::cout << num << " ";
        std::cout << std::endl;
    }
    
    // 6. Добавить к каждому элементу сумму всех чисел из заданного интервала
    std::vector<int> numbers_copy2 = numbers; // Новая копия для изменений
    if (!numbers_copy2.empty()) {
        int start_idx, end_idx;
        std::cout << "Введите начальный и конечный интервал" 
                  << numbers_copy2.size()-1 << "): ";
        std::cin >> start_idx >> end_idx;
        
        // Проверка корректности индексов
        if (start_idx >= 0 && end_idx < numbers_copy2.size() && start_idx <= end_idx) {
            int interval_sum = std::accumulate(numbers_copy2.begin() + start_idx,
                                              numbers_copy2.begin() + end_idx + 1, 0);
            
            std::transform(numbers_copy2.begin(), numbers_copy2.end(),
                          numbers_copy2.begin(),
                          [interval_sum](int x) { return x + interval_sum; });
            
            std::cout << "   Сумма чисел : " << interval_sum << std::endl;
            std::cout << "   Результат после добавления суммы: ";
            for (int num : numbers_copy2) std::cout << num << " ";
            std::cout << std::endl;
        } else {
            std::cout << " " << std::endl;
        }
    }
    
    // 7. Заменить числа с четным модулем на разность max-min
    std::vector<int> numbers_copy3 = numbers; // Новая копия для изменений
    if (!numbers_copy3.empty()) {
        auto [min_it, max_it] = std::minmax_element(numbers_copy3.begin(), numbers_copy3.end());
        int diff = *max_it - *min_it;
        
        std::replace_if(numbers_copy3.begin(), numbers_copy3.end(),
                       [](int x) { return std::abs(x) % 2 == 0; },
                       diff);
        
        std::cout << "Замена чисел с четным модулем:" << std::endl;
        for (int num : numbers_copy3) std::cout << num << " ";
        std::cout << std::endl;
    }
    
    // 8. Удалить все равные по модулю числа, кроме первого
    std::vector<int> numbers_copy4 = numbers; // Новая копия для изменений
    auto new_end = std::unique(numbers_copy4.begin(), numbers_copy4.end(),
                              [](int a, int b) { return std::abs(a) == std::abs(b); });
    numbers_copy4.erase(new_end, numbers_copy4.end());
    
    std::cout << " даление равных" << std::endl;
    for (int num : numbers_copy4) std::cout << num << " ";
    std::cout << std::endl;
    
    // Вывод исходного вектора для сравнения
    std::cout << "Изначальный вектор: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    return 0;
}
