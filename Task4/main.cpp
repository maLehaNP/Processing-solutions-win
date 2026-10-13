/*
 * IV.
 * Отсортировать последовательность. Принять N = 50000000
 * Сравнить эффективность выполнения сортировки на основе шаблонов
 * std::sort, concurrency::parallel_sort и
 * concurrency::parallel_buffered_sort и
 * concurrency::parallel_radixsort. В качестве контейнера для
 * хранения последовательности использовать вектор std::vector.
 */

#include <iostream>
#include <ppl.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace concurrency;
#define N 50000000


int main()
{
    using namespace std::chrono_literals;
    std::vector<float> x(N);
    // Заполняем вектор
    parallel_for(0, N, [&x](int n) {
        x[n] = 4 * 10e9 * abs(cos(n));
    });
    std::vector<float> v(x);

    std::cout << "IV.\n";

    auto start = std::chrono::steady_clock::now();
    std::sort(v.begin(), v.end());
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "std::sort: " << elapsed.count() << " с\n";
    v = x;

    start = std::chrono::steady_clock::now();
    parallel_sort(v.begin(), v.end());
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "parallel_sort: " << elapsed.count() << " с\n";
    v = x;

    start = std::chrono::steady_clock::now();
    parallel_buffered_sort(v.begin(), v.end());
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "parallel_buffered_sort: " << elapsed.count() << " с\n";
    v = x;

    start = std::chrono::steady_clock::now();
    parallel_radixsort(v.begin(), v.end(), [](const float& i) {
        return static_cast<size_t>(i);  // i - 0
    });
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "parallel_radixsort: " << elapsed.count() << " с\n";

    return 0;
}
