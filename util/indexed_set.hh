#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename value_t>
using indexed_set = tree<value_t, null_type, less<value_t>, rb_tree_tag,
                         tree_order_statistics_node_update>;
