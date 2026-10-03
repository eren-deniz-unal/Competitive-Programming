#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
ll const mod = (1e9) + 7;

void solve(){
    ll n;
    cin>>n;
    vector<vector<ll>> adjList(n);
    ll dp[n][2]; //dp[i][j] -> i -> node, j -> what its colored in (0 -> black, 1 -> while)

    for(int i = 0 ; i < n - 1 ; i++){
        ll a, b;
        cin>>a>>b;
        adjList[--a].push_back(--b);
        adjList[b].push_back(a);
        dp[i][0] = 1;
        dp[i][1] = 1;
    }
    dp[n - 1][0] = 1;
    dp[n - 1][1] = 1;

    queue<pair<ll, ll>> q;
    vector<pair<ll, ll>> order;
    for(int i = 0 ; i < adjList[0].size() ; i++) q.push({adjList[0][i], 0});
    while(!q.empty()){
        ll curNode = q.front().first;
        ll curPar = q.front().second;
        order.push_back(q.front());
        q.pop();

        for(int i = 0 ; i < adjList[curNode].size() ; i++){
            if(adjList[curNode][i] != curPar) q.push({adjList[curNode][i], curNode});
        }
    }

    for(int i = order.size() - 1 ; i >= 0 ; i--){
        ll curNode = order[i].first;
        ll curPar = order[i].second;
        dp[curPar][0] *= dp[curNode][1];
        dp[curPar][1] *= (dp[curNode][0] + dp[curNode][1]);
        dp[curPar][0] %= mod;
        dp[curPar][1] %= mod;
    }

    cout<<(dp[0][0] + dp[0][1]) % mod;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(numeric_limits<double>::max_digits10);

    solve();

    return 0;
}
