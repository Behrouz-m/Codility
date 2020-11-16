vector<int> getNext(vector<int>& A) {
    int n = A.size();
    vector<int> next(n+1, 0);
    next[n] = -1;
    for (int i = n - 1; i >= 0; i--)
        if (A[i] > 0)
            next[i] = i;
        else
            next[i] = next[i + 1];
    return next;
}
