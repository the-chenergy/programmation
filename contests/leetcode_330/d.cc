using ll=long long;
int l[4009][4009],r[4009][4009];

class Solution {
public:
    long long countQuadruplets(vector<int>& nums) {
        int n=nums.size();
        memset(l,0,sizeof(l[0])*(n+2));
        memset(r,0,sizeof(l[0])*(n+2));
        for(int i=0;i<n;i++){
            for(int j=1;j<=n;j++){
                l[i+1][j]=l[i][j]+(nums[i]<=j);
                // cout<<i<<" "<<j<<" "<<l[i+1][j]<<"\n";
            }
        }
        for(int i=n-1;i>=0;i--){
            for(int j=1;j<=n;j++){
                r[i+1][j]=r[i+2][j]+(nums[i]>=j);
                // cout<<i<<" "<<j<<" "<<r[i+1][j]<<"\n";
            }
        }
        ll ans=0;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(nums[i]>nums[j]){
                    ans+=l[i+1][nums[j]-1]*r[j+1][nums[i]+1];
                }
            }
        }
        return ans;
    }
};
