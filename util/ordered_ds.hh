#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename K, typename V, typename C = less<>>
using ordered_map =
        tree<K, V, C, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename C = less<>>
using ordered_set = ordered_map<T, null_type, C>;
// find_by_order(int) -> iterator
// order_of_key(K) -> int (index of first >=)
