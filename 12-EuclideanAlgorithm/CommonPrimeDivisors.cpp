// ref https://github.com/ZRonchy/Codility/blob/master/Lesson10/CommonPrimeDivisors.java

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

int gcd(int a, int b) {
    return gcd(a, b, 1);
}

bool hasSamePrimeDivisors(int a, int b) {
    int gcdValue = gcd(a, b);
    int gcdA;
    int gcdB;
    while (a != 1) {
        gcdA = gcd(a, gcdValue);
        if (gcdA == 1)
            break;
        a = a / gcdA;
    }
    if (a != 1) {
        return false;
    }
    while (b != 1) {
        gcdB = gcd(b, gcdValue);
        if (gcdB == 1)
            break;
        b = b / gcdB;
    }
    return b == 1;
}

int solution(vector<int>& A, vector<int>& B) {
    int count = 0;
    for (size_t i = 0; i < A.size(); i++) {
        if (hasSamePrimeDivisors(A[i], B[i])) {
            count++;
        }
    }
    return count;
}
