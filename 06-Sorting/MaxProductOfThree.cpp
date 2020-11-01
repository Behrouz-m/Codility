// Source: https://molchevskyi.medium.com/best-solutions-for-codility-lessons-lesson-6-sorting-770f931b65ad

int solution(vector<int> &v) {

    vector<int> max_num(3,-1000);
    vector<int> min_neg(2,0);    
	const int v_size = v.size();    
	for (auto i = 0; i < v_size; ++i) {
        if (v[i] < min_neg[0] ) {
            min_neg[1]=min_neg[0];
            min_neg[0]=v[i];
        }
        else if (v[i] < min_neg[1]) {
            min_neg[1]=v[i];
        }
        if (v[i] > max_num[0]) {
            max_num[2]=max_num[1];
            max_num[1]=max_num[0];
            max_num[0]=v[i];
        }
        else if (v[i] > max_num[1]) {
            max_num[2]=max_num[1];
            max_num[1]=v[i];
        }
        else if (v[i] > max_num[2]) {
            max_num[2]=v[i];
        }
    }  
	
	auto res_neg = max_num[0] * min_neg[0] * min_neg[1];
    auto res_pos = max_num[0] * max_num[1] * max_num[2];
    return max (res_pos, res_neg);
}
