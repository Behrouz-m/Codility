
int solution(int A, int B, int K) {
    if(A == B)
        return A % K == 0 ? 1 : 0;
        
    int b = B / K;
    int a = 0;
    
	if(A > 0)
        a = (A - 1) / K;
    else
        b++;

    return b - a;
}

