
int solution(int X, vector<int> &A) {
    vector<int> B(X+1,0);
    for(size_t i=0; i<A.size(); i++)
    {
        if(B[A[i]] == 0) {
            X--;
            if(X == 0)
                return i;
        }
        B[A[i]] += 1;
    }
    return -1;
}