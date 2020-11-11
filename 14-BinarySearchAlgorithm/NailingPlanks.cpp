// result: https://app.codility.com/demo/results/trainingQVHXNU-A92/

bool CheckAllPlanksNailed(vector<int>& A, vector<int>& B, vector<int>& C, int nail_count) {

    vector<int> presum_nailed_status(2 * C.size() + 1, 0);

    for (int i = 0; i < nail_count; i++) {
        presum_nailed_status[C[i]] = 1;
    }

    for (size_t i = 1; i < presum_nailed_status.size(); i++) {
        presum_nailed_status[i] += presum_nailed_status[i - 1];
    }

    bool all_nailed = true;
    for (size_t i = 0; i < A.size() && all_nailed; i++) {
        all_nailed = presum_nailed_status[B[i]] - presum_nailed_status[A[i] - 1] > 0;
    }
    return all_nailed;
}

int solution(vector<int>& A, vector<int>& B, vector<int>& C) {
    
    int result = -1;

    int minNails = 1;
    int maxNails = C.size();

    while (minNails <= maxNails) {
        int mid = (maxNails + minNails) / 2;
        if (CheckAllPlanksNailed(A, B, C, mid)) {
            result = mid;
            maxNails = mid - 1;
        }
        else {
            minNails = mid + 1;
        }
    }

    return result;
}
