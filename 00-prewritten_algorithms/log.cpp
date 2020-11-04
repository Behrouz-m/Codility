#define debug

#ifdef debug
    #define LOG(X) cout << X << endl
#else
    #define LOG(X) (void)0
#endif
