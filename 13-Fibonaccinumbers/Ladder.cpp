#include <algorithm>

// result: https://app.codility.com/demo/results/training36DCSY-F7Q/

vector<int> solution(vector<int> &A, vector<int> &B) {
    size_t maxB = *std::max_element(B.begin(), B.end());
    size_t maxA = *std::max_element(A.begin(), A.end());
	
    vector<int> L(A.size(), 0);
    vector<size_t> fib(maxA + 2, 0);
    fib[1] = 1;
	
    for (size_t i = 2; i < maxA + 2; i++)
        fib[i] = (fib[i - 1] + fib[i - 2]) & ((1 << maxB)-1);

    for (size_t i = 0; i < A.size(); i++) {
        size_t mask = (1 << B[i]) - 1;
        L[i] = fib[A[i] + 1] & mask;
    }

    return L;
}
