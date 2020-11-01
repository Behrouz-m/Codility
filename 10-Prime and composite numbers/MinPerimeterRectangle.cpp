#include <algorithm>
#include <climits>
#include <cmath>

int solution(int N) {
    int min_p = INT_MAX;
    int i = (int)sqrt(N) + 1;
    while(i >= 1) {
        if(N % i == 0) {
            min_p = min(min_p, N / i + i);
        }
        i--;
    }
    return 2 * min_p;
}
