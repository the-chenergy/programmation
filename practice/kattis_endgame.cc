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
    cout.tie(nullptr);
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

static mt19937 mt_rng(
    unsigned(chrono::steady_clock::now().time_since_epoch().count()));

template <typename T>
static T randint(T a, T b) {
    return uniform_int_distribution<T>(a, b)(mt_rng);
}

using point = complex<int>;

#define X real()
#define Y imag()

namespace std {
template <typename T>
static bool operator<(const complex<T>& a, const complex<T>& b) {
    return a.X != b.X ? a.X < b.X : a.Y < b.Y;
}
}  // namespace std

int n;
point a, b;
vector<point> dirs;

point read_pt() {
    int x, y;
    cin >> x >> y;
    return point(x, y);
}

bool capture(point src, point tar) {
    set<point> vis;
    for (auto d : dirs) {
        point nxt = src + d;
        if (nxt.X < 1 || nxt.X > n || nxt.Y < 1 || nxt.Y > n) continue;
        if (nxt == tar) return true;
        vis.insert(nxt);
    }
    for (auto d : dirs) {
        point nxt = tar - d;
        if (nxt.X < 1 || nxt.X > n || nxt.Y < 1 || nxt.Y > n) continue;
        if (vis.count(nxt)) return true;
    }
    return false;
}

void get_tries(set<point>& out) {
    if (n <= 420) {
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++) {
                point p(x, y);
                if (p == b) continue;
                out.insert(p);
            }
        }
    } else {
        while (int(out.size()) < 420) {
            point p(randint(1, n), randint(1, n));
            if (p == b) continue;
            out.insert(p);
        }
    }
}

#define report(x) return void(cout << x << "\n")

void solve(int /* case_id */) {
    cin >> n;
    a = read_pt(), b = read_pt();
    dirs.clear();
    for (int i = 0; i < n; i++) dirs.push_back(read_pt());

    if (capture(a, b)) report("Alice wins");
    set<point> tries;
    get_tries(tries);
    for (point p : tries) {
        if (!capture(b, p)) report("tie " << p.X << " " << p.Y);
    }
    report("Bob wins");
}

void solve_suite() {
    int num_cases = 1;
    // cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        // cout << "Case #" << case_id << ": ";
        solve(case_id);
        // cout << "\n";
    }
}
