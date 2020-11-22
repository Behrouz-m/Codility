//result: https://app.codility.com/demo/results/trainingNVUJ8Y-WWA/

vector<int> solution(string &S, vector<int> &P, vector<int> &Q) {
    vector<int> res;
    int N = S.size();
    vector<int> A(N + 1, 0);
    vector<int> C(N + 1, 0);
    vector<int> G(N + 1, 0);
    vector<int> T(N + 1, 0);

    for (int i = 0; i < N; i++) {
        A[i + 1] = A[i] + (S[i] == 'A' ? 1 : 0);
        C[i + 1] = C[i] + (S[i] == 'C' ? 1 : 0);
        G[i + 1] = G[i] + (S[i] == 'G' ? 1 : 0);
        T[i + 1] = T[i] + (S[i] == 'T' ? 1 : 0);
    }
    for (size_t i = 0; i < P.size(); i++) {
        if (A[Q[i]+1]-A[P[i]] > 0)
            res.push_back(1);
        else if (C[Q[i] + 1] - C[P[i]] > 0)
            res.push_back(2);
        else if (G[Q[i] + 1] - G[P[i]] > 0)
            res.push_back(3);
        else if (T[Q[i] + 1] - T[P[i]] > 0)
            res.push_back(4);
    }
    return res;
}
