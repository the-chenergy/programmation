/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        vector<long long> levels;
        deque<TreeNode*> bfs = {root};
        for (int level = -1, l = 0; l || (level++, l = bfs.size()); l--) {
            if (level == levels.size())
                levels.push_back(0);
            auto node = bfs.front();
            bfs.pop_front();
            levels.back() += node->val;
            if (node->left)
                bfs.push_back(node->left);
            if (node->right)
                bfs.push_back(node->right);
        }
        sort(levels.rbegin(), levels.rend());
        k--;
        if (k >= levels.size())
            return -1;
        return levels[k];
    }
};
