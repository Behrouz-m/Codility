// #define debug

#ifdef debug
    #define LOG(X) cout << X << endl
#else
    #define LOG(X) (void)0
#endif

int solution(vector<int> &A) {
    vector<int> pre_sum(A.size() + 1, 0);

    for(size_t i=1; i<=A.size(); i++)
        pre_sum[i] = (pre_sum[i-1] + A[i-1]);
    
    double min_av = 20000;
    int min_ix = -1;
    for(size_t i=1; i<A.size(); i++)
    {
        double avg = (pre_sum[i+1] - pre_sum[i-1]) / 2.0d;
        if(avg < min_av)
        {
            min_ix = i-1;
            min_av = avg;
            LOG("min_av=" << min_av << ", min-ix=" << min_ix << " i=" << i);
        }
        if(i+2 < pre_sum.size()) {
            avg = (pre_sum[i+2] - pre_sum[i-1]) / 3.0d;
            if(avg < min_av)
            {
                min_ix = i-1;
                min_av = avg;
                LOG("min_av=" << min_av << ", min-ix=" << min_ix << " i=" << i);
            }   
        }
    }

    return min_ix;
}
/*
    // O(N**2) solution for test purpose
    vector<int> pre_sum(A.size() + 1, 0);

    for(size_t i=1; i<=A.size(); i++)
        pre_sum[i] = (pre_sum[i-1] + A[i-1]);
    
    double min_av = 20000;
    int min_ix = -1;
    for(size_t i=1; i<A.size(); i++)
    {
        for(size_t j=i+1; j<=A.size(); j++)
        {
            float avg = (pre_sum[j] - pre_sum[i-1]) / (j-i+1);
            if(avg < min_av)
            {
                LOG("pre_sum[" << j << "]=" << pre_sum[j] << " pre_sum[" << i-1 << "]=" << pre_sum[i-1]);
                min_av = avg;
                min_ix = i-1;
                LOG("min_av=" << min_av << ", min-ix=" << min_ix << " i=" << i << " j="<< j);
            }
        }
    }*/