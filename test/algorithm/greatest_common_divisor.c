int greatest_common_divisor(int a, int b) {
  if (a % b == 0)
    return b;
  else {
    return greatest_common_divisor(b, a % b);
  }
}

int least_common_multiple(int a, int b) {
  int d = greatest_common_divisor(a, b);
  if (d == 1)
    return a * b;
  else
    return a * b / d;
}
