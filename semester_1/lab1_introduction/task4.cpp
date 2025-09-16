#include <iostream>
using namespace std;

int main() {
  long long even = 1 ,odd = 1;
  int n;
  cout << "введите n ";
  cin >> n;
  for (int i = 1; i <= n; i++) {
    if (i % 2 == 0) {
      even *= i;
    }
    else {
      odd *= i;  
    }
  }
  if (n % 2 == 0) {
    cout << "четное " << even;
  }
  else {
    cout << "нечетное " << odd;
  }
  return(0);
}
