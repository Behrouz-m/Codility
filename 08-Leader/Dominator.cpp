// #define debug

#ifdef debug
    #define LOG(X) cout << X << endl
#else
    #define LOG(X) (void)0
#endif

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    int candidate = -1;
    int size = 0;
    
    for(auto a : A) {
        if(size == 0) {
            size++;
            candidate = a;
        } else {
            if(candidate == a)
                size++;
            else
                size--;
        }
    }
    LOG("Size = " << size);
    LOG("candidate = " << candidate);
    if(size > 0)
    {
        int index = -1;
        size_t count = 0;
        for(size_t i=0; i<A.size() ; i++) {
            if(A[i] == candidate) {
                count++;
                if(index == -1)
                    index = i;
            }
        }
        
        if(count > A.size() / 2)
            return index;
    }
    return -1;
}
