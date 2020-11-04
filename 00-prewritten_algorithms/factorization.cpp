vector<int> getFactArr(int n) {
    vector<int> f(n+1, 0);
    int i = 2;
    while (i * i <= n) {
        if (f[i] == 0) {
            int k = i * i;
            while (k <= n) {
                if (f[k] == 0)
                    f[k] = i;
                k+=i;
            }
        }
        i++;
    }
    return f;
}

vector<int> factorization(int x) {
    vector<int> primeFactors;
    vector<int> F = getFactArr(x);
    while (F[x] > 0) {
        primeFactors.push_back(F[x]);
        x /= F[x];
    }
    primeFactors.push_back(x);
    
    return primeFactors;
}
