#include <math.h>

int solution(int X, int Y, int D) {
    return ceil((Y-X) / (double)D);
}