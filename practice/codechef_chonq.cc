/* Solution to "Cheating on Queue", a problem from the CodeChef February
   Challenge 2019 (https://www.codechef.com/problems/CHONQ).

   Think about how a person's anger score decays as the chef moves forward in
   the queue. Let's say there's guy with an anger score of 10. As the chef hops
   forward and away from this guy, his anger contribution goes something like
   {10, 5, 3, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, ...}. Notice that most of the time
   his contribution will be small and the same number (look at how many 0s and
   1s there are). Particularly, his anger contribution only changes at most
   O(sqrt A) times, A being his maximum anger score. It changes at every index
   up to sqrt(A), then only changes at every (A / i) indices for integers
   i <= sqrt(A).

   So, we can just precompute for each person in the queue, where the change
   points are with their anger contribution, and we can mark the changes in a
   difference array. This process takes O(N sqrt A). Then we simply sweep and
   find the first moment where the total anger is below K. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        [&] {
            int n;
            cin >> n;
            if (n < 0) cin >> n;
            long long k;
            cin >> k;
            static int a[100001];
            for (int i = 0; i < n; i++) cin >> a[i];

            static long long diff[100001];
            fill_n(diff, n + 1, 0);
            for (int i = 0; i < n; i++) {
                for (int j = 1; j * j <= a[i]; j++) {
                    if (i - j + 1 >= 0 && j != a[i] / j) {
                        diff[i - j + 1] += a[i] / j;
                        diff[i - j + 2] -= a[i] / j;
                    }
                    if (i - a[i] / (j + 1) + 1 > 0) {
                        diff[max(i - a[i] / j + 1, 0)] += j;
                        diff[i - a[i] / (j + 1) + 1] -= j;
                    }
                }
            }

            long long cur = 0;
            for (int i = 0; i < n; i++) {
                cur += diff[i];
                if (cur <= k) {
                    cout << i + 1 << "\n";
                    return;
                }
            }
            cout << n + 1 << "\n";
        }();
    }
}