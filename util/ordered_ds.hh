#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename TKey, typename TValue>
using ordered_map = tree<TKey, TValue, less<TKey>, rb_tree_tag,
                         tree_order_statistics_node_update>;
// find_by_order(int) -> it
// order_of_key(TKey) -> int
// Both act like lower_bound (finds >=)
