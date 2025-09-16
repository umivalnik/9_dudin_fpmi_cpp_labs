#include <iostream>
using namespace std;

int main() {
  int n, a = 0;
  cout << "введите n ";
  cin >> n;
  for (int k = 1; k <= n; k++ ) {
    a = a + pow(k,n);
  }
  cout << a;
  return(0);
}       


 //не влезает в int
