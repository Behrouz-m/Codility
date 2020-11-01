#include <stack>

int solution(vector<int> &A, vector<int> &B) {

    if(A.size() == 1)
        return 1;
    int alive = A.size();
    
    stack<int> F;
    
    for(size_t i = 0; i<A.size(); i++) {
        if(B[i] == 1) {
            F.push(i);
        }
        else if(B[i] == 0 && !F.empty()) {
            while(!F.empty() && A[F.top()] < A[i]) {
                F.pop();
                alive--;
            }
            
            if(!F.empty() && A[F.top()] > A[i])
                alive--;
        }
    }
    
    return alive;
}
