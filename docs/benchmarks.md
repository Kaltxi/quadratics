# Benchmarks

Here is the list of benchmarks done during various points of development to
estimate the performance. The values are median of 10000 `rdtsc` readings.

|   Change   | Threaded 1 | Serial 1 | Serial 1 Garbage | Threaded 1000 | Serial 1000 | Solve 1 |
| :--------: | ---------- | :------: | :--------------: | :-----------: | ----------- | ------- |
|  b7ace5d7  | 450e3      |   940    |       2800       |      4e6      | 2.3e6       | 23      |
| stdio sync | 450e3      | **2800** |       2800       |   **8.3e6**   | **7.3e6**   | 23      |
|  charconv  | 450e3      |   850    |     **115**      |      4e6      | 2.5e6       | 23      |
