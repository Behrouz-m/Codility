// #define debug

#ifdef debug
    #define LOG(X) cout << X << endl
#else
    #define LOG(X) (void)0
#endif

int solution1(vector<int> &A) {
    if(A.size() == 1)
        return 0;
        
    if(A.size() == 2) {
        if(A[0] == 0 && A[1] == 1)
            return 1;
        else
            return 0;
    }
    vector<int> suffix_sum(A.size()+1, 0);
    
    int one_counts = 0;
    for(int i=suffix_sum.size()-2; i>=0; i--)
    {
        if(A[i] == 1)
            one_counts++;
            
        suffix_sum[i] =  suffix_sum[i+1] + ((A[i] == 0) ? one_counts : 0);
        
        if(suffix_sum[i] > 1'000'000'000)
            return -1;
            
        LOG("suffix_sum[" << i << "]=" << suffix_sum[i]);
    }
    return suffix_sum[0];
    
}

int solution2(vector<int> &A) {
    size_t v_size = A.size();
    size_t pairs_passed_by = 0;
    size_t zeroes = 0;
    for(size_t i = 0; i < v_size; ++i) {
        if(0 == A[i]) {
            ++zeroes;
        }
        else if(1 == A[i]) {
            pairs_passed_by += zeroes;
            if(pairs_passed_by > 1'000'000'000) {
                return -1;
            }
        }
    }
    return pairs_passed_by;
}