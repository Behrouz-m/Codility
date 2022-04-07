// result: https://app.codility.com/demo/results/training2XYSK7-EK7/

#include <algorithm>

int solution(vector<int> &A) {
    if (A.size() < 3)
        return 0;
    int count = 0;
    sort(A.begin(), A.end());
    auto P = A.begin();

    while (P <= A.end()-3) {
        auto Q = P + 1;
        auto R = Q + 1;
        while (R < A.end()) {
            if (*P + *Q > *R) {
                count += R - Q;
                R++;
            }
            else if (Q < R - 1)
                Q++;
            else
                R++;
        }
        P++;
    }
    return count;
}
