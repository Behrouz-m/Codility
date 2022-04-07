#include <climits>

int solution(vector<int> &A) {
    size_t n = A.size();
    if (n == 0)
        return 0;
    int max_sum = INT_MIN;
    int sum_pre = 0;

    for (size_t i = 1; i <= n; i++) {
        sum_pre = max(sum_pre + A[i-1], A[i-1]);
        max_sum = max(max_sum, sum_pre);
    }

    return max_sum;
}
