int solution(vector<int> &A) {

    int N = A.size();
    vector<int> B(N+1, 0);
    
    for(int i=0; i<N; i++)
    {
        if(A[i] <= N)
            B[A[i]] += 1;
    }
    
    for(size_t j=1; j<B.size(); j++) {
        // cout << "B[" << j << "]=" << B[j] << endl;
        if(B[j] == 0 || B[j] > 1)
            return 0;
    }
    return 1;
}
