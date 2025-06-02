// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

#include "tree.h"

int main() {
  std::vector<char> basic = {'1', '2', '3'};
  PMTree tree(basic);

  std::cout << "Все перестановки:\n";
  auto all = getAllPerms(tree);
  for (const auto& p : all) {
    for (char c : p)
      std::cout << c;
    std::cout << '\n';
  }

  auto res1 = getPerm1(tree, 1);
  std::cout << "Перестановка №1: ";
  for (char c : res1)
    std::cout << c;
  std::cout << '\n';

  auto res2 = getPerm2(tree, 2);
  std::cout << "Перестановка №2: ";
  for (char c : res2)
    std::cout << c;
  std::cout << '\n';

  std::vector<int> sizes = {5, 6, 7, 8};
  std::ofstream file("result/times.csv");
  file << "n, getAll, getPerm1, getPerm2\n";

  for (int n : sizes) {
    std::vector<char> input;
    for (int i = 1; i <= n; ++i) {
      input.push_back('0' + i);
    }

    PMTree t(input);
    int64_t total = 1;
    for (int i = 2; i <= n; ++i)
      total *= i;

    std::mt19937_64 rng(1234);
    std::uniform_int_distribution<int64_t> dist(1, total);
    int idx = static_cast<int>(dist(rng));

    using clk = std::chrono::high_resolution_clock;
    auto start_all = clk::now();
    auto result_all = getAllPerms(t);
    auto end_all = clk::now();

    auto result1 = getPerm1(t, idx);
    auto end_p1 = clk::now();

    auto result2 = getPerm2(t, idx);
    auto end_p2 = clk::now();

    double time_all =
        std::chrono::duration<double, std::milli>(end_all - start_all).count();
    double time_p1 =
        std::chrono::duration<double, std::milli>(end_p1 - end_all).count();
    double time_p2 =
        std::chrono::duration<double, std::milli>(end_p2 - end_p1).count();

    file << n << ", " << time_all << ", " << time_p1 << ", " << time_p2 << "\n";

    std::cout << "n=" << n
              << ": getAll=" << time_all << "ms, getPerm1=" << time_p1
              << "ms, getPerm2=" << time_p2 << "ms\n";
  }

  return 0;
}
