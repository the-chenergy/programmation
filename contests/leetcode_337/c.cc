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
#    pragma clang attribute push (__attribute__((no_sanitize("address","undefined"))), apply_to=function)
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
    int beautifulSubsets(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        vector<int> l, r;
        for (int s = 0; s < 1 << n / 2; s++) {
            vector<int> a;
            int ok = 1;
            for (int i = 0; i < n / 2; i++) {
                if (s >> i & 1) {
                    for (int j : a) if (abs(j - nums[i]) == k) {
                        ok = 0;
                        break;
                    }
                    if (!ok) break;
                    a.push_back(nums[i]);
                }
            }
            if (!ok) continue;
            l.push_back(s);
        }
        for (int s = 0; s < 1 << n - n / 2; s++) {
            vector<int> a;
            int ok = 1;
            for (int i = 0; i < n - n / 2; i++) {
                if (s >> i & 1) {
                    for (int j : a) if (abs(j - nums[n / 2 + i]) == k) {
                        ok = 0;
                        break;
                    }
                    if (!ok) break;
                    a.push_back(nums[n / 2 + i]);
                }
            }
            if (!ok) continue;
            r.push_back(s);
        }
        trace(l, r);
        for (int s : l) {
            vector<int> a;
            for (int i = 0; i < n / 2; i++) if (s >> i & 1) a.push_back(nums[i]);
            for (int t : r) {
                trace(s, t, a);
                int ok = 1;
                for (int i = 0; i < n - n / 2; i++) {
                    if (~t >> i & 1) continue;
                    for (auto j : a) {
                        trace("    chk", j, nums[n / 2 + i], i);
                        if (abs(j - nums[n / 2 + i]) == k) {
                            trace("    fail", j, i, nums[n / 2 + i]);
                            ok = 0;
                            break;
                        }
                    }
                    if (!ok) break;
                }
                ans += ok;
            }
        }
        return ans - 1;
    }
};

#pragma region demo {
#if LOCAL && 01
Solution $s; int main() { auto $t = [&]() { cout << "Case #" << ++case_id << ": "; /* cout << $s; */ cout << "\n"; }; $t(); }
#elif !DEBUG
#    pragma clang attribute pop
#endif
#pragma endregion demo }
