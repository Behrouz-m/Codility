// Result: https://app.codility.com/demo/results/training37M7VV-A7W/

#include <cmath>
#include <climits>

int solution(vector<int> &A) {
	auto begin = A.begin();
    auto end = A.end()-1;
    int dist_count = 1;
    int64_t last = INT64_MAX;
    while (begin <= end) {
		// using int64_t to avoid arithmatic overflow in test cases!
        int64_t abs_begin = abs(static_cast<int64_t>(*begin));
        int64_t abs_end = abs(static_cast<int64_t>(*end));
        if (abs_begin != abs_end && *begin != last && *end != last) {
            dist_count++;
            if (abs_begin > abs_end) {
                last = *begin;
                begin++;
            }
            else {
                last = *end;
                end--;
            }
        }
        else {
            if (begin == end)
                break;
            if (*begin == last || last == INT64_MAX)
                begin++;
            else if (*end == last || last == INT64_MAX)
                end--;
            else
                last = INT64_MAX;
        }
    }

    return dist_count;
}


#include <unordered_set>

int solution1(vector<int> &A) {
    unordered_set<int> s;
    s.reserve(A.size());
    for(auto i : A)
        s.insert((int)abs(i));
        
    return s.size();
}

