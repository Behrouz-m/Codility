vector<int> solution(int N, vector<int> &A) {

    vector<int> c(N, 0);
    
    int max_c_val = 0;
    int max_current_c = 0;
    for(size_t i=0; i<A.size(); i++)
    {
        if(A[i] <= N) {
            c[A[i]-1] = max(max_current_c, c[A[i]-1]) + 1;
            if(c[A[i]-1] > max_c_val)
                max_c_val = c[A[i]-1];
        }
        else {
            max_current_c = max_c_val;
        }
    
    }
    
    for(int j=0; j<N; j++)
        c[j] = max(max_current_c, c[j]);
    return c;
}
