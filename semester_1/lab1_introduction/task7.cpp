#include <iostream>
using namespace std;

int main(){
  int n;
  cout << "ввведите n ";
  cin >> n;
  if (n % 2 == 0) {
    cout << "summ" << (n-1) * (n-1);
  }
  else {
    cout << "summ" << n * n;
  }
  return(0);
}
