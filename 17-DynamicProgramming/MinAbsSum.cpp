// reference: https://github.com/Behrouz-m/Codility/blob/master/Docs/solutions/solution-min-abs-sum.pdf
// O(N^2.M)
// result=72% : https://app.codility.com/demo/results/trainingQW8QE8-SDF/
int solution(vector<int>& A) {
    const int N = A.size();
    if (N == 0)
        return 0;

    int MaxVal = 0;
    for (int i = 0; i < N; i++) {
        A[i] = abs(A[i]);
        MaxVal = max(MaxVal, A[i]);
    }

    const int Sum = std::accumulate(A.begin(), A.end(), 0);
    
    vector<int> dp(Sum + 1, 0);
    dp[0] = 1;
    for (int j = 0; j < N; j++)
        for (int i = Sum; i > -1; i--)
            if (dp[i] == 1 and i + A[j] <= Sum)
                dp[i + A[j]] = 1;
    int result = Sum;
    for (int i = 0; i < Sum / 2 + 1; i++)
        if (dp[i] == 1)
            result = min(result, Sum - 2 * i);
    return result;
}

// O(N.M^2)
// result=100% = https://app.codility.com/demo/results/training226XH9-8VA/

int solution_golden(vector<int>& A) {
    const int N = A.size();
    if (N == 0)
        return 0;
   
    int MaxVal = 0;
    for (int i = 0; i < N; i++) {
        A[i] = abs(A[i]);
        MaxVal = max(MaxVal, A[i]);
    }

    const int Sum = std::accumulate(A.begin(), A.end(), 0);
    vector<int> count(MaxVal + 1, 0);
    for (int i = 0; i < N; i++)
        count[A[i]]++;

    vector<int> dp(Sum + 1, -1);
    dp[0] = 0;
    for (int a = 1; a <= MaxVal; a++) {
        if (count[a]>0) {
            for (int j = 0; j < Sum; j++) {
                if (dp[j] >= 0)
                    dp[j] = count[a];
                else if (j >= a && dp[j - a] > 0)
                    dp[j] = dp[j - a] - 1;
            }
        }
    }
    int result = Sum;
    for (int i = 0; i < Sum / 2 + 1; i++) {
        if (dp[i] >= 0)
            result = min(result, Sum - 2 * i);
    }

    return result;
}