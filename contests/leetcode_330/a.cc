set<int>s,t;

class Solution {
public:
    int distinctIntegers(int n) {
        bool go=1;
        s={n};
        int a=1;
        while(go&&a++<=1000){
            go=0;
            t=s;
            for(int i=1;i<=n;i++){
                for(int j:s)if(j%i==1&&t.insert(i).second)go=1;
            }
            s=move(t);
            // cout<<"s: ";for(auto x:s)cout<<x<<" ";cout<<"\n";
        }
        return size(s);
    }
};
