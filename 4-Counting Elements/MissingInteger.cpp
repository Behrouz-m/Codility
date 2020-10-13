int solution(vector<int> &A) {
    size_t N = A.size();
    int max_val = 1000000;
    vector<bool> B(max_val+1, 0);
    
    for(size_t i=0; i<N; i++)
    {
        int t = A[i];
        if(t<0)
            t = 0;
        B[t] = 1;
    }
    for(size_t j=1; j<B.size(); j++)
        if(B[j] == 0)
            return j;
    
    return max_val + 1;
}
