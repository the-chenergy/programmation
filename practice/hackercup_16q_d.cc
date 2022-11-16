// #define SYNC_IO 01 // Synchronize cin and cout
// #define TRACE_COUT 01 // Use cout for trace and redirect cerr to cout
// #define NO_MAIN 01 // Do not declare the main function
// #define LOCAL 0 // If 0 or not set, "comment" all cerr and trace

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

template <typename T>
static int len(T x) {
    return int(size(x));
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
#define trace(...) void(0)
#endif

#if !NO_MAIN
void solve_suite();
int main() { solve_suite(); }
#endif

#pragma endregion }

// https://www.facebook.com/codingcompetitions/hacker-cup/2016/qualification-round/problems/D
void solve(int /* case_id */) { 
    int n,k;cin>>n>>k;
    vector<string>dict(n);
    for(int i=0;i<n;i++)cin>>dict[i];
    sort(dict.begin(),dict.end());
    auto dist=vector(n,vector(n,int(1E9)));
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            int com=0;
            while(com<len(dict[i])&&com<len(dict[j])&&
                dict[i][com]==dict[j][com])com++;
            dist[i][j]=dist[j][i]=len(dict[i])-com+len(dict[j])-com;
        }
    }
    auto dp=vector(k+1,vector(n+1,int(1E9)));
    for(int i=0;i<=n;i++){
        dp[0][i]=0;
        if(i<n)dp[1][i]=len(dict[i]);
    }
    for(int r=2;r<=k;r++){
        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<=n;j++){
                int d=j==n?0:dist[i][j];
                assert(d<1E9||(trace(r,i,j),0));
                dp[r][i]=min(dp[r][i],d+dp[r-1][j]);
            }
        }
    }
    int ans=1E9;
    for(int i=0;i<n;i++)ans=min(ans,len(dict[i])+dp[k][i]);
    cout<<ans+k;
}

void solve_suite() {
    int num_cases = 1;
    cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        cout << "Case #" << case_id << ": ";
        solve(case_id);
        cout << "\n";
    }
}
