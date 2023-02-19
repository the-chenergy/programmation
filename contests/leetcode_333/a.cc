class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        map<int,int>ans;
        for(auto&a:nums1)ans[a[0]]+=a[1];
        for(auto&a:nums2)ans[a[0]]+=a[1];
        vector<vector<int>>ret;
        for(auto[x,y]:ans)ret.push_back({x,y});
        return ret;
    }
};
