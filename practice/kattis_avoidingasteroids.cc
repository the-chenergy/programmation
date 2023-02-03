// Solution to Avoiding Asteroids, a problem from the ICPC NAQ 2021
// (https://open.kattis.com/problems/avoidingasteroids)
// #geometry #binary_search
//
// The problem could be simplified a bit to "given a line segment and a set of
// rays, check if any ray and the segment is at distance less than D_i at the
// closest point." We can simplify the problem like that because the asteroids
// can move or rotate at any speed, so basically each asteroid can behave like a
// ball sweeping through 3D, where the radius of the ball is the point on the
// hull that's the furthest away from the center. So all we need to do is turn
// every asteroid into a ray and a radius, and we just check if the
// spaceship-base segment comes closer than radius to the ray.
//
// The KACTL library apparently only provided the code for measuring the
// distance between a segment and a point. So what I did was approximate the ray
// with a segment having the other endpoint being really far away, then I binary
// searched the points in between the spaceship and base to find the closest
// point to the ray.

// #define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
// #define TRACE_COUT 01  // Use stdout instead of stderr for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
// #define DEBUG 0  // If 0 or unset, disable trace, eprintf, and debug blocks

#pragma region programmation {
#pragma region common {  // clang-format off
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#ifndef DEBUG
#    define DEBUG 0
#endif
#if DEBUG
#    define _GLIBCXX_DEBUG 1
#    define _GLIBCXX_DEBUG_PEDANTIC 1
#    define _FORTIFY_SOURCE 2
#    pragma GCC optimize("trapv")
#    if TRACE_COUT
#        define eprintf printf
#    else
#        define eprintf(...) fprintf(stderr, __VA_ARGS__)  // printf into cerr
#    endif
#    define trace(...) (_trace(#__VA_ARGS__, __VA_ARGS__), 0)  // trace(x, ...) -> prints "x: {x}, ..." to cerr
#    define view(...) (_view(__VA_ARGS__), trace(""), 0)  // view(X, b1, e1, ...) prints X[b1:e1, ...] to cerr
#    define debug
#else
#    define eprintf(...) ((void)0, 0)
#    define trace(...) ((void)0, 0)
#    define view(...) ((void)0, 0)
#    define debug while (0)
#endif
#include <bits/stdc++.h>
#define rep(i, b, e) for (int i = b; i < (e); i++)
#define trav(x, a) for (auto& x : a)
#define all(x) begin(x), end(x)
#define sz len
#define _print_vector_impl s << "{"; string d; for (auto&& y : x) s << d << y, d = ", "; return s << "}";
using namespace std; using ll = long long; using ull = unsigned long long; using ld = long double; using vi = vector<int>; using pii = pair<int, int>; template <typename T> int len(const T& x) { return int(x.size()); } template <typename T, size_t l> int len(const T (&)[l]) { return l; } template <typename T, typename S> bool amax(T& t, S s) { return t < s && (t = s, 1); } template <typename T, typename S> bool amin(T& t, S s) { return s < t && (t = s, 1); } int num_cases = 1, case_id; namespace std { template <typename T, size_t l> ostream& operator<<(ostream& s, const array<T, l>& x); template <typename F, typename S> ostream& operator<<(ostream& s, const pair<F, S>& x); template <typename... T> ostream& operator<<(ostream& s, const tuple<T...>& x); template <typename C, typename T = enable_if_t<!is_same<C, string>::value, typename C::value_type>> ostream& operator<<(ostream& s, const C& x) { _print_vector_impl } template <typename T, size_t l, enable_if_t<!is_same<T, char>::value, int> = 0> ostream& operator<<(ostream& s, const T (&x)[l]) { _print_vector_impl } template <typename T, size_t l> ostream& operator<<(ostream& s, const std::array<T, l>& x) { _print_vector_impl } template <typename F, typename S> ostream& operator<<(ostream& s, const pair<F, S>& x) { return s << "{" << x.first << ", " << x.second << "}"; } template <typename... T> ostream& operator<<(ostream& s, const tuple<T...>& x) { s << "{"; string d; apply([&](auto&&... y) { (..., (s << d << y, d = ", ")); }, x); return s << "}"; } } struct _teed_cout { bool _b = 0; ofstream _f; void open(const char* s) { _f.open(s), _b = 1; } template <typename T> _teed_cout& operator<<(const T& x) { return cout << x, _b && (_f << x), *this; } } _teed_cout; ostream& _cout = cout;
#if TRACE_COUT
#    define _trace_out cout
#else
#    define _trace_out cerr
#    define cout _teed_cout  // Outputs to both console and file. Access original cout via _cout.
#endif
template <typename T> void _trace(const char* l, const T& x) { if (l[0] != '"') _trace_out << l + (l[0] == ' ') << ": "; _trace_out << x << "\n"; } template <typename T, typename... A> void _trace(const char* l, const T& x, const A&... a) { if (l[0] == ' ') l++; size_t s = strchr(l, ',') - l; if (l[0] != '"') _trace_out.write(l, s) << ": "; _trace_out << x << ", ", _trace(l + s + 1, a...); } template <typename T> void _view(const T& x) { _trace_out << x; } template <typename T, typename... R> void _view(const T& x, int b, int e, R... r) { b < 0 && (b += len(x)), e < 0 && (e += len(x)); b = min(max(b, 0), len(x)), e = min(max(e, b), len(x)); auto it = begin(x); advance(it, b); _trace_out << "{"; for (int i = b; i < e; it++, i++) { if (i != b) _trace_out << ", "; _view(*it, r...); } _trace_out << "}"; }
#if !SYNC_IO
void _init() __attribute__((constructor)); void _init() { ios::sync_with_stdio(0), cin.tie(0); }
#endif
#if !NO_MAIN
void solve_suite(); int main() { solve_suite(); }
#endif
#pragma endregion common }  // clang-format on

// Additional library code
/**
 * Author: Ulf Lundstrom with inspiration from tinyKACTL
 * Date: 2009-04-14
 * License: CC0
 * Source:
 * Description: Class to handle points in 3D space.
 * 	T can be e.g. double or long long.
 * Usage:
 * Status: tested, except for phi and theta
 */
template <class T>
struct Point3D {
    typedef Point3D P;
    typedef const P& R;
    T x, y, z;
    explicit Point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    bool operator<(R p) const { return tie(x, y, z) < tie(p.x, p.y, p.z); }
    bool operator==(R p) const { return tie(x, y, z) == tie(p.x, p.y, p.z); }
    P operator+(R p) const { return P(x + p.x, y + p.y, z + p.z); }
    P operator-(R p) const { return P(x - p.x, y - p.y, z - p.z); }
    P operator*(T d) const { return P(x * d, y * d, z * d); }
    P operator/(T d) const { return P(x / d, y / d, z / d); }
    T dot(R p) const { return x * p.x + y * p.y + z * p.z; }
    P cross(R p) const {
        return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    T dist2() const { return x * x + y * y + z * z; }
    double dist() const { return sqrt((double)dist2()); }
    // Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
    double phi() const { return atan2(y, x); }
    // Zenith angle (latitude) to the z-axis in interval [0, pi]
    double theta() const { return atan2(sqrt(x * x + y * y), z); }
    P unit() const { return *this / (T)dist(); }  // makes dist()=1
    // returns unit vector normal to *this and p
    P normal(P p) const { return cross(p).unit(); }
    // returns point rotated 'angle' radians ccw around axis
    P rotate(double angle, P axis) const {
        double s = sin(angle), c = cos(angle);
        P u = axis.unit();
        return u * dot(u) * (1 - c) + (*this) * c - cross(u) * s;
    }
    friend ostream&operator<<(ostream&s,P p){
        s<<"("<<p.x<<","<<p.y<<","<<p.z<<")";
        return s;
    }
};

/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
Returns the shortest distance between point p and the line segment from point s
to e. \end{minipage} \begin{minipage}{15mm} \vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * Usage:
 * 	Point<double> a, b(2,2), p(1,1);
 * 	bool onSegment = segDist(a,b,p) < 1e-10;
 * Status: tested
 */
typedef Point3D<double> P;
double segDist(P& s, P& e, P& p) {
    if (s == e) return (p - s).dist();
    auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}

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
double gss(double a, double b, double (*f)(double)) {
    double r = (sqrt(5) - 1) / 2, eps = 1e-7;
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
    // return a;
    return (f1 + f2) * .5;
}

#pragma GCC diagnostic pop
#pragma endregion programmation }

int n,ans,m;
P s,b,p,d,h,q;
double r;

double cal(double x){
    P y=s+(b-s)*x;
    double sd=segDist(p,q,y);
    trace(x,y,sd);
    return sd;
}

void solve() {
    cin>>s.x>>s.y>>s.z>>b.x>>b.y>>b.z>>n;
    if(!cin)exit(0);
    trace(s,d);
    ans=0;
    while(n--){
        cin>>p.x>>p.y>>p.z>>d.x>>d.y>>d.z>>m;
        r=0;
        while(m--){
            cin>>h.x>>h.y>>h.z;
            amax(r,(h-p).dist2());
        }
        r=sqrt(r);
        q=p+d*4E6;
        double cd=gss(0,1,cal);
        ans|=cd<=r;
        trace(p,r,q,cd);
    }
    cout<<(ans?"Surrender":"Go");
}

void solve_suite() {
    debug freopen("./sandbox/i.txt", "r", stdin);
    // debug cout.open("./sandbox/o.txt");
    // cin >> num_cases;
    debug num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id ==  ? _S_goodbit : _S_failbit);
        debug cout << "Case #" << case_id << ": ";
        solve();
        cout << "\n";
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
