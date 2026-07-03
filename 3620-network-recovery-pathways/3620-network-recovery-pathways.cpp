class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
                int n = online.size();

        vector<vector<pair<int,int>>> adj(n);
        vector<int> indegree(n,0);

        int mx = 0;

        for(auto &e:edges){
            adj[e[0]].push_back({e[1],e[2]});
            indegree[e[1]]++;
            mx=max(mx,e[2]);
        }

        vector<int> topo;
        queue<int> q;

        for(int i=0;i<n;i++)
            if(indegree[i]==0)
                q.push(i);

        while(!q.empty()){
            int u=q.front();
            q.pop();
            topo.push_back(u);

            for(auto &it:adj[u]){
                if(--indegree[it.first]==0)
                    q.push(it.first);
            }
        }
auto check = [&](int lim){

            const long long INF = 1e18;

            vector<long long> dp(n,INF);
            dp[0]=0;

            for(int u:topo){

                if(dp[u]==INF) continue;

                for(auto &[v,c]:adj[u]){

                    if(c<lim) continue;

                    if(v!=n-1 && !online[v]) continue;

                    dp[v]=min(dp[v],dp[u]+c);
                }
            }

            return dp[n-1]<=k;
        };

        int lo=0,hi=mx;
        int ans=-1;

        while(lo<=hi){

            int mid=(lo+hi)/2;

            if(check(mid)){
                ans=mid;
                lo=mid+1;
            }
            else
                hi=mid-1;
        }

        return ans;
    }
};