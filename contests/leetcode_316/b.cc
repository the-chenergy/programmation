#define SYNC_IO 1
#define TRACE_COUT 1
#define LOCAL 01

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;

#define len(x) (int)(x).size()

#ifdef TRACE_COUT
#define cerr cout
#endif

#if !LOCAL
#define cerr \
    if (false) cerr
#define fprintf \
    if (false) fprintf
#if TRACE_COUT
#define cout \
    if (false) cout
#endif
#endif

static void _init() __attribute__((constructor));

static void _init() {
#if !SYNC_IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.exceptions(ios::failbit);
    cout.tie(nullptr);
#endif
}

template <typename TFirst, typename TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x);

template <class... T>
ostream& operator<<(ostream& out, const tuple<T...> x);

template <typename TContainer, typename T = typename enable_if<
                                   !is_same<TContainer, string>::value,
                                   typename TContainer::value_type>::type>
ostream& operator<<(ostream& out, const TContainer& x) {
    out << "{";
    string delim;
    for (const T& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <typename TFirst, typename TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x) {
    return out << "{" << x.first << ", " << x.second << "}";
}

template <class... T>
ostream& operator<<(ostream& out, const tuple<T...> x) {
    out << "{";
    string delim;
    apply([&](auto&... y) { (..., (out << delim << y, delim = ", ")); }, x);
    return out << "}";
}

template <typename TArg1>
static void _trace(const char* labels, const TArg1& arg1) {
    if (labels[0] != '"') cerr << labels + (labels[0] == ' ') << ": ";
    cerr << arg1 << "\n";
}

template <typename TArg1, typename... TArgs>
static void _trace(const char* labels, const TArg1& arg1,
                   const TArgs&... args) {
    if (labels[0] == ' ') labels++;
    size_t first_label_size = strchr(labels, ',') - labels;
    if (labels[0] != '"') cerr.write(labels, first_label_size) << ": ";
    cerr << arg1 << ", ";
    _trace(labels + first_label_size + 1, args...);
}

#if LOCAL
#define trace(...) _trace(#__VA_ARGS__, __VA_ARGS__)
#else
#define trace(...) (void)0
#endif

#pragma endregion }
struct segment_tree {
    using value_t = int;
    // using value_t = ll;
    const value_t DEFAULT_VALUE = 0;
    // const value_t DEFAULT_VALUE = INT_MAX;
    // const value_t DEFAULT_VALUE = INT_MIN;
    // const value_t DEFAULT_VALUE = ;
    value_t _get(value_t x, value_t y) {
        // return min(x, y);
        // return max(x, y);
        return gcd(x, y);
        return x + y;
    }
    int size;
    vector<value_t> _data;
    segment_tree(int size) : size(size), _data(2 * size, DEFAULT_VALUE) {}
    void update(int index, value_t new_value) {
        for (_data[index += size] = new_value; index /= 2;)
            _data[index] = _get(_data[index * 2], _data[index * 2 + 1]);
    }
    value_t query(int begin, int end) {
        value_t res_a = DEFAULT_VALUE, res_b = DEFAULT_VALUE;
        for (begin += size, end += size; begin < end; begin /= 2, end /= 2) {
            if (begin % 2) res_a = _get(res_a, _data[begin++]);
            if (end % 2) res_b = _get(_data[--end], res_b);
        }
        return _get(res_a, res_b);
    }
};
class Solution {
public:
    int subarrayGCD(vector<int>& nums, int k) {
        int n=nums.size();
        segment_tree st(n);
        for(int i=0;i<n;i++)st.update(i,nums[i]);
        int ans=0;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<=n;j++){
                if(st.query(i,j)==k)ans++;
            }
        }
        return ans;
    }
};
