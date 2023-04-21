/* Solution to "Baby Names", a problem from NUS Competitive Programming.

   A classic trie problem, where we let each trie node also record the numbers
   of boy- and girl-names starting with this prefix. Run time: O(K), K being the
   total characters in all names and queries.

   As pointed out by the hint giver, this problem can also be solved with two
   order statistic trees, one each for the two genders. Then just perform two
   index subtractions for gender 0 queries. Run time should be O(N log N), N
   being the peek number of names.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    static int t[200000 * 30 + 1][29], ts = 1;
    unordered_map<string, int> gen;
    gen.max_load_factor(.25), gen.reserve(200000);

    while (1) {
        int qt;
        cin >> qt;
        if (!qt) break;
        if (qt == 1) {
            string s;
            int g;
            cin >> s >> g;
            int i = 0;
            for (auto c : s) {
                t[i][26]++;
                t[i][26 + g]++;
                int& j = t[i][c - 'A'];
                if (!j) j = ts++;
                i = j;
            }
            t[i][26]++;
            t[i][26 + g]++;
            gen[s] = g;
        } else if (qt == 2) {
            string s;
            cin >> s;
            int g = gen[s], i = 0;
            gen.erase(s);
            for (auto c : s) {
                t[i][26]--;
                t[i][26 + g]--;
                i = t[i][c - 'A'];
            }
            t[i][26]--;
            t[i][26 + g]--;
        } else if (qt == 3) {
            string a, b;
            int g;
            cin >> a >> b >> g;
            auto que = [&](string& x) -> int {
                int i = 0, ans = 0;
                for (int k = 0; k < (int)x.size(); k++) {
                    auto c = x[k];
                    if (k && !i) break;
                    for (int d = 0; d < c - 'A'; d++) {
                        int j = t[i][d];
                        if (j) {
                            ans += t[j][26 + g];
                            // cerr << t[j][26 + g] << " names start with "
                            //      << x.substr(0, k + 1) << "\n";
                        }
                    }
                    i = t[i][c - 'A'];
                }
                return ans;
            };
            cout << que(b) - que(a) << "\n";
        }
    }
}
