void counting_sort(vector<int> &A, int min, int max) {
    int offset = 0;
    if(min < 0)
        offset = -min;
    int size = max - min + 1;
    vector<int> count(size, 0);
    for(int i : A)
        count[i + offset] +=1;
        
    int p = 0;
    for(size_t j = 0; j<count.size(); j++)
    {
        for(int i=0; i<count[j]; i++)
            A[p++] = j - offset;
    }
}