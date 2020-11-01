int solution1(vector<int> &A) {
    vector<bool> count(2000001, 0);
    for(size_t i=0; i<A.size(); i++)
        count[A[i] + 1000000] = true;
    
    int dis = 0;
    for(size_t i=0; i<count.size(); i++)
        if(count[i])
            dis++;
            
    return dis;
}

#include <unordered_set.h>

int solution2(vector<int> &v) {
    return std::unordered_set<int>(v.begin(), v.end()).size();
}
