int solution(vector<int> &A) {
    vector<int> sum_pref(A.size(), 0);
    vector<int> sum_suff(A.size(), 0);
    if (A.size() == 3)
        return 0;

    for (size_t a = 1; a < A.size() - 1; a++) {
        sum_pref[a] = max(sum_pref[a - 1] + A[a], 0);
    }

    for (size_t a = A.size() - 2; a > 0; a--) {
        sum_suff[a] = max(sum_suff[a + 1] + A[a], 0);
    }

    int double_slice = 0;
    for (size_t a = 1; a < A.size() - 1; a++) {
        double_slice = max(double_slice, sum_pref[a - 1] + sum_suff[a + 1]);
    }
    return double_slice;
}