// Задание II

#include <iostream>
#include <cmath>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <chrono>
#include <ppl.h>

using namespace concurrency;

#define N 2000


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

    std::vector<float> X(N);
    std::deque<float>  deq(N);
    std::list<float>   lst;

    // Заполняем массивы значениями X_n
    for (int n = 0; n < N; n++) {
        X[n] = 100.0f * cos(n);
        deq[n] = X[n];
        lst.push_back(X[n]);
    }
    std::vector<float> vec(X);

    std::cout << "std::transform:\n";

    auto start = std::chrono::steady_clock::now();
    std::transform(vec.begin(), vec.end(), vec.begin(), f);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "vector: " << elapsed.count() << " с\n";

    start = std::chrono::steady_clock::now();
    std::transform(deq.begin(), deq.end(), deq.begin(), f);
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "deque: " << elapsed.count() << " с\n";

    start = std::chrono::steady_clock::now();
    std::transform(lst.begin(), lst.end(), lst.begin(), f);
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "list: " << elapsed.count() << " с\n";

    vec = X;
    for (int n = 0; n < N; n++)
        deq[n] = X[n];
    int n = 0;
    for (float item : lst)
        item = X[n++];

    std::cout << "concurrency::parallel_transform:\n";

    start = std::chrono::steady_clock::now();
    parallel_transform(vec.begin(), vec.end(), vec.begin(), f);
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "vector: " << elapsed.count() << " с\n";

    start = std::chrono::steady_clock::now();
    parallel_transform(deq.begin(), deq.end(), deq.begin(), f);
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "deque: " << elapsed.count() << " с\n";

    start = std::chrono::steady_clock::now();
    parallel_transform(lst.begin(), lst.end(), lst.begin(), f);
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "list: " << elapsed.count() << " с\n";

    return 0;
}
