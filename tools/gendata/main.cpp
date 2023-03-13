#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

constexpr auto RANGE = 100;

std::string gen_num() {
  std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> dist(-RANGE, RANGE);
  return " " + std::to_string(dist(rng));
}

int main(int arg_count, char* args[]) {
  if (arg_count < 2) {
    std::cout << "Number of treys unspecified";
    return 1;
  }

  auto gen_times{0};

  try {
    gen_times = std::stoi(args[1]);
  } catch (const std::invalid_argument&) {
    std::cout << "Error parsing number of treys";
    return 1;
  }

  for (auto i = 0; i < gen_times; ++i) {
    std::cout << gen_num() << gen_num() << gen_num();
  }

  std::cout << std::endl;

  return 0;
}