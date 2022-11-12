// #define SYNC_IO 1
// #define TRACE_COUT 1
// #define LOCAL 0

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using ull = uint64_t;

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

void solve(int /* case_id */) {
  int n, k, q;
  cin >> n >> k >> q;
  auto xs = vector(n, 0), ct = vector(k, 0), ws = vector(2 * n - 1, 0);
  int b = -1, e = -1, w = 0, pb = 0;
  while (e < n) {
    if (k) {
      e++;
      if (e == n) break;
      int x;
      cin >> x;
      xs[e] = x;
      if (!ct[x]) k--;
      ct[x]++;
      if (b >= 0) w ^= 1, ws[b + e] = w;
      trace("ADV E", b, e, pb, ws);
    } else {
      b++;
      ws[b + e] = w;
      ct[xs[b]]--;
      if (!ct[xs[b]]) k++;
      xs[b] = e;
      if (k) {
        w = (pb - b) & 1;
        if (w) ws[pb + e] = w;
        while (pb < b) {
          pb++;
          w ^= 1, ws[pb + e] = w;
        }
      }
      trace("ADV B", b, e, pb, ws);
    }
  }
  while (b < n - 1) b++, xs[b] = n, trace("FIN B", b, e, pb, ws);
  while (q--) {
    int l, r;
    cin >> l >> r;
    l--, r--;
    cout << (xs[l] > r ? 0 : ws[l + r] ? 1 : 2) << "\n";
  }
}

int main() {
  int num_cases = 1;
  // cin >> num_cases;
  for (int case_id = 0; case_id < num_cases; case_id++) {
    // cout << "Case #" << case_id + 1 << ": ";
    solve(case_id);
  }
}
