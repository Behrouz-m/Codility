#include <climits>

int solution(vector<int> &A) {
    size_t n = A.size();
    if (n == 0)
        return 0;
    int max_sum = INT_MIN;
    vector<int> sum_pre(n + 1, 0);

    for (size_t i = 1; i <= n; i++) {
        sum_pre[i] = max(sum_pre[i-1] + A[i-1], A[i-1]);
        max_sum = max(max_sum, sum_pre[i]);
    }

    return max_sum;
}
