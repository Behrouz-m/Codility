int gcdByDivision(int A, int B) {
    if (A % B == 0)
        return B;
    else
        return gcdByDivision(B, A % B);
}

int solution(int N, int M) {
    return N / gcdByDivision(N, M);
}
