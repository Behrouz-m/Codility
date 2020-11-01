int solution(vector<int> &A) {
    vector<int> B(A.size()+1, 0);
    
    for(size_t i = 0; i < A.size(); i++)
        B[A[i]-1] = 1;
    
    for(size_t i=0; i < B.size(); i++)
        if(B[i] == 0)
            return i+1;
        
    return 0;
}
