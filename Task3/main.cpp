/*
 * III.
 * Отсортировать последовательность. Принять N = 50000000
 * Сравнить эффективность выполнения сортировки на основе шаблонов
 * std::sort, concurrency::parallel_sort и
 * concurrency::parallel_buffered_sort. В качестве контейнера для
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
    parallel_for(0, N, [&x](int n) { x[n] = cos(n); });
    std::vector<float> v(x);
    
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
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
