/* Solution to "Colliding Encoding", problem A from the Google Code Jam Farewell
   Round A.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c95b94/0000000000cad7cf)
*/

#include <bits/stdc++.h>
using namespace std;

static void solve(int /* case_id */) {
    static char mp[26];
    for (int c = 0; c < 26; c++) cin >> mp[c];
    int n;
    cin >> n;
    unordered_set<string> st;
    int dup = 0;
    while (n--) {
        string s;
        cin >> s;
        for (auto& c : s) c = mp[c - 'A'];
        dup |= !st.insert(s).second;
    }
    cout << (dup ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int cases;
    cin >> cases;
    for (int i = 1; i <= cases; i++) {
        cout << "Case #" << i << ": ";
        solve(i);
    }
}
