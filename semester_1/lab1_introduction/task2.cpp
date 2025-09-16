#include <iostream>
using namespace std;

int main() {
    double a;
    double d = 0, e = 1;
    cout << "введите n ";
    cin >> a ;
    for (int k = 1; k <= a; k++ ) {
        if (k % 2 == 0) {
            d = d + k;
        }
        else{
            e = e * k;
        }
    }
    cout << "сумма " << d << endl;
    cout << "произведение "<< e ;
    return 0;
}
