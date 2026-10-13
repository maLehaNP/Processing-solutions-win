/*
 * V.
 * Для последовательности значений 𝑥_𝑛 = 100cos(𝑛), реализовать
 * преобразование .... Принять 𝑁 = 1000. Сравнить
 * эффективность выполнения последовательной и параллельной версий программы. Для
 * распараллеливания вычислений использовать шаблонный класс Concurrency::task_group.
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ppl.h>
using namespace concurrency;
#define N 1000


inline float f(float x) {
    int scaledX = static_cast<int>(20 * fabs(x));
    int max = 20 >= scaledX ? 20 : scaledX;
    float accum = 0.0f;
    for (int k = 1; k <= max; k++) {
        for (int j = 1; j <= max; j++) {
            accum += ((x * x) / (x * x + k * k + j * j)) * cos((k + j) * x);
        }
    }
    return accum;
}


int main() {
    using namespace std::chrono_literals;
    std::vector<float> x(N);
    // Заполняем вектор
    parallel_for(1, N+1, [&x](int n) {
        x[n] = 100 * cos(n);
    });
    std::vector<float> v(x);

    std::cout << "V.\n";

    auto start = std::chrono::steady_clock::now();
    std::transform(v.begin(), v.end(), v.begin(), f);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "std::transform: " << elapsed.count() << " с\n";
    v = x;

    task_group TGr;
    start = std::chrono::steady_clock::now();
    for (int n = 0; n < N; n++)
        TGr.run([&v, n]() {
            v[n] = f(n);
        });
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "Concurrency::task_group: " << elapsed.count() << " с\n";

    return 0;
}
