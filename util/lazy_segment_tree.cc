
/** A lazy sparse segment tree that supports range queries (sum, max) and
    updates (addition, assignment), all in O(log N).

    Usage:
        segment_tree<int, int> st(0, 7);  // st = {0, 0, 0, 0, 0, 0, 0}
        st.assign(2, 6, 5);               // st = {0, 0, 5, 5, 5, 5, 0}
        st.add(1, 4, 3);                  // st = {0, 3, 8, 8, 5, 5, 0}
        st.query_sum(0, 5);               // returns 0 + 3 + 8 + 8 + 5 = 24
        st.query_max(0, 5);               // returns max(0, 3, 8, 8, 5) = 8
*/
template <typename K = int, typename V = int>
struct segment_tree {
    const V INF = numeric_limits<V>::max() / 2;
    unique_ptr<segment_tree<K, V>> _left = 0, _right = 0;
    V _sum = 0, _max = 0, _assigned = INF, _added = 0;
    K _low, _high;
    /** Initializes tree[begin..end) = 0 in O(1). */
    segment_tree(K begin, K end) : _low(begin), _high(end) {}
    void _push() {
        if (!_left) {
            K mid = _low + (_high - _low) / 2;
            _left = make_unique<segment_tree<K, V>>(_low, mid);
            _right = make_unique<segment_tree<K, V>>(mid, _high);
        }
        if (_assigned != INF) {
            _left->assign(_low, _high, _assigned);
            _right->assign(_low, _high, _assigned);
            _assigned = INF;
        }
        if (_added) {
            _left->add(_low, _high, _added);
            _right->add(_low, _high, _added);
            _added = 0;
        }
    }
    /** Assigns tree[begin..end) = value in O(log N). */
    void assign(K begin, K end, V value) {
        if (begin >= _high || end <= _low) return;
        if (begin <= _low && end >= _high) {
            _assigned = value;
            _added = 0;
            _sum = (_high - _low) * value;
            _max = value;
            return;
        }
        _push();
        _left->assign(begin, end, value);
        _right->assign(begin, end, value);
        _sum = _left->_sum + _right->_sum;
        _max = max(_left->_max, _right->_max);
    }
    /** Adds tree[begin..end) += value in O(log N). */
    void add(K begin, K end, V value) {
        if (begin >= _high || end <= _low) return;
        if (begin <= _low && end >= _high) {
            if (_assigned != INF) _assigned += value;
            else _added += value;
            _sum += (_high - _low) * value;
            _max += value;
            return;
        }
        _push();
        _left->add(begin, end, value);
        _right->add(begin, end, value);
        _sum = _left->_sum + _right->_sum;
        _max = max(_left->_max, _right->_max);
    }
    /** Queries sum(tree[begin..end)) in O(log N). */
    V query_sum(K begin, K end) {
        if (begin >= _high || end <= _low) return 0;
        if (begin <= _low && end >= _high) return _sum;
        _push();
        return _left->query_sum(begin, end) + _right->query_sum(begin, end);
    }
    /** Queries max(tree[begin..end)) in O(log N). */
    V query_max(K begin, K end) {
        if (begin >= _high || end <= _low) return -INF;
        if (begin <= _low && end >= _high) return _max;
        _push();
        return max(_left->query_max(begin, end), _right->query_max(begin, end));
    }
};
