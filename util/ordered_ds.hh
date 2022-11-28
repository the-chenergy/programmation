#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

template <typename T>
// A order statistic tree that provides:
// - find_by_order(int) -> it
// - order_of_key(TKey) -> int (index of first >=)
// To use like a multiset, set pair<T, int> as the key and include a unique int
// timestamp for each T key.
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename TKey, typename TValue>
using ordered_map = tree<TKey, TValue, less<TKey>, rb_tree_tag,
                         tree_order_statistics_node_update>;
