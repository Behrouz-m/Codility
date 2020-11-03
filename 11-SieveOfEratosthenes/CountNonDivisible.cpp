// ref: https://stackoverflow.com/a/21916916/365229
#include <algorithm>

vector<int> solution(vector<int> &A) {
    int N = A.size();
    vector<int> counts (*std::max_element(A.begin(), A.end()) + 1,0);

    // Calculate occurences of each number in the array
    for (int i = 0; i < N; ++i)
        counts[A[i]] += 1;


    std::vector<int> answer(N,0);

    // For each element of the array
    for (int i = 0; i < N; ++i)	{
        // Calulate how many of its divisors are in the array
        int divisors = 0;
		const int num = A[i];
        for (int j = 1; j * j <= num; ++j)	{
            if (num % j == 0)	{
                divisors += counts[j];
                if (num / j != j) {
                    divisors += counts[num / j];
				}
            }
        }

        // Subtract the number of divisors from the number of elements in the array
        answer[i] = N - divisors;
    }

    return answer;
}