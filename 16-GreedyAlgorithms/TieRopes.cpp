// result: https://app.codility.com/demo/results/trainingAF5XHH-VBA/

int solution(vector<int>& A, int K) {
    int count = 0;
    int rop_sum = 0;
    for (int i = 0; i < A.size(); i++)
    {
        rop_sum += A[i];
        if (rop_sum >= K) {
            count++;
            rop_sum = 0;
        }

    }
    return count;
}