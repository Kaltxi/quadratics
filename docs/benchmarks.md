# Benchmarks

Here is the list of benchmarks done during various points of development to
estimate the performance. The values are median of 1000 `rdtsc` readings.

Measurements were done on a development laptop plugged in, with 6/12 core
AMD Ryzen 5600.

|       Change        | Threaded 1 | Serial 1 | Serial 1 Garbage | Threaded 1000 | Serial 1000 | Solve 1 |
| :-----------------: | ---------- | :------: | :--------------: | :-----------: | ----------- | ------- |
|      b7ace5d7       | 450e3      |   940    |       2800       |      4e6      | 2.3e6       | 23      |
|     stdio sync      | 450e3      | **2800** |       2800       |   **8.3e6**   | **7.3e6**   | 23      |
|     from_chars      | 450e3      |   850    |     **115**      |      4e6      | 2.5e6       | 23      |
|    batches (50)     | 480e3      |   950    |     **184**      |   **1.5e6**   | **2.4e6**   | 23      |
|  solution refactor  | **560e6**  |   950    |       184        |     1.4e6     | **2.1e6**   | 23      |
|   linux 1 solver    | 75e6       |   950    |       184        |     2.1e6     | 2.1e6       | 23      |
|   linux 2 solvers   | 90e6       |   950    |       184        |     1.4e6     | 2.1         | 23      |
|   linux 5 solvers   | 200e6      |   950    |       184        |     1.2e6     | 2.1e6       | 23      |
|  linux 11 solvers   | 500e6      |   950    |       184        |     1.4e6     | 2.1e6       | 23      |
| batch-aware threads | **85e6**   |   950    |       250        |     1.4e6     | 2.1e6       | 23      |
|   float to_chars    | 85e6       |   950    |       250        |  **1.25e6**   | **1.5e6**   | 23      |
