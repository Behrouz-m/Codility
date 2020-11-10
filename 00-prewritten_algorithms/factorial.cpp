vector<uint64_t> getFactorial(int n) {
    vector<uint64_t> f(n+1, 0);
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        f[i] = f[i - 1] * i;
    return f;
}
