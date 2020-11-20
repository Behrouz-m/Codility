#include <climits>
// results (100%):  https://app.codility.com/demo/results/training8JYZDW-UFC/

int solution(vector<int>& A) {
    const int N = A.size();
    if (N == 2)
        return A[0] + A[1];

    vector<int> MaxSum(N, INT_MIN);
    MaxSum[0] = A[0];
    for (int i = 1; i < N; i++) {
        for (int dice = 1; dice <= 6; dice++) {
            if (dice > i)
                break;
            MaxSum[i] = max(MaxSum[i], A[i] + MaxSum[i - dice]);
        }
    }
    return MaxSum[N-1];
}