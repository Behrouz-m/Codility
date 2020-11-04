
vector<int> getFactArr(int n) {
    vector<int> f(n+1, 0);
    f[1] = 1;
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

vector<int> solution(int N, vector<int> &P, vector<int> &Q) {
    vector<int> F = getFactArr(N);
    vector<int> prefix_semi_primes(N + 1, 0);

    for (int x = 1; x <= N; x++) {
        if (F[x] > 0 && F[x / F[x]] == 0)
            prefix_semi_primes[x]++;
        prefix_semi_primes[x] += prefix_semi_primes[x - 1];
    }

    const int M = P.size();
    vector<int> ans(M, 0);
    for (int i = 0; i < M; i++) {
        ans[i] = prefix_semi_primes[Q[i]] - prefix_semi_primes[P[i] - 1];
    }

    return ans;
}
