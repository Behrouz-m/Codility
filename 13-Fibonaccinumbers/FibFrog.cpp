vector<int> getFibonacciArrayMax(int MaxNum) {
    if (MaxNum == 0)
        return vector<int>(1, 0);
    vector<int> fib(2, 0);
    fib[1] = 1;
    for (int i = 2; fib[fib.size()-1] + fib[fib.size() - 2] <= MaxNum; i++)
        fib.push_back(fib[i - 1] + fib[i - 2]);
    return fib;
}

int solution1(vector<int>& A) {
    int N = A.size();
    if (N == 0)
        return 1;
    A.push_back(1);
    N++;
    vector<int> f = getFibonacciArrayMax(N);
    const int oo = 1'000'000;
    vector<int> moves(N, oo);
    
    for (auto i : f)
        if (i - 1 >= 0 && A[i-1])
            moves[i-1] = 1;
    
    for (int pos = 0; pos < N; pos++) {
        if (A[pos] == 0)
            continue;

        for (int i = f.size()-1; i >= 0; i--) {
            if (pos + f[i] < N && A[pos + f[i]]) {
                moves[pos + f[i]] = min(moves[pos]+1, moves[pos + f[i]]);
            }
        }
    }
    if (moves[N - 1] != oo) {
        return moves[N - 1];
    }
    return -1;
}

#include <set>

int solution2(vector<int>& A) {
    int N = A.size();

    vector<int> fib = getFibonacciArrayMax(N);

    set<int> positions;
    positions.insert(N);
    for (int jumps = 1; ; jumps++)
    {
        set<int> new_positions;
        for (int pos : positions)
        {
            for (int f : fib)
            {
                // return jumps if we reach to the start point
                if (pos - (f - 1) == 0)
                    return jumps;
                
                int prev_pos = pos - f;
                
                // we do not need to calculate bigger jumps.
                if (prev_pos < 0)
                    break;
                
                if (prev_pos < A.size() && A[prev_pos])
                    new_positions.insert(prev_pos);
            }
        }
        if (new_positions.size() == 0)
            return -1;
        positions = new_positions;
    }

    return -1;
}