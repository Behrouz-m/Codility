int solution(vector<int> &A) {
    size_t n = A.size();
    if (n == 0)
        return 0;
    int max_profit = 0;
    int profit_sum = 0;
    for (size_t i = 1; i < n; i++) {
        profit_sum = max(0, profit_sum + A[i] - A[i - 1]);
        max_profit = max(max_profit, profit_sum);
    }

    return max_profit;
}