// result: https://app.codility.com/demo/results/trainingT77WKP-39N/
// reference: https://github.com/wtsanshou/Coding/blob/master/Algorithm/Greedy/CodilityFloodDepth.md

int solution(vector<int> &A) {
    int n = A.size(), res = 0;
    vector<int> depths(n);
    int wall = A[0];
    for(int i=1; i<n-1; ++i)
    {
        if(A[i] > wall) wall = A[i];
        else depths[i] = wall - A[i];
    }
    
    wall = A[n-1];
    for(int i= n-2; i>0; --i)
    {
        if(A[i] > wall) 
        {
            wall = A[i];
            depths[i] = 0;
        }
        else depths[i] = min(wall-A[i], depths[i]);
        
        res = max(res, depths[i]);
    }
    return res;
}