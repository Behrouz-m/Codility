int traverse(tree * t, int h) {
    if(t->l || t->r)
        h++;
    int h_l = h;
    int h_r = h;
    if(t->l)
        h_l = traverse(t->l, h);
    if(t->r)
        h_r = traverse(t->r, h);
    return max(h_l, h_r);
}

int solution(tree * T) {
    int h = 0;
    if(T)
        h = traverse(T, h);
    return h;
}
