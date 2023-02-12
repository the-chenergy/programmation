using vi=vector<int>;
class Solution {
public:
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {
        // cout<<"----\n";
        vector<vi> ans(size(queries));
        unordered_map<int,array<int,2>>val;
        for(int i=size(s)-1;i>=0;i--){
            int x=0;
            for(int j=0;j<31&&i-j>=0;j++){
                if(s[i-j]=='1'){
                    x|=1<<j;
                    int r=j+1;
                    // cout<<i<<" "<<j<<" "<<r<<" "<<val[x][0]<<" "<<val[x][1]<<"\n";
                    if(!val.count(x)||r<=val[x][1]-val[x][0]+1)val[x]={i-j,i};
                }
            }
        }
        for(int i=0;i<size(s);i++){
            if(s[i]=='0'){
                val[0]={i,i};
                break;
            }
        }
        for(int i=0;i<size(queries);i++){
            int x=queries[i][1]^queries[i][0];
            if(auto it=val.find(x);it!=end(val))ans[i]={it->second[0],it->second[1]};
            else ans[i]={-1,-1};
        }
        return ans;
    }
};
