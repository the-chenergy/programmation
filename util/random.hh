static mt19937 mt_rng(
    unsigned(chrono::steady_clock::now().time_since_epoch().count()));

template <typename T>
static T randint(T a, T b) {
    return uniform_int_distribution<T>(a, b)(mt_rng);
}
