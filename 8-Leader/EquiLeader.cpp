#include <stack>
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


int solution(vector<int> &A) {
    if(A.size() == 1)
        return 0;
    
    int equi_count = 0;
    pair<int,int> leader = getLeader(A);
    if(leader == make_pair(-1, 0))
        return 0;
        
    size_t leader_count_left = 0;
    size_t leader_count_right = leader.second;
    
    for(size_t i=0; i<A.size(); i++)
    {
        if(A[i] == leader.first) {
            leader_count_left++;
            leader_count_right--;
            LOG("leader_count_left=" << leader_count_left << "\tleader_count_right=" << leader_count_right);
        }
        
        if(leader_count_left > (i+1)/2 &&
            leader_count_right > (A.size()-i-1)/2)
            equi_count++;
    }
    
    return equi_count;
}
