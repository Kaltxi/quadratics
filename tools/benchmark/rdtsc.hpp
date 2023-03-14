#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>

namespace quadratics {

template <typename F> uint64_t clocks_once(F&& func) {
  const auto t0 = __builtin_ia32_rdtsc();
  func();
  const auto t1 = __builtin_ia32_rdtsc();

  return t1 - t0;
}

template <typename F> double clocks(F&& func) {
  constexpr auto LOOPS = 10000;

  auto sum = 0.;

  for (size_t i = 0; i < LOOPS; ++i) {
    const auto t0 = __builtin_ia32_rdtsc();

    func();

    const auto t1 = __builtin_ia32_rdtsc();
    const auto elapsed = t1 - t0;
    sum += static_cast<double>(elapsed);
  }

  return sum / LOOPS;
}

template <typename F> std::pair<double, uint64_t> clocks_with_median(F&& func) {
  constexpr auto LOOPS = 1000;

  auto sum = 0.;
  std::array<uint64_t, LOOPS> readings;

  for (size_t i = 0; i < LOOPS; ++i) {
    const auto t0 = __builtin_ia32_rdtsc();

    func();

    const auto t1 = __builtin_ia32_rdtsc();
    const auto elapsed = t1 - t0;
    sum += static_cast<double>(elapsed);
    readings[i] = elapsed;
  }

  std::sort(readings.begin(), readings.end());

  return {sum / LOOPS, readings[LOOPS / 2]};
}

} // namespace quadratics