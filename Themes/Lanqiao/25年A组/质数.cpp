#include <bits/stdc++.h>

using namespace std;

bool isPrime(int num) {
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int cnt = 0;
  for (int i = 2; i <= 1e8; i++) {
    if (isPrime(i))
      cnt++;

    if (cnt == 2025) {
      cout << i;
      break;
    }
  }
  return 0;
}