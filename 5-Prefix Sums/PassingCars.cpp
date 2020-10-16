// #define debug

#ifdef debug
    #define LOG(X) cout << X << endl
#else
    #define LOG(X) (void)0
#endif

int solution(vector<int> &A) {
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
        
        if(suffix_sum[i] > 1000000000)
            return -1;
            
        LOG("suffix_sum[" << i << "]=" << suffix_sum[i]);
    }
    return suffix_sum[0];
    
}
