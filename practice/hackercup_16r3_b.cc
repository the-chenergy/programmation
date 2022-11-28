#define SYNC_IO 01  // Synchronize cin and cout
// #define TRACE_COUT 01  // Use stdout for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
#define LOCAL 0  // If 0 or not set, "comment" all trace and eprintf

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int, int>;

#define rep(i, b, e) for (int i = b; i < (e); i++)
#define trav(x, a) for (auto& x : a)
#define all(x) begin(x), end(x)

template <typename T>
int len(const T& x) {
    return int(x.size());
}

template <typename T, size_t size>
int len(const T (&)[size]) {
    return size;
}

#define sz len

void _init() __attribute__((constructor));
void _init() {
#if !SYNC_IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
}

namespace std {
template <typename T, size_t size>
ostream& operator<<(ostream& out, const array<T, size>& x);

template <typename TFirst, typename TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond>& x);

template <typename... T>
ostream& operator<<(ostream& out, const tuple<T...>& x);

template <typename TContainer,
          typename T = enable_if_t<!is_same<TContainer, string>::value,
                                   typename TContainer::value_type>>
ostream& operator<<(ostream& out, const TContainer& x) {
    out << "{";
    string delim;
    for (auto& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <typename T, size_t size,
          enable_if_t<!is_same<T, char>::value, int> = 0>
ostream& operator<<(ostream& out, const T (&x)[size]) {
    out << "{";
    string delim;
    for (auto& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <typename T, size_t size>
ostream& operator<<(ostream& out, const std::array<T, size>& x) {
    out << "{";
    string delim;
    for (auto& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <typename TFirst, typename TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond>& x) {
    return out << "{" << x.first << ", " << x.second << "}";
}

template <typename... T>
ostream& operator<<(ostream& out, const tuple<T...>& x) {
    out << "{";
    string delim;
    apply([&](auto&... y) { (..., (out << delim << y, delim = ", ")); }, x);
    return out << "}";
}
}  // namespace std

#if TRACE_COUT
#    define _trace_out cout
#else
#    define _trace_out cerr
#endif

template <typename TArg1>
void _trace(const char* labels, const TArg1& arg1) {
    if (labels[0] != '"') _trace_out << labels + (labels[0] == ' ') << ": ";
    _trace_out << arg1 << "\n";
}

template <typename TArg1, typename... TArgs>
void _trace(const char* labels, const TArg1& arg1, const TArgs&... args) {
    if (labels[0] == ' ') labels++;
    size_t first_label_size = strchr(labels, ',') - labels;
    if (labels[0] != '"') _trace_out.write(labels, first_label_size) << ": ";
    _trace_out << arg1 << ", ";
    _trace(labels + first_label_size + 1, args...);
}

template <typename T>
void _view(const T& x) {
    _trace_out << x;
}

template <typename T, typename... TRange>
void _view(const T& x, int b, int e, TRange... ranges) {
    b = max(0, min(len(x), b)), e = max(b, min(len(x), e));
    string delim = "";
    auto it = begin(x);
    advance(it, b);
    auto& out = _trace_out;
    out << "{";
    for (; b < e; it++, b++) out << delim, _view(*it, ranges...), delim = ", ";
    out << "}";
}

#if LOCAL
#    if TRACE_COUT
#        define eprintf printf
#    else
#        define eprintf(...) fprintf(stderr, __VA_ARGS__)
#    endif
#    define trace(...) _trace(#__VA_ARGS__, __VA_ARGS__)
#    define view(...) _view(__VA_ARGS__), trace("")
#    define _local
#else
#    define eprintf(...) (void)0
#    define trace(...) (void)0
#    define view(...) (void)0
#    define _local while (false)
#endif

#if !NO_MAIN
void solve_suite();
int main() { solve_suite(); }
#endif

#pragma endregion }

const int c2r[]{0b00, 0b10, 0b11, 0b01};
int h, w, k, g[100][100], dp[1001][100][100][2], a0[1001];

void solve(int /* case_id */) {
    cin >> h >> w >> k;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            char c;
            cin >> c;
            g[y][x] = c2r[c - 'A'];
        }
    }
#define check(l)                                                     \
    _local if (y < h - 1 || x < w - 1) for (int p = 0; p < 2; p++) { \
        assert(dp[l][y][x][p] >= 0 && dp[l][y][x][p] <= h * w / 2);  \
    }
    for (int y = h - 1; y >= 0; y--) {
        for (int x = w - 1; x >= 0; x--) {
            dp[0][y][x][0] = 0;
            dp[0][y][x][1] = x > 0 && !(g[y][x] & 2);
            if (x < w - 1) {
                dp[0][y][x][0] += dp[0][y][x + 1][!!(g[y][x] & 2)];
                dp[0][y][x][1] += dp[0][y][x + 1][!!(g[y][x] & 2)];
            } else if (y < h - 1) {
                dp[0][y][x][0] += dp[0][y + 1][0][0];
                dp[0][y][x][1] += dp[0][y + 1][0][0];
            }
            check(0);
        }
    }
    for (int l = 1; l <= k; l++) {
        for (int y = h - 1; y >= 0; y--) {
            for (int x = w - 1; x >= 0; x--) {
                if (x < w - 1) {
                    dp[l][y][x][0] = min(dp[l - !!(g[y][x] & 2)][y][x + 1][0],
                                         dp[l - !(g[y][x] & 2)][y][x + 1][1]);
                    dp[l][y][x][1] =
                        min(1 + dp[l - !!(g[y][x] & 2)][y][x + 1][0],
                            dp[l - !(g[y][x] & 2)][y][x + 1][1]);
                } else if (y < h - 1) {
                    dp[l][y][x][0] = dp[l][y + 1][0][0];
                    dp[l][y][x][1] =
                        min(1 + dp[l - !!(g[y][x] & 2)][y + 1][0][0],
                            dp[l - !(g[y][x] & 2)][y + 1][0][0]);
                } else {
                    dp[l][y][x][0] = dp[l][y][x][1] = 0;
                }
                check(l);
            }
        }
    }
    for (int l = 0; l <= k; l++) a0[l] = dp[l][0][0][0];
    // view(a0, 0, k + 1);
    memset(dp, 0xC0, sizeof(dp));
    for (int x = w - 1; x >= 0; x--) {
        for (int y = h - 1; y >= 0; y--) {
            dp[0][y][x][0] = 0;
            dp[0][y][x][1] = y > 0 && !(g[y][x] & 1);
            if (y < h - 1) {
                dp[0][y][x][0] += dp[0][y + 1][x][!!(g[y][x] & 1)];
                dp[0][y][x][1] += dp[0][y + 1][x][!!(g[y][x] & 1)];
            } else if (x < w - 1) {
                dp[0][y][x][0] += dp[0][0][x + 1][0];
                dp[0][y][x][1] += dp[0][0][x + 1][0];
            }
            check(0);
        }
    }
    for (int l = 1; l <= k; l++) {
        for (int x = w - 1; x >= 0; x--) {
            for (int y = h - 1; y >= 0; y--) {
                if (y < h - 1) {
                    dp[l][y][x][0] = min(dp[l - !!(g[y][x] & 1)][y + 1][x][0],
                                         dp[l - !(g[y][x] & 1)][y + 1][x][1]);
                    dp[l][y][x][1] =
                        min(1 + dp[l - !!(g[y][x] & 1)][y + 1][x][0],
                            dp[l - !(g[y][x] & 1)][y + 1][x][1]);
                } else if (x < w - 1) {
                    dp[l][y][x][0] = dp[l][0][x + 1][0];
                    dp[l][y][x][1] =
                        min(1 + dp[l - !!(g[y][x] & 1)][0][x + 1][0],
                            dp[l - !(g[y][x] & 1)][0][x + 1][0]);
                } else {
                    dp[l][y][x][0] = dp[l][y][x][1] = 0;
                }
                check(l);
            }
        }
    }
    // view(dp, 0, k + 1, 0, 1, 0, 1, 0, 1);
    for (int l = 0; l <= k; l++) trace(l, dp[l][0][0][0], k - l, a0[k - l]);
    int ans = 1E9;
    for (int l = 0; l <= k; l++) ans = min(ans, dp[l][0][0][0] + a0[k - l]);
    cout << ans;
}

void solve_suite() {
    freopen("./sandbox/in.txt", "r", stdin);

    int num_cases = 1 << 0;
    cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        cout << "Case #" << case_id << ": ";
        solve(case_id);
        cout << "\n";

        // fprintf(stderr, "(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC);
    }
}
