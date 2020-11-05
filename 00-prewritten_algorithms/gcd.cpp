// call it with gcd(a, b, 1) to calculate gcd(a,b)

int gcd(int a, int b, int res) {
    if (a == b)
        return res * a;
    else if ((a % 2 == 0) and (b % 2 == 0))
        return gcd(a / 2, b / 2, 2 * res);
    else if (a % 2 == 0)
        return gcd(a / 2, b, res);
    else if (b % 2 == 0)
        return gcd(a, b / 2, res);
    else if (a > b)
        return gcd(a - b, b, res);
    else
        return gcd(a, b - a, res);
}

int gcdByDivision(int A, int B) {
    if (A % B == 0)
        return B;
    else
        return gcdByDivision(B, A % B);
}
