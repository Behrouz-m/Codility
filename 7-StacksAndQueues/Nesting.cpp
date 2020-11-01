int solution(string &S) {

    if(S.empty())
        return 1;
    if(S.size() % 2)
        return 0;
        
    int open = 0;
    for(auto c : S) {
        if(c == '(') {
            open++;
        } else {
            if(open > 0)
                open--;
            else
                return 0;
        }
    }
    
    return open==0;
}