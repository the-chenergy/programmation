#define cout 0 && cout


#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */
#pragma once

// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "typedef ull H;" instead if you think test data is random,
// or work mod 10^9+7 if the Birthday paradox is not a problem.
typedef uint64_t ull;
struct H {
	ull x; H(ull x=0) : x(x) {}
	H operator+(H o) { return x + o.x + (x + o.x < x); }
	H operator-(H o) { return *this + ~o.x; }
	H operator*(H o) { auto m = (__uint128_t)x * o.x;
		return H((ull)m) + (ull)(m >> 64); }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

vector<H> getHashes(string& str, int length) {
	if (sz(str) < length) return {};
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h};
	rep(i,length,sz(str)) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}

H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}


class Solution {
public:
    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        cout << "----\n";
        cout << "0....,....1....,....2....,....3....,....4\n" << s << "\n";
        int n = s.size() / 2;
        static int pa[50001][26], pb[50001][26];
        for (int i = 0; i < n; i++) {
            memcpy(pa[i + 1], pa[i], sizeof(pa[0]));
            memcpy(pb[i + 1], pb[i], sizeof(pb[0]));
            pa[i + 1][s[i] - 'a']++;
            pb[i + 1][s[2 * n - 1 - i] - 'a']++;
        }
        auto t1 = s.substr(0, n), t2 = s.substr(n, 2 * n);
        reverse(t2.begin(), t2.end());
        HashInterval h1(t1), h2(t2);
        if (cout) {
            auto s2 = s;
            reverse(s2.begin(), s2.end());
            cout << s.substr(0, n) << "\n" << s2.substr(0, n) << "\n";
            if (0) {
                auto s3 = s.substr(2, 13 - 2), s4 = s2.substr(2, 13 - 2);
                sort(s3.begin(), s3.end()), sort(s4.begin(), s4.end());
                cout << s3 << "\n" << s4 << "\n";
            }
        }
        vector<bool> ans, cor;
        if (cout && 01) {
                cor = {true,false,false,false,true,false,false,false,false,true,false,false,false,false,false,true,false,false,true};
        }
        for (int qi = -1; auto& q : queries) {
            qi++;
            int a = q[0], b = q[1], c2 = q[2], d2 = q[3];
            b++;
            int c = 2 * n - 1 - d2, d = 2 * n - 1 - c2 + 1;
            cout << q[0] << " " << q[1] << " " << q[2] << " " << q[3] << "\n";
            cout << a << " " << b << " " << c << " " << d << "\n";
            int ok = [&]() -> int {
                if (c >= a && d <= b || a >= c && b <= d) {
                    cout << "case 1\n";
                    int aa = min(a, c), bb = max(b, d), cc = max(a, c), dd = min(b, d);
                    cout << "\t" << aa << " " << bb << " " << cc << " " << dd << "\n";
                    for (int x = 0; x < 26; x++) {
                        if (pa[bb][x] - pa[aa][x] != pb[bb][x] - pb[aa][x]) {
                            return 0;
                        }
                        // if (pa[aa][x] - pa[0][x] != pb[aa][x] - pb[0][x]) {
                        //     return 0;
                        // }
                        if (0 && x == 4) {
                            cout << "\t" << pa[n][x] << " " << pa[bb][x] << " " << pb[n][x] << " " << pb[bb][x] << "\n";
                        }
                        // if (pa[n][x] - pa[bb][x] != pb[n][x] - pb[bb][x]) {
                        //     return 0;
                        // }
                    }
                    if (h1.hashInterval(0, aa) != h2.hashInterval(0, aa)) {
                        return 0;
                    }
                    if (h1.hashInterval(bb, n) != h2.hashInterval(bb, n)) {
                        return 0;
                    }
                    return 1;
                } else if (max(a, c) >= min(b, d)) {
                    cout << "case 2\n";
                    int aa = min(a, c), bb = min(b, d), cc = max(a, c), dd = max(b, d);
                    for (int x = 0; x < 26; x++) {
                        if (pa[b][x] - pa[a][x] != pb[b][x] - pb[a][x]) {
                            return 0;
                        }
                        if (pa[d][x] - pa[c][x] != pb[d][x] - pb[c][x]) {
                            return 0;
                        }
                        // if (pa[aa][x] - pa[0][x] != pb[aa][x] - pb[0][x]) {
                        //     return 0;
                        // }
                        // if (pa[cc][x] - pa[bb][x] != pb[cc][x] - pb[bb][x]) {
                        //     return 0;
                        // }
                        // if (pa[n][x] - pa[dd][x] != pb[n][x] - pb[dd][x]) {
                        //     return 0;
                        // }
                    }
                    if (h1.hashInterval(0, aa) != h2.hashInterval(0, aa)) {
                        return 0;
                    }
                    if (h1.hashInterval(bb, cc) != h2.hashInterval(bb, cc)) {
                        return 0;
                    }
                    if (h1.hashInterval(dd, n) != h2.hashInterval(dd, n)) {
                        return 0;
                    }
                    return 1;
                } else if (a < c) {
                    cout << "case 3\n";
                    int aa = min(a, c), bb = min(b, d), cc2 = max(a, c), dd2 = max(b, d);
                    // for (int x = 0; x < 26; x++) {
                    //     if (pa[aa][x] - pa[0][x] != pb[aa][x] - pb[0][x]) {
                    //         return 0;
                    //     }
                    //     if (pa[n][x] - pa[dd2][x] != pb[n][x] - pb[dd2][x]) {
                    //         return 0;
                    //     }
                    // }
                    if (h1.hashInterval(0, aa) != h2.hashInterval(0, aa)) {
                        return 0;
                    }
                    if (h1.hashInterval(dd2, n) != h2.hashInterval(dd2, n)) {
                        return 0;
                    }
                    static int ca[26], cb[26], cc[26], cd[26];
                    memset(ca, 0, sizeof(ca));
                    memset(cb, 0, sizeof(cb));
                    for (int x = 0; x < 26; x++) {
                        ca[x] = pa[b][x] - pa[a][x];
                        cb[x] = pb[c][x] - pb[a][x];
                        if (ca[x] < cb[x]) {
                            return 0;
                        }
                        ca[x] -= cb[x];
                    }
                    memset(cc, 0, sizeof(cc));
                    memset(cd, 0, sizeof(cd));
                    for (int x = 0; x < 26; x++) {
                        cc[x] = pa[d][x] - pa[b][x];
                        cd[x] = pb[d][x] - pb[c][x];
                        if (cd[x] < cc[x]) {
                            return 0;
                        }
                        cd[x] -= cc[x];
                    }
                    for (int x = 0; x < 26; x++) {
                        cout << "\t" << x << " " << ca[x] << " " << cb[x] << " " << cc[x] << " " << cd[x] << "\n";
                        if (ca[x] != cd[x]) {
                            return 0;
                        }
                    }
                    return 1;
                } else {
                    assert(a > c);
                    cout << "case 4\n";
                    int aa = min(a, c), bb = min(b, d), cc2 = max(a, c), dd2 = max(b, d);
                    // for (int x = 0; x < 26; x++) {
                    //     if (pa[aa][x] - pa[0][x] != pb[aa][x] - pb[0][x]) {
                    //         return 0;
                    //     }
                    //     if (pa[n][x] - pa[dd2][x] != pb[n][x] - pb[dd2][x]) {
                    //         return 0;
                    //     }
                    // }
                    if (h1.hashInterval(0, aa) != h2.hashInterval(0, aa)) {
                        return 0;
                    }
                    if (h1.hashInterval(dd2, n) != h2.hashInterval(dd2, n)) {
                        return 0;
                    }
                    static int ca[26], cb[26], cc[26], cd[26];
                    memset(ca, 0, sizeof(ca));
                    memset(cb, 0, sizeof(cb));
                    for (int x = 0; x < 26; x++) {
                        ca[x] = pa[b][x] - pa[a][x];
                        cb[x] = pb[b][x] - pb[d][x];
                        if (ca[x] < cb[x]) {
                            return 0;
                        }
                        ca[x] -= cb[x];
                    }
                    memset(cc, 0, sizeof(cc));
                    memset(cd, 0, sizeof(cd));
                    for (int x = 0; x < 26; x++) {
                        cc[x] = pa[a][x] - pa[c][x];
                        cd[x] = pb[d][x] - pb[c][x];
                        if (cd[x] < cc[x]) {
                            return 0;
                        }
                        cd[x] -= cc[x];
                    }
                    for (int x = 0; x < 26; x++) {
                        cout << "\t" << x << " " << ca[x] << " " << cb[x] << " " << cc[x] << " " << cd[x] << "\n";
                        if (ca[x] != cd[x]) {
                            return 0;
                        }
                    }
                    return 1;
                }
            }();
            cout << ok << "\n";
            if (cout && cor.size()) {
                assert(ok == cor[qi]);
            }
            ans.push_back(ok);
        }
        // exit(1);
        return ans;
    }
};
