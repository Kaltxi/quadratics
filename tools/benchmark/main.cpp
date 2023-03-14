#include "benchmarks.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace quadratics;

int main(int arg_count, char* args[]) {
  std::ios_base::sync_with_stdio(false);

  std::vector<std::string> results;

  // Skipping the first arg which contains program's name
  results.push_back(bench_runtime(arg_count - 1, args + 1));
  results.push_back(bench_solve());
  results.push_back(bench_parser_and_solver_serial(arg_count - 1, args + 1));
  results.push_back(bench_thread());
  print_vec(results);

  return 0;
}
