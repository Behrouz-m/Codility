vector<int> fibs={0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025};

// only for N <=46
uint64_t getFibonacci(size_t N) {
    return static_cast<uint64_t>((pow((1.0 + sqrt(5)) / 2.0, N) - pow((1.0 - sqrt(5)) / 2.0, N)) / sqrt(5));
}

vector<uint64_t> getFibonacciArray(size_t N) {
    vector<uint64_t> fib(N + 2, 0);
    fib[1] = 1;
    for (size_t i = 2; i <= N + 1; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
    return fib;
}

vector<int> getFibonacciArrayMax(int MaxNum) {
    if (MaxNum == 0)
        return vector<int>(1, 0);
    vector<int> fib(2, 0);
    fib[1] = 1;
    for (int i = 2; fib[fib.size()-1] + fib[fib.size() - 2] <= MaxNum; i++)
        fib.push_back(fib[i - 1] + fib[i - 2]);
    return fib;
}