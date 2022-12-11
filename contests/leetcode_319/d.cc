#define SYNC_IO 01 // Synchronize cin and cout
#define TRACE_COUT 01 // Use cout for trace and redirect cerr to cout
#define NO_MAIN 01 // Do not declare the main function
#define LOCAL 01 // If 0 or not set, "comment" all cerr and trace

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

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
#endif
}

namespace std {
template <typename T, size_t size>
static ostream& operator<<(ostream& out, const array<T, size>& x);

template <typename TFirst, typename TSecond>
static ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x);

template <typename... T>
static ostream& operator<<(ostream& out, const tuple<T...> x);

template <typename TContainer, typename T = typename enable_if<
                                   !is_same<TContainer, string>::value,
                                   typename TContainer::value_type>::type>
static ostream& operator<<(ostream& out, const TContainer& x) {
    out << "{";
    string delim;
    for (const T& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <typename T, size_t size>
static ostream& operator<<(ostream& out, const std::array<T, size>& x) {
    out << "{";
    string delim;
    for (const T& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <typename TFirst, typename TSecond>
static ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x) {
    return out << "{" << x.first << ", " << x.second << "}";
}

template <typename... T>
static ostream& operator<<(ostream& out, const tuple<T...> x) {
    out << "{";
    string delim;
    apply([&](auto&... y) { (..., (out << delim << y, delim = ", ")); }, x);
    return out << "}";
}
}  // namespace std

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

#if !NO_MAIN
void solve_suite();
int main() { solve_suite(); }
#endif

#pragma endregion }

class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n=int(s.size());
        //{b,c}->is pal
        auto pal=vector(n+1,vector(n+1,0));
        for(int b=0;b<=n;b++)pal[b][0]=1;
        for(int b=0;b<n;b++)pal[b][1]=1;
        //pal(b,c)=pal(b+1,c-2)*(s[b]==s[b+c-1])
        function<void()>tpal=[&](){};
        #if LOCAL
        tpal=[&](){
            for(int b=0;b<=n;b++)for(int c=0;b+c<=n;c++)trace(b,c,pal[b][c]);
        };
        #endif
        for(int c=2;c<=n;c++){
            for(int b=n-c;b>=0;b--){
                pal[b][c]=s[b]==s[b+c-1]&&pal[b+1][c-2];
            }
        }
        // tpal();
        set<array<int,2>>rs;
        for(int b=0;b<n;b++){
            for(int c=k;b+c<=n;c++){
                if(pal[b][c]){
                    if(c-2<k||(b+c>n||!pal[b+1][c-2]))
                        rs.insert({b+c,b});
                }
            }
        }
        // trace(rs);
        int ans=0,cur_e=0;
        for(auto[e,b]:rs){
            if(b>=cur_e)ans++,cur_e=e;
        }
        return ans;
    }
};
