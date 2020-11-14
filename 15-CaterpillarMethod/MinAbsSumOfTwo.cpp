//result: https://app.codility.com/demo/results/trainingU93EQN-9A2/

#include <algorithm>
#include <climits>

int solution(vector<int> &A) {
    if (A.size() == 1)
        return abs(A[0] + A[0]);

    sort(A.begin(), A.end());

    int total_min = *min_element(A.begin(), A.end());
    if (total_min >= 0)
        return 2 * A[0];

    int minimal_sum = INT_MAX;
    auto P = A.begin();
    auto Q = A.end()-1;
    while (P < Q) {
        minimal_sum = min(minimal_sum, abs(*P + *Q));
        minimal_sum = min(minimal_sum, abs(*P + *P));
        minimal_sum = min(minimal_sum, abs(*Q + *Q));

        if (abs(*(P + 1) + *Q) <= abs(*P + *(Q - 1)))
            P++;
        else      
            Q--;
    }
    minimal_sum = min(minimal_sum, abs(*P + *Q));
    return minimal_sum;
}
