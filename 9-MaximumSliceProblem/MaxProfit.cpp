int solution(vector<int> &A) {
    size_t n = A.size();
    if (n == 0)
        return 0;
    int max_profit = 0;
    vector<int> profit_sum(n);
    for (size_t i = 1; i < n; i++) {
        profit_sum[i] = max(0, profit_sum[i-1] + A[i] - A[i - 1]);
        max_profit = max(max_profit, profit_sum[i]);
    }

    return max_profit;
}