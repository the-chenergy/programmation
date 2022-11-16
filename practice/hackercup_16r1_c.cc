// #define SYNC_IO 01 // Synchronize cin and cout
// #define TRACE_COUT 01 // Use cout for trace and redirect cerr to cout
// #define NO_MAIN 01 // Do not declare the main function
#define LOCAL 0 // If 0 or not set, "comment" all cerr and trace

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

#define len(x) int(size(x))

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

// https://www.facebook.com/codingcompetitions/hacker-cup/2016/round-1/problems/C
void solve(int /* case_id */) {
    int n;
    double a,b;
    cin>>n>>a>>b;
    vector<double>c(n),pre{0};
    double tot=0;
    for(auto&x:c)cin>>x,tot+=x,pre.push_back(pre.back()+x);
    trace(tot);
    double lo=0,spent=0,tar=fmod(fmod(tot-a,tot)+tot,tot);
    if(tar>1E-9)
        for(int i=n-1;i>=0;i--){
            if(spent+c[i]>tar){
                lo+=(tar-spent)/tar*.5*(c[i]+tot-tar-pre[i]);
                break;
            }
            lo+=c[i]/tar*.5*c[i];
            spent+=c[i];
        }
    trace(tar,lo);
    double mid=0;
    for(int i=0;i<n;i++){
        mid+=c[i]/tot*.5*c[i];
    }
    trace(mid);
    double hi=0,hi_tar=fmod(b,tot);
    spent=0;
    if(hi_tar>1E-9)
        for(int i=0;i<n;i++){
            if(spent+c[i]>hi_tar){
                hi+=(hi_tar-spent)/hi_tar*.5*(hi_tar-spent);
                break;
            }
            hi+=c[i]/hi_tar*.5*c[i];
            spent+=c[i];
        }
    trace(hi_tar,hi);
    cout<<setprecision(12)<<(lo*tar+mid*(b-a-tar-hi_tar)+hi*hi_tar)/(b-a);
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
