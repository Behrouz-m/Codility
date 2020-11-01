int solution(vector<int> &A) {

    vector<bool> c(1'000'000 + 1, false);
    for(int i : A) {
        if(i>0)
            c[i] = true;
    }
    for(int i=1; i<=1'000'000; i++)
        if(c[i] == false)
            return i;
    return 1;
}
