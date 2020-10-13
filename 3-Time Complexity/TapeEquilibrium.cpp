#include <numeric>
#include <math.h>
#include <limits.h>

int solution(vector<int> &A) {
    int sum_r = std::accumulate(A.begin(), A.end(), 0);
    int min = INT_MAX;
    int sum_l = 0;
    for(size_t p=1; p<A.size(); p++)
    {
        sum_l += A[p-1];
        sum_r -= A[p-1];
        int dif = (int)abs(sum_l - sum_r);
        if(dif < min)
            min = dif;
    }
    return min;
}
