#include <utility>
// #define debug

#ifdef debug
    #define LOG(X) cout << X << endl
#else
    #define LOG(X) (void)0
#endif

pair<int,int> getLeader(vector<int> &A) {
    int candidate = -1;
    int size = 0;
    
    for(size_t i=0; i<A.size(); i++) {
        if(size == 0) {
            size++;
            candidate = A[i];
        } else {
            if(candidate == A[i])
                size++;
            else
                size--;
        }
    }
    
    if(size > 0)
    {
        size_t count = 0;
        for(size_t i=0; i<A.size() ; i++) {
            if(A[i] == candidate) {
                count++;
            }
        }
        
        if(count > A.size() / 2) {
            LOG("candidate = " << candidate << " count = " << count);
            return make_pair(candidate, count);
        }
    }
    LOG("No candidate");
    return make_pair(-1,0);
}