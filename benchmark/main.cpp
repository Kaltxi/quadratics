#include "benchmarks.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace quadratics;

int main(int size, char** input) {
  std::ios_base::sync_with_stdio(false);

  std::vector<std::string> results;
  results.push_back(bench_runtime(size, input));
  results.push_back(bench_solve());
  print_vec(results);

  return 0;
}
