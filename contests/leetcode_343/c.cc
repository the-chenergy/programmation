#define cout 0 && cout

class Solution {
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        static priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq = {};
        auto diff = [&](int a, int b, int c, int d) -> int {
            return abs(c - a) + abs(d - b);
        };
        specialRoads.push_back({start[0], start[1], target[0], target[1], diff(start[0], start[1], target[0], target[1])});
        map<pair<int, int>, int> id;
        vector<pair<int, int>> fid;
        for (auto& sr : specialRoads) {
            if (id.insert({{sr[0], sr[1]}, (int)id.size()}).second)
                fid.push_back({sr[0], sr[1]});
            if (id.insert({{sr[2], sr[3]}, (int)id.size()}).second)
                fid.push_back({sr[2], sr[3]});
        }
        
        int n = id.size();
        static vector<map<int, int>> nei;
        nei.assign(n, {});
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                nei[j][i] = nei[i][j] = diff(fid[i].first, fid[i].second, fid[j].first, fid[j].second);
                cout << "  prep "<< i << " " << j << " " << nei[i][j] << "\n";
            }
        }
        for (int i = 0; i < specialRoads.size(); i++) {
            auto a = id[{specialRoads[i][0], specialRoads[i][1]}];
            auto b = id[{specialRoads[i][2], specialRoads[i][3]}];
            auto t = min(nei[a][b], specialRoads[i][4]);
            nei[a][b] = t;
        }
        
        static vector<long long> dist;
        dist.assign(n, LLONG_MAX / 2);
        int src = id[{start[0], start[1]}];
        dist[src] = 0;
        pq.push({0, src});
        int tar = id[{target[0], target[1]}];
        cout << src << " " << tar << "\n";
        while (pq.size()) {
            auto [d, i] = pq.top();
            pq.pop();
            if (d > dist[i]) continue;
            cout << "  " << i << " " << d << "\n";
            if (i == tar) return d;
            for (auto [j, w] : nei[i]) {
                cout << "    " << j << " " << w << "\n";
                if (d + w >= dist[j]) continue;
                dist[j] = d + w;
                cout << "    hello\n";
                pq.push({dist[j], j});
            }
        }
        throw 42;
    }
};
