class Solution {
public:
static const int maxn=1e5;
static const long long MOD=1e9+7;

vector<long long>pow10;
Solution(){
    pow10.resize(maxn+1);
    pow10[0]=1;
    for(int i=1;i<=maxn;i++)
       pow10[i]=(pow10[i-1]*10)%MOD;
}

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n=s.size();
        vector<pair<int,int>>pref(n+1);
        vector<long long>num(n+1);
        for(int i=0;i<n;i++){
            int d=s[i]-'0';
            pref[i+1].first=pref[i].first+d;
            pref[i+1].second=pref[i].second+(d>0);
            num[i+1]=(d>0)?(num[i]*10+d)%MOD:num[i];
        }
        vector<int> ans;
        ans.reserve(queries.size());
        for(vector<int>&querie:queries){
            int l=querie[0],r=querie[1]+1;
            auto [rsum,rdigit]=pref[r];
            auto [lsum,ldigit]=pref[l];
            int len=rdigit-ldigit;
        long long val=((num[r]-num[l]*pow10[len])%MOD+MOD)%MOD;
            ans.push_back((1LL*(rsum-lsum)*val)%MOD);
        }
    return ans;
    }
};