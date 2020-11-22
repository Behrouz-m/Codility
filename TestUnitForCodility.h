#pragma once

// this test unit has been developed specially for Codility
// by Behrouz Mohammadi

#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>
#include <time.h>
#include <functional>
#include <numeric>
#include <random>

using namespace std;

#define debug

#ifdef debug
#define LOG(X) cout << X << endl
#else
#define LOG(X) (void)0
#endif

template<typename T>
T random(const T range_from, const T range_to) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<T>    distr(range_from, range_to);
    return distr(generator);
}

template<typename T>
ostream& operator<<(ostream& s, vector<T> v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        s << v[i];
        if (i < v.size() - 1)
            s << ", ";
    }
    cout << "]";
    return s;
}

template<typename T>
void log_array(vector<T>& A) {
    cout << "array = " << A << endl;
}

#include <memory>

class Array2D {
    size_t _rows;
    size_t _columns;
    std::unique_ptr<int[]> data;

public:
    Array2D(size_t rows, size_t columns)
        : _rows{ rows },
        _columns{ columns },
        data{ std::make_unique<int[]>(rows * columns) } {}

    size_t rows() const { return _rows; }

    size_t columns() const { return _columns; }

    int* operator[](size_t row) { return row * _columns + data.get(); }

    int& operator()(size_t row, size_t column) {
        return data[row * _columns + column];
    }
};

template<typename T=int>
class ArrayInfo {
public:
    using AfterInit = std::function<void(vector<T>& init_vector)>;

    ArrayInfo() {}

    ArrayInfo(const T minV, const T maxV, bool unique = false, const AfterInit afterInit = nullptr) {
        _minV = minV;
        _maxV = maxV;
        _unique = unique;
        _afterInit = afterInit;
    }

    vector<T> Make(size_t size) {
        return Make(size, _minV, _maxV);
    }

    vector<T> Make(size_t size, T minV, T maxV)
    {
        if (_unique && static_cast<size_t>(_maxV - _minV + 1) < size)
            throw exception("Invalid range");

        vector<T> a(size);
        for (size_t i = 0; i < size; i++) {
            a[i] = static_cast<T>(random(static_cast<int64_t>(_minV), static_cast<int64_t>(_maxV)));
            if (_unique) {
                for (size_t j = 0; j < i; j++)
                    if (a[j] == a[i])
                        i--;
            }
        }
        if (_afterInit)
            _afterInit(a);
        return a;
    }

    T Max() { return _maxV; }
    T Min() { return _minV; }
    bool UniqueValues() { return _unique; }

private:
    AfterInit _afterInit = nullptr;
    T _minV = T();
    T _maxV = T();
    bool _unique = false;
};

template<typename T=int>
class VarInfo {
public:
    using AfterInit = function<void(T&)>;

    VarInfo(const T minV, const T maxV, const AfterInit afterInit = nullptr) {
        _minV = minV;
        _maxV = maxV;
        _afterInit = afterInit;
    }

    T Make() {
        return Make(_minV, _maxV);
    }

    T Make(T minV, T maxV) {
        T v = random(_minV, _maxV);
        if (_afterInit)
            _afterInit(v);
        return v;
    }
    
    T Max() { return _maxV; }
    T Min() { return _minV; }

private:
    AfterInit _afterInit;
    T _minV;
    T _maxV;
};

template<typename RET>
class TestBase {
public:
    bool virtual AutoTest(size_t test_count, size_t minN, size_t maxN) = 0;
    bool virtual IsEqual(RET& sln, RET& dummy) { return sln == dummy; }
};

template<typename A1=int, typename RET=int>
class Test_1a : public TestBase<RET> {
public:
    using Sln = function<RET(vector<A1>&)>;
    using BeforeRunningEachTest = function<void(vector<A1>&, const ArrayInfo<A1>&)>;

    Test_1a(const Sln& dummy_sln, const Sln& sln, const ArrayInfo<A1>& arr_info) :
        _dummy_sln(dummy_sln),
        _sln(sln),
        _arr_info(arr_info)
    {}
    
    void SetBeforeRunningEachTestCallback(const BeforeRunningEachTest beforeRunningEachTest) {
        _beforeRunningEachTest = beforeRunningEachTest;
    }

    bool Test(vector<A1> a1) {
        RET rdum = _dummy_sln(a1);
        LOG("Dummy test passed.");
        RET rsln = _sln(a1);
        if (rsln != rdum) {
            LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
            log_array(a1);
            return false;
        }
        LOG("Manual test passed.");
        return true;
    }
    

    bool Test(vector<A1> a1, RET result) {
        RET rdum = _dummy_sln(a1);
        if (rdum != result) {
            LOG("Dummy test failed: Dummy: " << rdum << " != " << result << " :answer");
            log_array(a1);
            return false;
        }
        else {
            LOG("Dummy test passed.");
            RET rsln = _sln(a1);
            if (rsln != rdum) {
                LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
                log_array(a1);
                return false;
            }
            LOG("Manual test passed.");
            return true;
        }
    }

    bool AutoTest(size_t test_count, size_t minN, size_t maxN) {
#ifdef debug
        size_t test_number = 100000;
        const size_t test_groups = 3;
        // check low boundry
        for (size_t test = 0; test <= 5; test++) {
            vector<A1> a = _arr_info.Make(minN + test);
            if (!caller(a, test_number))
                return false;
            test_number++;
        }

        test_number = 200000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a = _arr_info.Make(n);
            if (!caller(a, test_number))
                return false;
            test_number++;
        }
        // All Max
        test_number = 300000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a = _arr_info.Make(n, _arr_info.Max()-n, _arr_info.Max());
            if (!caller(a, test_number))
                return false;
            test_number++;
        }

        // All Min
        test_number = 400000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a = _arr_info.Make(n, _arr_info.Min(), _arr_info.Min() + n);
            if (!caller(a, test_number))
                return false;
            test_number++;
        }
        LOG("All Tests Passed :-)");
#endif
        return true;
    }
private:
    bool caller(vector<A1> &a, size_t test_number) {
        if (_beforeRunningEachTest)
            _beforeRunningEachTest(a, _arr_info);

        RET ret_sln = _sln(a);
        RET ret_dummy = _dummy_sln(a);

        if (!this->IsEqual(ret_sln, ret_dummy)) {
            LOG("[x] Test(" << test_number << ") FAILED.");
            LOG("solution = (" << ret_sln << ") != (" << ret_dummy << ") dummy_solution");
            LOG("failed on:");
            log_array(a);
            return false;
        }
        else {
            LOG("[+] Test(" << test_number << ") Passed.");
        }
        return true;
    }

    ArrayInfo<A1>           _arr_info;
    Sln                     _dummy_sln;
    Sln                     _sln;
    BeforeRunningEachTest   _beforeRunningEachTest = NULL;
};


template<typename V1 = int, typename RET = int>
class Test_1v : public TestBase<RET> {
public:
    using Sln = function<RET(V1)>;
    using BeforeRunningEachTest = function<void(V1&, const VarInfo<V1>&)>;

    Test_1v(const Sln& dummy_sln, const Sln& sln, const VarInfo<V1>& var_info) : 
        _dummy_sln(dummy_sln),
        _sln(sln),
        _var_info(var_info)
    {}

    void SetBeforeRunningEachTestCallback(const BeforeRunningEachTest beforeRunningEachTest) {
        _beforeRunningEachTest = beforeRunningEachTest;
    }

    bool Test(V1 v1) {
        RET rdum = _dummy_sln(v1);
        LOG("Dummy test passed.");
        RET rsln = _sln(v1);
        if (rsln != rdum) {
            LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
            return false;
        }
        LOG("Manual test passed.");
        return true;
    }
    
    bool Test(V1 v1,  RET result) {
        RET rdum = _dummy_sln(v1);
        if (rdum != result) {
            LOG("Dummy test failed: Dummy: " << rdum << " != " << result << " :answer");
            return false;
        }
        else {
            LOG("Dummy test passed.");
            RET rsln = _sln(v1);
            if (rsln != rdum) {
                LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
                return false;
            }
            LOG("Manual test passed.");
            return true;
        }
    }

    bool AutoTest(size_t test_count, size_t minN, size_t maxN) {
#ifdef debug
        size_t test_number = 100000;
        const size_t test_groups = 3;
        // check low boundry
        for (size_t test = 0; test <= 5; test++) {
            V1 v1 = _var_info.Make();
            if (!caller(v1, test_number))
                return false;
            test_number++;
        }

        test_number = 200000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            V1 v1 = _var_info.Make();
            if (!caller(v1, test_number))
                return false;
            test_number++;
        }
        // All Max
        test_number = 300000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            V1 v1 = _var_info.Make(_var_info.Max() - n, _var_info.Max());
            if (!caller(v1, test_number))
                return false;
            test_number++;
        }

        // All Min
        test_number = 400000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            V1 v1 = _var_info.Make(_var_info.Min(), _var_info.Min() + n);
            if (!caller(v1, test_number))
                return false;
            test_number++;
        }
        LOG("All Tests Passed :-)");
#endif
        return true;
    }

private:
    bool caller(V1& v1, size_t test_number) {
        if (_beforeRunningEachTest)
            _beforeRunningEachTest(v1, _var_info);

        RET ret_sln = _sln(v1);
        RET ret_dummy = _dummy_sln(v1);
        if (!this->IsEqual(ret_sln, ret_dummy)) {
            LOG("[x] Test(" << test_number << ") FAILED.");
            LOG("solution = (" << ret_sln << ") != (" << ret_dummy << ") dummy_solution");
            LOG("failed on: " << v1);
            return false;
        }
        else {
            LOG("[+] Test(" << test_number << ") Passed.");
        }
        return true;
    }

    VarInfo<V1>             _var_info;
    Sln                     _dummy_sln;
    Sln                     _sln;
    BeforeRunningEachTest   _beforeRunningEachTest = nullptr;
};

template<typename V1 = int, typename V2 = int, typename RET = int>
class Test_2v : public TestBase<RET> {
public:
    using Sln = function<RET(V1, V2)>;
    using BeforeRunningEachTest = function<void(V1&, const VarInfo<V1>&, V2&, const VarInfo<V2>&)>;

    Test_2v(const Sln& dummy_sln, const Sln& sln, const VarInfo<V1>& var_info1, const VarInfo<V2>& var_info2) :
        _dummy_sln(dummy_sln),
        _sln(sln),
        _var_info1(var_info1),
        _var_info2(var_info2)
    {}

    void SetBeforeRunningEachTestCallback(const BeforeRunningEachTest beforeRunningEachTest) {
        _beforeRunningEachTest = beforeRunningEachTest;
    }

    bool Test(V1 v1, V2 v2) {
        RET rdum = _dummy_sln(v1, v2);

        RET rsln = _sln(v1, v2);
        if (rsln != rdum) {
            LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
            return false;
        }
        LOG("Manual test passed.");
        return true;
    }
    
    bool Test(V1 v1, V2 v2, RET result) {
        RET rdum = _dummy_sln(v1, v2);
        if (rdum != result) {
            LOG("Dummy test failed: Dummy: " << rdum << " != " << result << " :answer");
            return false;
        }
        else {
            LOG("Dummy test passed.");
            RET rsln = _sln(v1, v2);
            if (rsln != rdum) {
                LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
                return false;
            }
            LOG("Manual test passed.");
            return true;
        }
    }

    bool AutoTest(size_t test_count, size_t minN, size_t maxN) {
#ifdef debug
        size_t test_number = 100000;
        const size_t test_groups = 3;
        // check low boundry
        for (size_t test = 0; test <= 5; test++) {
            V1 v1 = _var_info1.Make();
            V2 v2 = _var_info2.Make();
            if (!caller(v1, v2, test_number))
                return false;
            test_number++;
        }

        test_number = 200000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            V1 v1 = _var_info1.Make();
            V2 v2 = _var_info2.Make();
            if (!caller(v1, v2, test_number))
                return false;
            test_number++;
        }
        // All Max
        test_number = 300000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            V1 v1 = _var_info1.Make(_var_info1.Max() - n, _var_info1.Max());
            V2 v2 = _var_info2.Make(_var_info2.Max() - n, _var_info2.Max());
            if (!caller(v1, v2, test_number))
                return false;
            test_number++;
        }

        // All Min
        test_number = 400000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            V1 v1 = _var_info1.Make(_var_info1.Min(), _var_info1.Min() + n);
            V2 v2 = _var_info2.Make(_var_info2.Min(), _var_info2.Min() + n);
            if (!caller(v1, v2, test_number))
                return false;
            test_number++;
        }
        LOG("All Tests Passed :-)");
#endif
        return true;
    }

private:
    bool caller(V1& v1, V2& v2, size_t test_number) {
        if (_beforeRunningEachTest)
            _beforeRunningEachTest(v1, _var_info1, v2, _var_info2);

        RET ret_sln = _sln(v1, v2);
        RET ret_dummy = _dummy_sln(v1, v2);
        if (!this->IsEqual(ret_sln, ret_dummy)) {
            LOG("[x] Test(" << test_number << ") FAILED.");
            LOG("solution = (" << ret_sln << ") != (" << ret_dummy << ") dummy_solution");
            LOG("failed on: " << v1);
            return false;
        }
        else {
            LOG("[+] Test(" << test_number << ") Passed.");
        }
        return true;
    }

    VarInfo<V1>             _var_info1;
    VarInfo<V2>             _var_info2;
    Sln                     _dummy_sln;
    Sln                     _sln;
    BeforeRunningEachTest   _beforeRunningEachTest = nullptr;
};

template<typename A1=int, typename V1=int, typename RET=int>
class Test_1a_1v : public TestBase<RET> {
public:
    using Sln = function<RET(vector<A1>&, V1&)> ;
    using BeforeRunningEachTest = function<void(vector<A1>&, const ArrayInfo<A1>&, V1&, const VarInfo<V1>&)> ;

    Test_1a_1v(const Sln& dummy_sln, const Sln& sln, const ArrayInfo<A1>& arr_info, const VarInfo<V1>& var_info) :
        _dummy_sln(dummy_sln),
        _sln(sln),
        _arr_info(arr_info),
        _var_info(var_info)
        {}

    void SetBeforeRunningEachTestCallback(const BeforeRunningEachTest beforeRunningEachTest) {
        _beforeRunningEachTest = beforeRunningEachTest;
    }

    bool Test(vector<A1> a1, V1 v1) {
        RET rdum = _dummy_sln(a1, v1);
        LOG("Dummy test passed.");
        RET rsln = _sln(a1, v1);
        if (rsln != rdum) {
            LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
            log_array(a1);
            return false;
        }
        LOG("Manual test passed.");
        return true;
    }

    bool Test(vector<A1> a1, V1 v1, RET result) {
        RET rdum = _dummy_sln(a1, v1);
        if (rdum != result) {
            LOG("Dummy test failed: Dummy: " << rdum << " != " << result << " :answer");
            log_array(a1);
            return false;
        }
        else {
            LOG("Dummy test passed.");
            RET rsln = _sln(a1, v1);
            if (rsln != rdum) {
                LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
                log_array(a1);
                return false;
            }
            LOG("Manual test passed.");
            return true;
        }
    }

    bool AutoTest(size_t test_count, size_t minN, size_t maxN) {
#ifdef debug
        size_t test_number = 100000;
        const size_t test_groups = 3;
        // check low boundry
        for (size_t test = 0; test <= 5; test++) {
            vector<A1> a = _arr_info.Make(minN + test);
            V1 v1 = _var_info.Make();
            if (!caller(a, v1, test_number))
                return false;
            test_number++;
        }

        test_number = 200000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a = _arr_info.Make(n);
            V1 v1 = _var_info.Make();
            if (!caller(a, v1, test_number))
                return false;
            test_number++;
        }
        // All Max
        test_number = 300000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a = _arr_info.Make(n, _arr_info.Max() - n, _arr_info.Max());
            V1 v1 = _var_info.Make(_var_info.Max() - n, _var_info.Max());
            if (!caller(a, v1, test_number))
                return false;
            test_number++;
        }

        // All Min
        test_number = 400000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a = _arr_info.Make(n, _arr_info.Min(), _arr_info.Min() + n);
            V1 v1 = _var_info.Make(_var_info.Min(), _var_info.Min() + n);
            if (!caller(a, v1, test_number))
                return false;
            test_number++;
        }
        LOG("All Tests Passed :-)");
#endif
        return true;
    }

private:
    bool caller(vector<A1>& a, V1& v1, size_t test_number) {
        if (_beforeRunningEachTest)
            _beforeRunningEachTest(a, _arr_info, v1, _var_info);

        RET ret_sln = _sln(a, v1);
        RET ret_dummy = _dummy_sln(a, v1);
        if ( !this->IsEqual(ret_sln, ret_dummy)) {
            LOG("[x] Test(" << test_number << ") FAILED.");
            LOG("solution = (" << ret_sln << ") != (" << ret_dummy << ") dummy_solution");
            LOG("failed on: variable=" << v1 << " and the array:");
            log_array(a);
            return false;
        }
        else {
            LOG("[+] Test(" << test_number << ") Passed.");
        }
        return true;
    }

    ArrayInfo<A1>           _arr_info;
    VarInfo<V1>             _var_info;
    Sln                     _dummy_sln;
    Sln                     _sln;
    BeforeRunningEachTest   _beforeRunningEachTest = nullptr;
};

template<typename A1 = int, typename V1 = int, typename V2 = int, typename RET = int>
class Test_1a_2v : public TestBase<RET> {
public:
    using Sln = function<RET(vector<A1>&, V1&, V2&)>;
    using BeforeRunningEachTest = function<void(vector<A1>&, const ArrayInfo<A1>&, V1&, const VarInfo<V1>&, V2&, const VarInfo<V2>&)>;

    Test_1a_2v(const Sln& dummy_sln, const Sln& sln, const ArrayInfo<A1>& arr_info, const VarInfo<V1>& var_info1, const VarInfo<V2>& var_info2) :
        _dummy_sln(dummy_sln),
        _sln(sln),
        _arr_info(arr_info),
        _var_info1(var_info1),
        _var_info2(var_info2)
    {}

    void SetBeforeRunningEachTestCallback(const BeforeRunningEachTest beforeRunningEachTest) {
        _beforeRunningEachTest = beforeRunningEachTest;
    }

    bool Test(vector<A1> a1, V1 v1, V2 v2) {
        RET rdum = _dummy_sln(a1, v1, v2);
        LOG("Dummy test passed.");
        RET rsln = _sln(a1, v1, v2);
        if (rsln != rdum) {
            LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
            log_array(a1);
            return false;
        }
        LOG("Manual test passed.");
        return true;

    }

    bool Test(vector<A1> a1, V1 v1, V2 v2, RET result) {
        RET rdum = _dummy_sln(a1, v1, v2);
        if (rdum != result) {
            LOG("Dummy test failed: Dummy: " << rdum << " != " << result << " :answer");
            log_array(a1);
            return false;
        }
        else {
            LOG("Dummy test passed.");
            RET rsln = _sln(a1, v1, v2);
            if (rsln != rdum) {
                LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
                log_array(a1);
                return false;
            }
            LOG("Manual test passed.");
            return true;
        }
    }

    bool AutoTest(size_t test_count, size_t minN, size_t maxN) {
#ifdef debug
        size_t test_number = 100000;
        const size_t test_groups = 3;
        // check low boundry
        for (size_t test = 0; test <= 5; test++) {
            vector<A1> a = _arr_info.Make(minN + test);
            V1 v1 = _var_info1.Make();
            V2 v2 = _var_info2.Make();
            if (!caller(a, v1, v2, test_number))
                return false;
            test_number++;
        }

        test_number = 200000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a = _arr_info.Make(n);
            V1 v1 = _var_info1.Make();
            V2 v2 = _var_info2.Make();
            if (!caller(a, v1, v2, test_number))
                return false;
            test_number++;
        }
        // All Max
        test_number = 300000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a = _arr_info.Make(n, _arr_info.Max() - n, _arr_info.Max());
            V1 v1 = _var_info1.Make(_var_info1.Max() - n, _var_info1.Max());
            V2 v2 = _var_info2.Make(_var_info2.Max() - n, _var_info2.Max());
            if (!caller(a, v1, v2, test_number))
                return false;
            test_number++;
        }

        // All Min
        test_number = 400000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a = _arr_info.Make(n, _arr_info.Min(), _arr_info.Min() + n);
            V1 v1 = _var_info1.Make(_var_info1.Min(), _var_info1.Min() + n);
            V2 v2 = _var_info2.Make(_var_info2.Min(), _var_info2.Min() + n);
            if (!caller(a, v1, v2, test_number))
                return false;
            test_number++;
        }
        LOG("All Tests Passed :-)");
#endif
        return true;
    }

private:
    bool caller(vector<A1>& a, V1& v1, V2& v2, size_t test_number) {
        if (_beforeRunningEachTest)
            _beforeRunningEachTest(a, _arr_info, v1, _var_info1, v2, _var_info2);

        RET ret_sln = _sln(a, v1, v2);
        RET ret_dummy = _dummy_sln(a, v1, v2);
        if (!this->IsEqual(ret_sln, ret_dummy)) {
            LOG("[x] Test(" << test_number << ") FAILED.");
            LOG("solution = (" << ret_sln << ") != (" << ret_dummy << ") dummy_solution");
            LOG("failed on: variable=" << v1 << ", " << v2 << ", and the array:");
            log_array(a);
            return false;
        }
        else {
            LOG("[+] Test(" << test_number << ") Passed.");
        }
        return true;
    }

    ArrayInfo<A1>           _arr_info;
    VarInfo<V1>             _var_info1;
    VarInfo<V2>             _var_info2;
    Sln                     _dummy_sln;
    Sln                     _sln;
    BeforeRunningEachTest   _beforeRunningEachTest = nullptr;
};

template<typename A1 = int, typename A2 = int, typename RET = int>
class Test_2a : public TestBase<RET> {
public:
    using Sln = function<RET(vector<A1>&, vector<A2>&)>;
    using BeforeRunningEachTest = function<void(vector<A1>&, const ArrayInfo<A1>&, vector<A2>&, const ArrayInfo<A2>&)>;

    Test_2a(const Sln& dummy_sln, const Sln& sln, const ArrayInfo<A1>& arr_info1, const ArrayInfo<A2>& arr_info2) :
        _dummy_sln(dummy_sln),
        _sln(sln),
        _arr_info1(arr_info1),
        _arr_info2(arr_info2)
    {}

    void SetBeforeRunningEachTestCallback(const BeforeRunningEachTest beforeRunningEachTest) {
        _beforeRunningEachTest = beforeRunningEachTest;
    }

    bool Test(vector<A1> a1, vector<A2> a2) {
        RET rdum = _dummy_sln(a1, a2);
        LOG("Dummy test passed.");
        RET rsln = _sln(a1, a2);
        if (rsln != rdum) {
            LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
            log_array(a1);
            log_array(a2);
            return false;
        }
        LOG("Manual test passed.");
        return true;
    }

    bool Test(vector<A1> a1, vector<A2> a2, const RET result) {
        RET rdum = _dummy_sln(a1, a2);
        if (rdum != result) {
            LOG("Dummy test failed: Dummy: " << rdum << " != " << result << " :answer");
            log_array(a1);
            log_array(a2);
            return false;
        }
        else {
            LOG("Dummy test passed.");
            RET rsln = _sln(a1, a2);
            if (rsln != rdum) {
                LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
                log_array(a1);
                log_array(a2);
                return false;
            }
            LOG("Manual test passed.");
            return true;
        }
    }

    bool AutoTest(size_t test_count, size_t minN, size_t maxN) {
#ifdef debug
        size_t test_number = 100000;
        const size_t test_groups = 3;
        // check low boundry
        for (size_t test = 0; test <= 5; test++) {
            vector<A1> a1 = _arr_info1.Make(minN + test);
            vector<A2> a2 = _arr_info2.Make(minN + test);
            if (!caller(a1, a2, test_number))
                return false;
            test_number++;
        }

        test_number = 200000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a1 = _arr_info1.Make(n);
            vector<A2> a2 = _arr_info2.Make(n);
            if (!caller(a1, a2, test_number))
                return false;
            test_number++;
        }
        // All Max
        test_number = 300000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a1 = _arr_info1.Make(n, _arr_info1.Max() - n, _arr_info1.Max());
            vector<A2> a2 = _arr_info2.Make(n, _arr_info2.Max() - n, _arr_info2.Max());
            if (!caller(a1, a2, test_number))
                return false;
            test_number++;
        }

        // All Min
        test_number = 400000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a1 = _arr_info1.Make(n, _arr_info1.Min(), _arr_info1.Min() + n);
            vector<A2> a2 = _arr_info2.Make(n, _arr_info2.Min(), _arr_info2.Min() + n);
            if (!caller(a1, a2, test_number))
                return false;
            test_number++;
        }
        LOG("All Tests Passed :-)");
#endif
        return true;
    }

private:
    bool caller(vector<A1>& a1, vector<A2>& a2, size_t test_number) {
        if (_beforeRunningEachTest)
            _beforeRunningEachTest(a1, _arr_info1, a2, _arr_info2);

        RET ret_sln = _sln(a1, a2);
        RET ret_dummy = _dummy_sln(a1, a2);
        if (!this->IsEqual(ret_sln, ret_dummy)) {
            LOG("[x] Test(" << test_number << ") FAILED.");
            LOG("solution = (" << ret_sln << ") != (" << ret_dummy << ") dummy_solution");
            log_array(a1);
            log_array(a2);
            return false;
        }
        else {
            LOG("[+] Test(" << test_number << ") Passed.");
        }
        return true;
    }

    ArrayInfo<A1>           _arr_info1;
    ArrayInfo<A2>           _arr_info2;
    Sln                     _dummy_sln;
    Sln                     _sln;
    BeforeRunningEachTest   _beforeRunningEachTest = nullptr;
};

template<typename A1=int, typename A2 = int, typename V1 = int, typename RET = int>
class Test_2a_1v : public TestBase<RET> {
public:
    using Sln = function<RET(vector<A1>&, vector<A2>&, V1&)>;
    using BeforeRunningEachTest = function<void(vector<A1>&, const ArrayInfo<A1>&, vector<A2>&, const ArrayInfo<A2>&, V1&, const VarInfo<V1>&)>;

    Test_2a_1v(const Sln& dummy_sln, const Sln& sln, const ArrayInfo<A1>& arr_info1, const ArrayInfo<A2>& arr_info2, const VarInfo<V1>& var_info) :
        _dummy_sln(dummy_sln),
        _sln(sln),
        _arr_info1(arr_info1),
        _arr_info2(arr_info2),
        _var_info(var_info)
    {}

    void SetBeforeRunningEachTestCallback(const BeforeRunningEachTest beforeRunningEachTest) {
        _beforeRunningEachTest = beforeRunningEachTest;
    }

    bool Test(vector<A1> a1, vector<A2> a2, V1 v1) {
        RET rdum = _dummy_sln(a1, a2, v1);
        LOG("Dummy test passed.");
        RET rsln = _sln(a1, a2, v1);
        if (rsln != rdum) {
            LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
            log_array(a1);
            log_array(a2);
            return false;
        }
        LOG("Manual test passed.");
        return true;
    }
    

    bool Test(vector<A1> a1, vector<A2> a2, V1 v1, RET result) {
        RET rdum = _dummy_sln(a1, a2, v1);
        if (rdum != result) {
            LOG("Dummy test failed: Dummy: " << rdum << " != " << result << " :answer");
            log_array(a1);
            log_array(a2);
            return false;
        }
        else {
            LOG("Dummy test passed.");
            RET rsln = _sln(a1, a2, v1);
            if (rsln != rdum) {
                LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
                log_array(a1);
                log_array(a2);
                return false;
            }
            LOG("Manual test passed.");
            return true;
        }
    }

    bool AutoTest(size_t test_count, size_t minN, size_t maxN) {
#ifdef debug
        size_t test_number = 100000;
        const size_t test_groups = 3;
        // check low boundry
        for (size_t test = 0; test <= 5; test++) {
            vector<A1> a1 = _arr_info1.Make(minN + test);
            vector<A2> a2 = _arr_info2.Make(minN + test);
            V1 v1 = _var_info.Make();
            if (!caller(a1, a2, v1, test_number))
                return false;
            test_number++;
        }

        test_number = 200000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a1 = _arr_info1.Make(n);
            vector<A2> a2 = _arr_info2.Make(n);
            V1 v1 = _var_info.Make();
            if (!caller(a1, a2, v1, test_number))
                return false;
            test_number++;
        }
        // All Max
        test_number = 300000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a1 = _arr_info1.Make(n, _arr_info1.Max() - n, _arr_info1.Max());
            vector<A2> a2 = _arr_info2.Make(n, _arr_info2.Max() - n, _arr_info2.Max());
            V1 v1 = _var_info.Make(_var_info.Max() - n, _var_info.Max());
            if (!caller(a1, a2, v1, test_number))
                return false;
            test_number++;
        }

        // All Min
        test_number = 400000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a1 = _arr_info1.Make(n, _arr_info1.Min(), _arr_info1.Min() + n);
            vector<A2> a2 = _arr_info2.Make(n, _arr_info2.Min(), _arr_info2.Min() + n);
            V1 v1 = _var_info.Make(_var_info.Min(), _var_info.Min() + n);
            if (!caller(a1, a2, v1, test_number))
                return false;
            test_number++;
        }
        LOG("All Tests Passed :-)");
#endif
        return true;
    }

private:
    bool caller(vector<A1>& a1, vector<A2>& a2, V1& v1, size_t test_number) {
        if (_beforeRunningEachTest)
            _beforeRunningEachTest(a1, _arr_info1, a2, _arr_info2, v1, _var_info);

        RET ret_sln = _sln(a1, a2, v1);
        RET ret_dummy = _dummy_sln(a1, a2, v1);
        if (!this->IsEqual(ret_sln, ret_dummy)) {
            LOG("[x] Test(" << test_number << ") FAILED.");
            LOG("solution = (" << ret_sln << ") != (" << ret_dummy << ") dummy_solution");
            LOG("failed on: variable=" << v1 << " and the array:");
            log_array(a1);
            log_array(a2);
            return false;
        }
        else {
            LOG("[+] Test(" << test_number << ") Passed.");
        }
        return true;
    }

    ArrayInfo<A1>           _arr_info1;
    ArrayInfo<A2>           _arr_info2;
    VarInfo<V1>             _var_info;
    Sln                     _dummy_sln;
    Sln                     _sln;
    BeforeRunningEachTest   _beforeRunningEachTest = nullptr;
};

template<typename A1 = int, typename A2 = int, typename A3 = int, typename RET = int>
class Test_3a : public TestBase<RET> {
public:
    using Sln = function<RET(vector<A1>&, vector<A2>&, vector<A3>&)>;
    using BeforeRunningEachTest = function<void(vector<A1>&, const ArrayInfo<A1>&, vector<A2>&, const ArrayInfo<A2>&, vector<A3>&, const ArrayInfo<A3>&)>;

    Test_3a(const Sln& dummy_sln, const Sln& sln, const ArrayInfo<A1>& arr_info1, const ArrayInfo<A2>& arr_info2, const ArrayInfo<A3>& arr_info3) :
        _dummy_sln(dummy_sln),
        _sln(sln),
        _arr_info1(arr_info1),
        _arr_info2(arr_info2),
        _arr_info3(arr_info3)
    {}

    void SetBeforeRunningEachTestCallback(const BeforeRunningEachTest beforeRunningEachTest) {
        _beforeRunningEachTest = beforeRunningEachTest;
    }

    bool Test(vector<A1> a1, vector<A2> a2, vector<A3> a3) {
        RET rdum = _dummy_sln(a1, a2, a3);
        LOG("Dummy test passed.");
        RET rsln = _sln(a1, a2, a3);
        if (rsln != rdum) {
            LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
            log_array(a1);
            log_array(a2);
            log_array(a3);
            return false;
        }
        LOG("Manual test passed.");
        return true;
    }

    bool Test(vector<A1> a1, vector<A2> a2, vector<A3> a3, const RET result) {
        RET rdum = _dummy_sln(a1, a2, a3);
        if (rdum != result) {
            LOG("Dummy test failed: Dummy: " << rdum << " != " << result << " :answer");
            log_array(a1);
            log_array(a2);
            log_array(a3);
            return false;
        }
        else {
            LOG("Dummy test passed.");
            RET rsln = _sln(a1, a2, a3);
            if (rsln != rdum) {
                LOG("Manual test failed: Dummy: " << rdum << " != " << rsln << " :solution");
                log_array(a1);
                log_array(a2);
                log_array(a3);
                return false;
            }
            LOG("Manual test passed.");
            return true;
        }
    }

    bool AutoTest(size_t test_count, size_t minN, size_t maxN) {
#ifdef debug
        size_t test_number = 100000;
        const size_t test_groups = 3;
        // check low boundry
        for (size_t test = 0; test <= 5; test++) {
            vector<A1> a1 = _arr_info1.Make(minN + test);
            vector<A2> a2 = _arr_info2.Make(minN + test);
            vector<A3> a3 = _arr_info3.Make(minN + test);
            if (!caller(a1, a2, a3, test_number))
                return false;
            test_number++;
        }

        test_number = 200000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a1 = _arr_info1.Make(n);
            vector<A2> a2 = _arr_info2.Make(n);
            vector<A3> a3 = _arr_info3.Make(minN + test);
            if (!caller(a1, a2, a3, test_number))
                return false;
            test_number++;
        }
        // All Max
        test_number = 300000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a1 = _arr_info1.Make(n, _arr_info1.Max() - n, _arr_info1.Max());
            vector<A2> a2 = _arr_info2.Make(n, _arr_info2.Max() - n, _arr_info2.Max());
            vector<A3> a3 = _arr_info3.Make(n, _arr_info3.Max() - n, _arr_info3.Max());
            if (!caller(a1, a2, a3, test_number))
                return false;
            test_number++;
        }

        // All Min
        test_number = 400000;
        for (size_t test = 1; test <= test_count / test_groups; test++) {
            size_t n = rand() % maxN + minN;
            vector<A1> a1 = _arr_info1.Make(n, _arr_info1.Min(), _arr_info1.Min() + n);
            vector<A2> a2 = _arr_info2.Make(n, _arr_info2.Min(), _arr_info2.Min() + n);
            vector<A3> a3 = _arr_info3.Make(n, _arr_info3.Min(), _arr_info3.Min() + n);
            if (!caller(a1, a2, a3, test_number))
                return false;
            test_number++;
        }
        LOG("All Tests Passed :-)");
#endif
        return true;
    }

private:
    bool caller(vector<A1>& a1, vector<A2>& a2, vector<A3>& a3, size_t test_number) {
        if (_beforeRunningEachTest)
            _beforeRunningEachTest(a1, _arr_info1, a2, _arr_info2, a3, _arr_info3);

        RET ret_sln = _sln(a1, a2, a3);
        RET ret_dummy = _dummy_sln(a1, a2, a3);
        if (!this->IsEqual(ret_sln, ret_dummy)) {
            LOG("[x] Test(" << test_number << ") FAILED.");
            LOG("solution = (" << ret_sln << ") != (" << ret_dummy << ") dummy_solution");
            log_array(a1);
            log_array(a2);
            log_array(a3);
            return false;
        }
        else {
            LOG("[+] Test(" << test_number << ") Passed.");
        }
        return true;
    }

    ArrayInfo<A1>           _arr_info1;
    ArrayInfo<A2>           _arr_info2;
    ArrayInfo<A3>           _arr_info3;
    Sln                     _dummy_sln;
    Sln                     _sln;
    BeforeRunningEachTest   _beforeRunningEachTest = nullptr;
};