// #define DEBUG 01

#pragma region programmation {
#pragma region common {  // clang-format off
#pragma GCC diagnostic ignored "-Wshadow"
#ifndef DEBUG
#    define DEBUG 0
#endif
#if DEBUG
#    define trace(...) (_trace(#__VA_ARGS__, __VA_ARGS__), 0)
#    define view(...) (cout << #__VA_ARGS__": ", _view(__VA_ARGS__), cout << "\n", 0)
#else
#    pragma clang attribute push (__attribute__((no_sanitize("address", "undefined"))), apply_to=function)
#    define trace(...) ((void)0, 0)
#    define view(...) ((void)0, 0)
#endif
#include <bits/stdc++.h>
#define rep(i, b, e) for (int i = b; i < (e); i++)
#define trav(x, a) for (auto& x : a)
#define all(x) begin(x), end(x)
#define sz len
#define comparing(s, ...) [&](auto& _l, auto& _r) { auto _f = [&](auto& _) { return __VA_ARGS__; }; return _f(_l) s _f(_r); }
using namespace std; using ll = long long; using ull = unsigned long long; using ld = long double; using vi = vector<int>; using pii = pair<int, int>; template <typename T> int len(const T& x) { return int(x.size()); } template <typename T, size_t l> int len(const T (&)[l]) { return l; } template <typename T, typename S> bool amax(T& t, S s) { return t < s && (t = s, 1); } template <typename T, typename S> bool amin(T& t, S s) { return s < t && (t = s, 1); } int case_id; namespace std { template <typename T, size_t l> ostream& operator<<(ostream& s, const array<T, l>& x); template <typename F, typename S> ostream& operator<<(ostream& s, const pair<F, S>& x); template <typename... T> ostream& operator<<(ostream& s, const tuple<T...>& x); template <typename C, typename T = enable_if_t<!is_same<C, string>::value, typename C::value_type>> ostream& operator<<(ostream& s, const C& x) { s << "{"; string d; for (auto&& y : x) s << d << y, d = ", "; return s << "}"; } template <typename T, size_t l, enable_if_t<!is_same<T, char>::value, int> = 0> ostream& operator<<(ostream& s, const T (&x)[l]) { s << "{"; string d; for (auto&& y : x) s << d << y, d = ", "; return s << "}"; } template <typename T, size_t l> ostream& operator<<(ostream& s, const std::array<T, l>& x) { s << "{"; string d; for (auto&& y : x) s << d << y, d = ", "; return s << "}"; } template <typename F, typename S> ostream& operator<<(ostream& s, const pair<F, S>& x) { return s << "{" << x.first << ", " << x.second << "}"; } template <typename... T> ostream& operator<<(ostream& s, const tuple<T...>& x) { s << "{"; string d; apply([&](auto&&... y) { (..., (s << d << y, d = ", ")); }, x); return s << "}"; } } template <typename T> void _trace(const char* l, const T& x) { if (l[0] != '"') cout << l + (l[0] == ' ') << ": "; cout << x << "\n"; } template <typename T, typename... A> void _trace(const char* l, const T& x, const A&... a) { if (l[0] == ' ') l++; size_t s = strchr(l, ',') - l; if (l[0] != '"') cout.write(l, s) << ": "; cout << x << ", ", _trace(l + s + 1, a...); } template <typename T> void _view(const T& x) { cout << x; } template <typename T, typename... R> void _view(const T& x, int b, int e, R... r) { b < 0 && (b += len(x)), e < 0 && (e += len(x)); b = min(max(b, 0), len(x)), e = min(max(e, b), len(x)); auto it = begin(x); advance(it, b); cout << "{"; for (int i = b; i < e; it++, i++) { if (i != b) cout << ", "; _view(*it, r...); } cout << "}"; } __attribute__((constructor)) static void _init() { if (!DEBUG) ios::sync_with_stdio(0), cin.tie(0); }
#pragma endregion common }  // clang-format on

// Additional library code

#pragma GCC diagnostic pop
#pragma endregion programmation }

class Solution {
  public:
    string smallestBeautifulString(string s, int k) {
        int n = (int)s.size();
        if (n == 1) {
            if (s[0] == 'a' + k - 1) return "";
            s[0]++;
            return s;
        }
        for (char c = s[n - 1] + 1; c < 'a' + k; c++) {
            if (c != s[n - 2] && (n == 2 || c != s[n - 3])) {
                s.back() = c;
                return s;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (char c = s[i] + 1; c < 'a' + k; c++) {
                for (char d = 'a'; d < 'd'; d++) {
                    if ((!i || c != s[i - 1]) && (i < 2 || c != s[i - 2]) &&
                        d != c && (!i || d != s[i - 1])) {
                        s[i] = c, s[i + 1] = d;
                        for (int j = i + 2; j < n; j++) {
                            for (char e = 'a'; e < 'd'; e++) {
                                if (e != s[j - 1] && e != s[j - 2]) {
                                    s[j] = e;
                                    break;
                                }
                            }
                        }
                        return s;
                    }
                }
            }
        }
        return "";
    }
};

#pragma region demo {
#if LOCAL && 01
Solution $s;
int main() {
    auto $t = [&](string s, int k) {
        cout << "Case #" << ++case_id << ": ";
        cout << $s.smallestBeautifulString(s, k);
        cout << "\n";
    };
    $t("abcz", 26);
    $t("dc", 4);
    $t("dfa", 6);
    $t("dca", 4);
    $t("edg", 7);
}
#elif !DEBUG
#    pragma clang attribute pop
#endif
#pragma endregion demo }
