vector<bool> getPeaks(vector<int>& A)
{
    int n = A.size();
    vector<bool> P(A.size(), false);
    
    for (int x = 1; x < n - 1; x++)
        if (A[x] > A[x - 1] && A[x] > A[x + 1])
            P[x] = true;

    return P;
}

vector<int> getNext(vector<int> &A, vector<bool> &peaks) {
    vector<int> next(A.size(), 0);
    next[A.size()-1] = -1;
    for (int i = A.size() - 2; i >= 0; i--) {
        if (peaks[i])
            next[i] = i;
        else
            next[i] = next[i + 1];
    }
    return next;
}

int solution(vector<int>& A) {
    if (A.size() < 3) return 0;
    const int N = A.size();
    vector<bool> P = getPeaks(A);
    vector<int> next = getNext(A, P);
    int max_flags = 0;
    for (int d = 1; d * (d-1) <= N; d++)
    {
        int current_flags = 0;
        int pos = 0;
        while (pos < N && current_flags < d) {
            pos = next[pos];
            if (pos == -1)   //end
                break;
            pos += d;
            current_flags++;
        }
        max_flags = max(max_flags, current_flags);
    }

    return max_flags;
}