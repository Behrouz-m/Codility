// result: https://app.codility.com/demo/results/trainingG63GWF-RXZ/

int solution(string &S) {
    int let = 0;
    int dig = 0;
    int max_len = -1;
    S += ' ';
    bool valid = true;
    for (char s : S) {
        if (s >= 'a' && s <= 'z' ||
            s >= 'A' && s <= 'Z')
            let++;
        else if (s >= '0' && s <= '9')
            dig++;
        else if (s == ' ')
        {
            if (let % 2 == 0 and dig % 2 == 1 and valid) {
                max_len = max(let + dig, max_len);
            }
            let = 0;
            dig = 0;
            valid = true;
        }
        else {
            valid = false;
        }
    }
    return max_len;
}
