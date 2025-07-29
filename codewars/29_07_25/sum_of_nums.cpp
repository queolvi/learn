int get_sum(int a, int b) {
  int min = a > b ? a : b;
  int max = a < b ? a : b;
  return (max - min + 1) * (min + max) / 2;
}
