#include <stack>

// #define debug

#ifdef debug
    #define LOG(X) cout << X << endl
#else
    #define LOG(X) (void)0
#endif

int solution(vector<int> &H) {
    if(H.size() == 1)
        return 1;
    
    int count = 0;
    stack<int> W;
    int current_h = 0;
    
    for(auto h : H) {
        if(W.empty()) {
            W.push(h);
            current_h = h;
            LOG(current_h);
            count++;
        } else if(current_h == h) {
            continue;
        } else if(current_h < h) {
            LOG(h - current_h);
            W.push(h - current_h);
            current_h = h;
            count++;
        } else {
            while(!W.empty() && current_h > h) {
                current_h -= W.top();
                W.pop();
            }
            if(!W.empty() && current_h < h) {
                LOG(h - current_h);
                W.push(h - current_h);
                current_h = h;
                count++;
            }
            if(W.empty()) {
                W.push(h);
                current_h = h;
                LOG(current_h);
                count++;
            }
        }
    }
    return count;
}

// ref: https://molchevskyi.medium.com/best-solutions-for-codility-lessons-lesson-7-stacks-and-queues-ef1415898cb
int solution2(const vector<int> &v) {
    std::stack<int> stack;
    int stones = 0;
	for (auto height : v) {
        while (!stack.empty() && stack.top() > height) {
            stack.pop();
        }
        if (!stack.empty() && stack.top() == height) {
            continue;
        }
        stones++;
        stack.push(height);
    }
    return stones;
}
