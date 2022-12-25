#define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
// #define TRACE_COUT 01  // Use stdout instead of stderr for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
// #define DEBUG 0  // If 0 or unset, disable trace, eprintf, and debug blocks

const double eps = 1E-8;

#pragma region programmation {
#pragma region common {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#ifndef DEBUG
#    define DEBUG 0
#elif DEBUG
// #    define _GLIBCXX_DEBUG 1
// #    define _GLIBCXX_DEBUG_PEDANTIC 1
// #    define _FORTIFY_SOURCE 2
#endif

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int, int>;

template <typename T>
int len(const T& x) {
    return int(x.size());
}
template <typename T, size_t size>
int len(const T (&)[size]) {
    return size;
}

#define __argc(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, n, ...) n
#define _argc(...) __argc(__VA_ARGS__, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define _concat(x, y) __CONCAT(x, y)

#define _range4(b, e, d, i) \
    for (auto i = b; (d) > 0 ? i < (e) : i > (e); i += d)
#define _range1(n) _range4(0, n, 1, _i)
#define _range2(n, i) _range4(0, n, 1, i)
#define _range3(b, e, i) _range4(b, e, 1, i)
// range([begin=0], end, [step=1], i) -> for i in range(begin, end, step)
#define range(...) _concat(_range, _argc(__VA_ARGS__))(__VA_ARGS__)

#define _each2(a, x) for (auto& x : a)
#define _each_(a, ...) for (auto& [__VA_ARGS__] : a)
#define _argc2(...) __argc(__VA_ARGS__, _, _, _, _, _, _, _, _, _, _, 2, 1, 0)
// each(A, ...) -> for ... in A
#define each(...) _concat(_each, _argc2(__VA_ARGS__))(__VA_ARGS__)

// enumerate(A, i, ...) -> for i, (...) in enumerate(A)
#define enumerate(a, i, ...)         \
    for (int i = 0; i != -1; i = -1) \
    each(a, __VA_ARGS__) for (int _##i = 1; _##i; _##i = 0, i++)

int _ADJ4_DIRS[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
#define _adj42(dy, dx) for (auto [dy, dx] : _ADJ4_DIRS)
#define _adj44(cy, cx, y, x)                                              \
    _adj42(_dy, _dx) for (int y = cy + _dy, x = cx + _dx, _##y = 1; _##y; \
                          _##y = 0)
#define _adj46(h, w, cy, cx, y, x) \
    _adj42(y, x) for (y += cy, x += cx; ~y && ~x && y != h && x != w; y = -1)
// adj4([y_lim], [x_lim], cur_y, cur_x, y, x)
//     -> for each (y, x) adjacent to (cy, cx), with optional boundary checks
#define adj4(...) _concat(_adj4, _argc(__VA_ARGS__))(__VA_ARGS__)

#define rep(i, b, e) _range3(b, e, i)
#define trav(x, a) _each2(a, x)
#define all(x) begin(x), end(x)
#define sz len

template <typename TT, typename TS>
bool amax(TT& t, TS s) {
    return t < s && (t = s, true);
}
template <typename TT, typename TS>
bool amin(TT& t, TS s) {
    return s < t && (t = s, true);
}

// Example: partition_point(all(A), selecting(x, len(x) < 2))
#define selecting(x, ...) [&](auto& x) { return __VA_ARGS__; }

// Example: sort(all(A), comparing(x, len(x)))
#define comparing(x, ...)                               \
    [&](auto& _l, auto& _r) {                           \
        auto _f = [&](auto& x) { return __VA_ARGS__; }; \
        return _f(_l) < _f(_r);                         \
    }

// Example: accumulate(all(A), 0LL, adding(x, len(x)))
#define adding(x, ...) [&](auto _s, auto& x) { return _s + (__VA_ARGS__); }

// Binary search
// Example: first_where(0, len(A), i, len(A[i]) >= 2)
#define first_where(b, e, i, ...)                                        \
    [&](decltype(e) _b, decltype(e) _e, decltype(e) i) {                 \
        while (_b < _e)                                                  \
            i = _b + (_e - _b) / 2, (__VA_ARGS__) ? _e = i : _b = i + 1; \
        return _b;                                                       \
    }(b, e, 0)

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
    for (auto&& y : x) out << delim << y, delim = ", ";
    return out << "}";
}
template <typename T, size_t size,
          enable_if_t<!is_same<T, char>::value, int> = 0>
ostream& operator<<(ostream& out, const T (&x)[size]) {
    out << "{";
    string delim;
    for (auto&& y : x) out << delim << y, delim = ", ";
    return out << "}";
}
template <typename T, size_t size>
ostream& operator<<(ostream& out, const std::array<T, size>& x) {
    out << "{";
    string delim;
    for (auto&& y : x) out << delim << y, delim = ", ";
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
    apply([&](auto&&... y) { (..., (out << delim << y, delim = ", ")); }, x);
    return out << "}";
}
}  // namespace std

struct _teed_cout {
    bool _opened = false;
    ofstream _file_out;
    void open(const char* path) { _file_out.open(path), _opened = true; }
    template <typename T>
    _teed_cout& operator<<(const T& x) {
        return cout << x, _opened && (_file_out << x), *this;
    }
} _teed_cout;
ostream& _cout = cout;

#if TRACE_COUT
#    define _trace_out cout
#else
#    define _trace_out cerr
// Outputs to both console and file. Access original cout via _cout.
#    define cout _teed_cout
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
    _trace_out << arg1 << ", ", _trace(labels + first_label_size + 1, args...);
}

template <typename T>
void _view(const T& x) {
    _trace_out << x;
}

template <typename T, typename... TRange>
void _view(const T& x, int b, int e, TRange... ranges) {
    b < 0 && (b += len(x)), e < 0 && (e += len(x));
    b = min(max(b, 0), len(x)), e = min(max(e, b), len(x));
    auto it = begin(x);
    advance(it, b);
    _trace_out << "{";
    for (int i = b; i < e; it++, i++) {
        if (i != b) _trace_out << ", ";
        _view(*it, ranges...);
    }
    _trace_out << "}";
}

#if DEBUG
// printf into cerr
#    if TRACE_COUT
#        define eprintf printf
#    else
#        define eprintf(...) fprintf(stderr, __VA_ARGS__)
#    endif
// trace(x, ...) -> prints "x: {x}, ..." to cerr
#    define trace(...) (_trace(#__VA_ARGS__, __VA_ARGS__), 0)
// view(X, b1, e1, ...) prints X[b1:e1, ...] to cerr
#    define view(...) (_view(__VA_ARGS__), trace(""), 0)
#    define debug
#else
#    define eprintf(...) (void)0
#    define trace(...) ((void)0, 0)
#    define view(...) ((void)0, 0)
#    define debug while (false)
#endif

int num_cases = 1, case_id;

#if !NO_MAIN
void solve_suite();
int main() { solve_suite(); }
#endif
#pragma endregion common }

// Additional library code
/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
template <class T>
int sgn(T x) {
    return (x > 0) - (x < 0);
}
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); }  // makes dist()=1
    P perp() const { return P(-y, x); }        // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
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
typedef Point<double> P;
double segDist(P& s, P& e, P& p) {
    if (s == e) return (p - s).dist();
    auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}
/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true iff p lies on the line segment from s to e.
 * Use \texttt{(segDist(s,e,p)<=epsilon)} instead when using Point<double>.
 * Status:
 */
template <class P>
bool onSegment(P s, P e, P p) {
    return segDist(s, e, p) <= 1E-7;
}
/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true if p lies within the polygon. If strict is true,
 * it returns false for points on the boundary. The algorithm uses
 * products in intermediate steps so watch out for overflow.
 * Time: O(n)
 * Usage:
 * vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
 * bool in = inPolygon(v, P{3, 3}, false);
 * Status: stress-tested and tested on kattis:pointinpolygon
 */
template <class P>
bool inPolygon(vector<P>& p, P a, bool strict = true) {
    int cnt = 0, n = sz(p);
    rep(i, 0, n) {
        P q = p[(i + 1) % n];
        if (onSegment(p[i], q, a)) return !strict;
        // or: if (segDist(p[i], q, a) <= eps) return !strict;
        cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
    }
    return cnt;
}
/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-27
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
If a unique intersection point between the line segments going from s1 to e1 and
from s2 to e2 exists then it is returned. If no intersection point exists an
empty vector is returned. If infinitely many exist a vector with 2 elements is
returned, containing the endpoints of the common line segment. The wrong
position will be returned if P is Point<ll> and the intersection point does not
have integer coordinates. Products of three coordinates are used in intermediate
steps so watch out for overflow if using int or long long. \end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * Usage:
 * vector<P> inter = segInter(s1,e1,s2,e2);
 * if (sz(inter)==1)
 *   cout << "segments intersect at " << inter[0] << endl;
 * Status: stress-tested, tested on kattis:intersection
 */
template <class P>
vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c),
         od = a.cross(b, d);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {all(s)};
}
/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
If a unique intersection point of the lines going through s1,e1 and s2,e2 exists
\{1, point\} is returned. If no intersection point exists \{0, (0,0)\} is
returned and if infinitely many exists \{-1, (0,0)\} is returned. The wrong
position will be returned if P is Point<ll> and the intersection point does not
have integer coordinates. Products of three coordinates are used in intermediate
steps so watch out for overflow if using int or ll. \end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}
 * Usage:
 * 	auto res = lineInter(s1,e1,s2,e2);
 * 	if (res.first == 1)
 * 		cout << "intersection point at " << res.second << endl;
 * Status: stress-tested, and tested through half-plane tests
 */
template <class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (abs(d) < eps)  // if parallel
        return {-(abs(s1.cross(e1, s2)) < eps), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
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
    double r = (sqrt(5) - 1) / 2;
    double x1 = b - r * (b - a), x2 = a + r * (b - a);
    double f1 = f(x1), f2 = f(x2);
    while (b - a > eps)
        if (
            // trace(a, b, x1, x2, f1, f2),
            f1 < f2) {  // change to > to find maximum
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

#pragma GCC diagnostic pop
#pragma endregion programmation }

using pd = Point<double>;

int n;
double w, h;
pd tc, tl, tr, tb, tt;
vector<pd> tps, ps;
double lef = 1 / .0, rig = -1 / .0, bot = 1 / .0, top = -1 / .0;

bool close(double a, double b) { return abs(a - b) < eps; }
bool close(pd a, pd b) {
    auto c = a - b;
    return abs(c.x) < eps && abs(c.y) < eps;
}

bool tile_has(pd bl) {
    if (inPolygon(ps, (bl + tc))) {
        // trace("rec center in pol", bl);
        return true;
    }
    vector<pd> blp{bl, bl + tps[1], bl + tps[2], bl + tps[3]};
    if (any_of(all(blp), selecting(p, inPolygon(ps, p)))) {
        // trace("ver pol in rec", bl);
        return true;
    }
    if (any_of(all(ps), selecting(p, inPolygon(blp, p)))) {
        // trace("ver rec in pol", bl);
        return true;
    }
    range(n, i) {
        int iv = 0, ie = 0;
        range(4, j) {
            auto inter =
                segInter(ps[i], ps[(i + 1) % n], blp[j], blp[(j + 1) % 4]);
            if (len(inter) == 1) {
                bool cl1 = close(inter[0], blp[j]),
                     cl2 = close(inter[0], blp[(j + 1) % 4]);
                if (!cl1 && !cl2 && !close(inter[0], ps[i]) &&
                    !close(inter[0], ps[(i + 1) % n])) {
                    // trace("intersect", bl, ps[i], ps[(i + 1) % n], inter);
                    return true;
                }
                if (cl1) iv |= 1 << j;
                if (cl2) iv |= 1 << ((j + 1) % 4);
                if (!cl1 && !cl2) ie++;
                if (ie == 2 || (ie == 1 && iv) || (iv & 1 && iv & 4) ||
                    (iv & 2 && iv & 8)) {
                    // trace("cross", bl, ps[i], ps[(i + 1) % n], iv, ie);
                    return true;
                }
            }
            // auto smp = ps[i] + ps[(i + 1) % n];
            // if (inPolygon(blp, pd(smp.x / 2., smp.y / 2.))) {
            //     // trace("mid edge pol in rec", bl);
            //     return true;
            // }
        }
    }
    return false;
}

pair<double, double> bound_x(double x) {
    return {min(x - ceil((x - lef) / w) * w, x) - w,
            max(x + ceil((rig - x) / w) * w, x) + w};
}
pair<double, double> bound_y(double y) {
    return {min(y - ceil((y - bot) / h) * h, y) - h,
            max(y + ceil((top - y) / h) * h, y) + h};
}
pd mwh(pd p) {
    p.x = fmod(p.x, w), p.y = fmod(p.y, h);
    if (p.x < 0) p.x += w;
    if (p.y < 0) p.y += h;
    return p;
}

int count_tiles(pd c) {
    c = mwh(c);
    vector<double> hx, hy;
    int t = 0;
    auto [xl, xh] = bound_x(c.x);
    auto [yl, yh] = bound_y(c.y);
    // trace("ct", c, xl, xh, yl, yh, (xh - xl) / w, (yh - yl) / h);
    range(xl, xh + w, w, x) {
        range(yl, yh + h, h, y) {
            if (tile_has(pd(x, y))) {
                // trace("TILE HAS IT", x, y);
                debug hx.push_back(x), hy.push_back(y);
                t++;
            } else {
                // trace("tile nah", x, y);
            }
        }
    }
    // debug trace(hx, hy);
    return t;
}

void solve() {
    cin >> n;
    if (0 || !cin) exit(0);
    if (n < 0) cin >> n;
    cin >> w >> h;
    lef = 1 / .0, rig = -1 / .0, bot = 1 / .0, top = -1 / .0;
    tps = {pd(0, 0), pd(w, 0), pd(w, h), pd(0, h)};
    tc = pd(w / 2., h / 2.);
    ps.resize(n);
    range(n, i) {
        double x, y;
        cin >> x >> y;
        ps[i].x = x, ps[i].y = y;
        if (amin(lef, x)) tl = ps[i];
        if (amax(rig, x)) tr = ps[i];
        if (amin(bot, y)) tb = ps[i];
        if (amax(top, y)) tt = ps[i];
    }
    trace(n, w, h, ps, lef, rig, bot, top);

    debug if (!cerr) {
        return;
        ;
    }

    int ans = 1E9;
    pd ap, cp;

    // cerr.clear(_S_failbit);
    // return (void)trace(count_tiles(pd(4, 5)));
    debug if (0) {
        range(0., 2., .001, y) if (amin(ans, count_tiles(pd(18, y)))) ap =
            pd(18, y);
        trace(ans, ap);
        return;
    }

    each(ps, p) {
        // Snap X and Y to a pair of vertices
        each(ps, q) {
            cp = pd(p.x, q.y);
            if (amin(ans, count_tiles(cp))) ap = cp;
        }

        range(n, i) {
            // Snap X to P and intersect Y with an edge
            double xl, xh, yl, yh;
            tie(xl, xh) = bound_x(p.x);
            yl = bot, yh = top;
            range(xl, xh + w, w, x) {
                auto inter =
                    segInter(ps[i], ps[(i + 1) % n], pd(x, yl), pd(x, yh));
                if (len(inter) == 1) {
                    // if (p == pd(20, 12) && (ps[(i + 1) % n] == pd(35, 23))) {
                    //     cerr.clear();
                    //     trace("hi", x, yl, yh, ps[i], ps[(i + 1) % n],
                    //           inter[0]);
                    // }
                    if (amin(ans, count_tiles(inter[0]))) ap = inter[0];
                }
            }

            // Snap Y to P and intersect X with an edge
            tie(yl, yh) = bound_y(p.y);
            xl = lef, xh = rig;
            range(yl, yh + h, h, y) {
                auto inter =
                    segInter(ps[i], ps[(i + 1) % n], pd(xl, y), pd(xh, y));
                if (len(inter) == 1) {
                    if (amin(ans, count_tiles(inter[0]))) ap = inter[0];
                }
            }
        }
    }
    range(n, i) range(i + 2, n, j) {
        auto inter = lineInter(ps[i], ps[(i + 1) % n], ps[j], ps[(j + 1) % n]);
        if (i == 0 && j == 3) trace("hi", inter, mwh(inter.second));
        if (!inter.first) continue;
        assert(inter.first < 2);
        if (amin(ans, count_tiles(inter.second))) ap = inter.second;
    }

    trace(ap, mwh(ap), ans);
    debug if (40) {
        range(0., w, w / 50, x) range(0., h, h / 50, y) {
            cp = pd(x, y);
            if (amin(ans, count_tiles(cp))) ap = cp;
        }
        trace(ap, mwh(ap), ans);
    }

    cout << ans;
}

void solve_suite() {
    debug freopen("./sandbox/i3.txt", "r", stdin);
    // debug cout.open("./sandbox/o.txt");
    // cin >> num_cases;
    debug num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        debug cerr.clear(case_id == 97 ? _S_goodbit : _S_failbit);
        debug _cout.clear(cerr ? _S_goodbit : _S_failbit);
        debug cout << "Case #" << case_id << ": ";
        solve();
        cout << "\n";
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
