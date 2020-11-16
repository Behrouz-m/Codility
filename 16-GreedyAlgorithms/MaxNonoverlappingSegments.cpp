// result: https://app.codility.com/demo/results/trainingZRX235-MH6/

int solution(vector<int>& A, vector<int>& B) {
    if (A.size() == 0)
        return 0;
    int count = 1;
    int prev_end = B[0];
    for (int i = 1; i < A.size(); i++)
        if (A[i] > prev_end) {
            count++;
            prev_end = B[i];
        }

    return count;
}