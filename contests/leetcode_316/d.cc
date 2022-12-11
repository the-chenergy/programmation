/*
5    5  5
1    5  13
-2   0  4
*/
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
class Solution {
public:
    long long makeSimilar(vector<int>& nums, vector<int>& target) {
        vector<int>o1,e1,o2,e2;
        for(auto x:nums){
            if(x%2)o1.push_back(x);
            else e1.push_back(x);
        }for(auto x:target){
            if(x%2)o2.push_back(x);
            else e2.push_back(x);
        }
        sort(o1.begin(),o1.end());
        sort(o2.begin(),o2.end());
        sort(e1.begin(),e1.end());
        sort(e2.begin(),e2.end());
        ll neg=0,pos=0;
        for(int i=0;i<o1.size();i++){
            if(o1[i]==o2[i])continue;
            if(o1[i]<o2[i])pos+=(ll)(o2[i]-o1[i])/2;
            else neg+=(ll)(o1[i]-o2[i])/2;
        }
        for(int i=0;i<e1.size();i++){
            if(e1[i]==e2[i])continue;
            if(e1[i]<e2[i])pos+=(ll)(e2[i]-e1[i])/2;
            else neg+=(ll)(e1[i]-e2[i])/2;
        }
        return max(neg,pos);
    }
};
