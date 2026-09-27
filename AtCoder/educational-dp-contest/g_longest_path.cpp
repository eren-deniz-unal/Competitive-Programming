#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN

void solve(){
    ll n, m;
    cin>>n>>m;
    vector<vector<ll>> adjList(n);
    vector<vector<ll>> adjListRev(n);
    ll outDeg[n];
    for(int i = 0 ; i < n ; i++){
        outDeg[i] = 0;
    }

    for(int i = 0 ; i < m ; i++){
        ll a, b;
        cin>>a>>b;
        adjList[--a].push_back(--b);
        adjListRev[b].push_back(a);
        outDeg[a]++;
    }

    //bfs from the ends of any paths
    queue<pair<ll, ll>> q;
    for(int i = 0 ; i < n ; i++){
        if(outDeg[i] == 0) q.push({i, 0});
    }
    ll ans = 0;
    while(!q.empty()){
        ll curNode = q.front().first;
        ll curLenght = q.front().second;
        ans = max(ans, curLenght);
        q.pop();

        for(int i = 0 ; i < adjListRev[curNode].size() ; i++){
            ll nextNode = adjListRev[curNode][i];
            outDeg[nextNode]--;
            if(outDeg[nextNode] == 0) q.push({nextNode, curLenght + 1});
        }
    }

    cout<<ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}