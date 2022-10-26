// #define SYNC_IO 01
// #define TRACE_COUT 01
// #define LOCAL 0

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
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
    cout.tie(nullptr);
#endif
}

template <class T, size_t size>
ostream& operator<<(ostream& out, const array<T, size>& x);

template <class TFirst, class TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x);

template <class... T>
ostream& operator<<(ostream& out, const tuple<T...> x);

template <class TContainer,
          class T = class enable_if<!is_same<TContainer, string>::value,
                                    class TContainer::value_type>::type>
ostream& operator<<(ostream& out, const TContainer& x) {
    out << "{";
    string delim;
    for (const T& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <class T, size_t size>
ostream& operator<<(ostream& out, const array<T, size>& x) {
    out << "{";
    string delim;
    for (const T& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <class TFirst, class TSecond>
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

template <class TArg1>
static void _trace(const char* labels, const TArg1& arg1) {
    if (labels[0] != '"') cerr << labels + (labels[0] == ' ') << ": ";
    cerr << arg1 << "\n";
}

template <class TArg1, class... TArgs>
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

auto dirs = vector<array<int, 2>>{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void solve(int /* case_id */) {
    int h, w;
    cin >> h >> w;
    auto graph = vector<string>(h);
    for (int y = 0; y < h; y++) cin >> graph[y];
    auto dist = vector(h, vector(w, (int)1E9));
    auto par = vector(h, vector(w, pair{0, 0}));
    auto locked = vector(h, vector(w, false));
    dist[0][0] = 0;
    locked[0][0] = true;
    auto search = set<array<int, 3>>{{0, 0, 0}};
    while (len(search)) {
        auto [cd, cy, cx] = *search.begin();
        search.erase(search.begin());
        trace("  visit", cd, cy, cx);
        if (cd > dist[cy][cx]) continue;
        if (graph[cy][cx] == 'T' && !locked[cy][cx]) {
            int py = cy, px = cx;
            while (!locked[py][px]) {
                locked[py][px] = true;
                tie(py, px) = par[py][px];
            }
            cd = 0;
        }
        for (auto [dy, dx] : dirs) {
            int y = cy + dy, x = cx + dx;
            if (y < 0 || y >= h || x < 0 || x >= w || graph[y][x] == '.')
                continue;
            int d = cd + 1;
            if (d > dist[y][x]) continue;
            if (!locked[y][x]) {
                dist[y][x] = d;
                par[y][x] = {cy, cx};
            }
            search.insert({d, y, x});
        }
    }
    ll ans = 0;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (graph[y][x] != '.') ans += dist[y][x];
    cout << ans << "\n";
}

int main() {
    int num_cases = 1;
    cin >> num_cases;
    for (int case_id = 0; case_id < num_cases; case_id++) {
        cout << "Case #" << case_id + 1 << ": ";
        solve(case_id);
    }
}
