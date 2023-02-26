class Solution {
public:
    vector<int> leftRigthDifference(vector<int>& nums) {
        vector<int>ans;
        for(int i=0;i<nums.size();i++){
            int s=0;
            for(int j=0;j<i;j++)s+=nums[j];
            for(int j=i+1;j<nums.size();j++)s-=nums[j];
            ans.push_back(abs(s));
        }
        return ans;
    }
};
