#define SYNC_IO 1
#define TRACE_COUT 1
#define LOCAL 0

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
class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& cost) {
        using ll=long long;
        ll lo=*min_element(nums.begin(),nums.end());
        ll hi=*max_element(nums.begin(),nums.end())+1;
        auto cc=[&](ll x){
            ll ans=0;
            int i=0;
            for(auto y:nums)ans+=abs(y-x)*(ll)cost[i],i++;
            return ans;
        };
        ll a=0;
        while(lo<hi){
            ll m1=lo+(hi-lo)/3;
            ll m2=hi-(hi-lo+2)/3;
            trace(lo,hi,m1,m2);
            ll c1=cc(m1),c2=cc(m2);
            a=min(c1,c2);
            if(c1<c2)hi=m2;
            else lo=m1+1;
        }
        return a;
    }
};
