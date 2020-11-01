// Reference: https://molchevskyi.medium.com/best-solutions-for-codility-lessons-lesson-6-sorting-770f931b65ad

#include <algorithm>

int solution(vector<int> &v) {

    const int v_size = v.size();
    if(v_size < 3)
		return 0;   
	std::sort(v.begin(), v.end());
    for (auto i = 2; i < v_size; ++i) {
        if (v[i - 2] > v[i] - v[i - 1]) {
            return 1;
        }
    }
    return 0;
}
