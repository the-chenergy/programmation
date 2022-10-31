using point = complex<int>;

#define X real()
#define Y imag()

namespace std {
template <typename T>
static bool operator<(const complex<T>& a, const complex<T>& b) {
    return a.X != b.X ? a.X < b.X : a.Y < b.Y;
}
}  // namespace std
