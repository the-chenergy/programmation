/* Solution to X-ray Spectrum, a KTH training problem.
   (https://open.kattis.com/problems/spectrum)

   Let err(a, b) denote the minimum error with best choice of simulation energy
   contributed by photons a..b-1. Now the problem becomes to select the best
   (a, b)-range for each of the M choices. This can be solved with a dynamic
   program where the recurrence is
       dp[r, i] := min(dp[r - 1, j] + err(i, j) for j > i)
   Here, dp[r, i] denotes the answer with r choices remaining starting from
   index i.

   Then the error function can be solved as follows, assuming the simulation
   choice is x:
       err(a, b) = sum(k[j] * (j - x)**2 for a < j <= b)
                 = sum(k[j] * j**2 - 2 * k[j] * x + k[j] * x**2)
                 = sum(k[j] * j**2) - 2 * sum(k[j] * j) * x + sum(k[j]) * x**2
   So, if we maintain a total for each of the "sum" terms as we sweep the values
   j > i, we can use ternary search or GSS provided by the KACTL library to find
   the best choice of x in log(N) time. Overall the running time is
   O(N**3 log N).
    */

#include <bits/stdc++.h>
using namespace std;

/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-17
 * License: CC0
 * Source: Numeriska algoritmer med matlab, Gerd Eriksson, NADA, KTH
 * Description: Finds the argument minimizing the function $f$ in the interval
 $[a,b]$ assuming $f$ is unimodal on the interval, i.e. has only one local
 minimum. The maximum error in the result is $eps$. Works equally well for
 maximization with a small change in the code. See TernarySearch.h in the
 Various chapter for a discrete version.
 * Usage:
        double func(double x) { return 4+x+.3*x*x; }
        double xmin = gss(-1000,1000,func);
 * Time: O(\log((b-a) / \epsilon))
 * Status: tested
 */
/// It is important for r to be precise, otherwise we don't necessarily maintain
/// the inequality a < x1 < x2 < b.
template <typename F>
double gss(double a, double b, F f) {
    double r = (sqrt(5) - 1) / 2, eps = 1e-5;
    double x1 = b - r * (b - a), x2 = a + r * (b - a);
    double f1 = f(x1), f2 = f(x2);
    while (b - a > eps)
        if (f1 < f2) {  // change to > to find maximum
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = b - r * (b - a);
            f1 = f(x1);
        } else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = a + r * (b - a);
            f2 = f(x2);
        }
    return a;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<double> k(n);
    for (int i = 0; i < n; i++) cin >> k[i];

    vector<vector<double>> dp(m + 1, vector(n + 1, 1 / 0.));
    for (int r = 0; r <= m; r++) dp[r][n] = 0;
    for (int r = 1; r <= m; r++) {
        for (int i = 0; i <= n; i++) {
            auto& ans = dp[r][i];
            double kj2 = 0, kj = 0, ks = 0;
            for (int j = i; j < n; j++) {
                kj2 += k[j] * j * j;
                kj += k[j] * j;
                ks += k[j];
                auto err = [&](double x) -> double {
                    return kj2 - 2 * kj * x + ks * x * x;
                };
                double x = gss(i, j, err);
                ans = min(ans, err(x) + dp[r - 1][j + 1]);
            }
        }
    }
    cout << setprecision(5) << dp[m][0] << "\n";
}
