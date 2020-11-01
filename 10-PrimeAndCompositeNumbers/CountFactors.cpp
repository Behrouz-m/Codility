int solution(int n) {
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    int div = 2; // one and itself
    long long x = 2;
    for (; x*x < n; x++)
    {
        if (n % x == 0)
            div += 2;
    }
    if (x * x == n)
        div++;
    return div;
}