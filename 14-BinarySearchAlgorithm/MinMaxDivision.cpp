#include <numeric>
#include <algorithm>

// result: https://app.codility.com/demo/results/training4NW8N5-TKB/

bool check(vector<int>& A, int K_MaxBlockCount, int MidSumCandidate) {
    int blocks = 1;
    int sum = 0;
    for (auto i : A) {
        sum += i;
        if (sum > MidSumCandidate) {
            blocks++;
            sum = i;
        }
        if (blocks > K_MaxBlockCount)
            return false;
    }
    return true;
}

// NOTE: do not use M, it is incorrect in some test cases.
//       you need to calculate it yourself

int solution(int K_MaxBlockCount, int /*M*/, vector<int> &A) {
    // using binary search to find optimum block counts
    // minimum large sum
    int min_sum = *std::max_element(A.begin(), A.end());
    // maximum large sum
    int max_sum = std::accumulate(A.begin(), A.end(), 0);

    if (A.size() == 1)
        return min_sum;
    if (K_MaxBlockCount == 1)
        return max_sum;

    while (min_sum <= max_sum) {
        int mid_sum_candidate = (min_sum + max_sum) / 2;
        // check if we can make maximum possible blocks (<K) that have maximum large sum up to mid_sum_candidate
        if (check(A, K_MaxBlockCount, mid_sum_candidate)) {    
            max_sum = mid_sum_candidate - 1;
        }
        else {
            min_sum = mid_sum_candidate + 1;
        }
    }
    return min_sum;
}
