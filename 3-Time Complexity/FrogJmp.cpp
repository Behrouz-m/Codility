#include <math.h>

int solution(int X, int Y, int D) {
    return ceil((Y - X) / (double)D);
}

int solution2(int X, int Y, int D) {
    return (Y - X + D - 1) / D;
}