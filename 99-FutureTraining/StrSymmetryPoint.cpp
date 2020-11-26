
int solution(string &S) {
    int N = S.size();
    if(N == 0)
        return -1;
    if(N == 1)
        return 0;
    if(N%2 == 0)
        return -1;
	
    int mid = N / 2;
    for(int i = 1; i <= mid + 1; i++)
        if(S[mid + i] != S[mid - i])
            return -1;
    return mid;
}
