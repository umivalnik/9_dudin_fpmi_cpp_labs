#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int max1 = 100;

int main() {
    double arr[max1];
    int n;

    cout << "введите количество менее " << max1 << ": ";
    cin >> n;

    if (n <= 0 || n > max1) {
        cout << "ошибка размермера" << endl;
        return 1;
    }

    cout << "введите элементы массива: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    double sum1 = 0.0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            sum1 += arr[i];
        }
    }

    int maxindex = 0;
    double maxnum = fabs(arr[0]);
    for (int i = 1; i < n; i++) {
        if (fabs(arr[i]) > maxnum) {
            maxnum = fabs(arr[i]);
            maxindex = i;
        }
    }

    int minindex = 0;
    double minnum = fabs(arr[0]);
    for (int i = 1; i < n; i++) {
        if (fabs(arr[i]) <= minnum) {
            minnum = fabs(arr[i]);
            minindex = i;
        }
    }

    double umn = 1.0;
    int start = min(maxindex, minindex);
    int end = max(maxindex, minindex);
    bool elements_between = false;

    for (int i = start + 1; i < end; i++) {
        umn *= arr[i];
        elements_between = true;
    }
    if (elements_between == false) {
        umn = 0.0;
    }

    for (int i = 0; i < n; i += 2) {
        for (int k = 0; k < n - i; k += 2) {
            if (arr[k] < arr[k + 2]) {
                swap(arr[k], arr[k + 2]);
            }
        }
    }
    cout << "сумма положительных : " << sum1 << endl;
    cout << "произведение: " << umn << endl;
    cout << "после сортировки: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;


    return 0;
}
