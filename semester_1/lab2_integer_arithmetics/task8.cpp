#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    int a, b;
    cout << "введите a, затем b ";
    cin >> a >> b;
    if (a > b) {
        swap(a, b);
    }
    for (int n = a; n <= b; n++) {
        if (n < 2) continue;
        int i;
        for (i = 2; i <= n - 1; i++) {
            if (n % i == 0) {
                break;

            }
        }
        if (i * i > n) {
            cout << n << " ";
        }
    }

    return 0;

}
