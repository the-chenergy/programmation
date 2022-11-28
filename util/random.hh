
static mt19937 _mt_rng(
    unsigned(chrono::steady_clock::now().time_since_epoch().count()));

// Returns a uniform random integer within [inc a..inc b]
template <typename T>
static T randint(T a, T b) {
    return uniform_int_distribution<T>(a, b)(_mt_rng);
}
