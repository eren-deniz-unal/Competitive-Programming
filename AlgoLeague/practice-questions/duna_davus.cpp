#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

vector<vector<ll>> revAdjList;
vector<vector<ll>> edgeList; //{node1, node2, weight}
vector<ll> dist;
vector<bool> pathExists;
ll n, m, k;

void bfs(ll start){
    pathExists.resize(n, false);
    queue<ll> q;
    q.push(start);
    while(!q.empty()){
        ll curNode = q.front();
        q.pop();
        pathExists[curNode] = true;

        for(int i = 0 ; i < revAdjList[curNode].size() ; i++){
            ll curNeg = revAdjList[curNode][i];
            if(!pathExists[curNeg]){
                q.push(curNeg);
            }
        }
    }
}

void solve(){
    cin>>n>>m>>k;
    revAdjList.resize(n);
    dist.resize(n);
    for(int i = 0 ; i < m ; i++){
        ll a, b, c;
        cin>>a>>b>>c;
        revAdjList[--b].push_back(--a);
        edgeList.push_back({a, b, -c});
    }
    bfs(n-1);

    for(int i = 0 ; i < n ; i++){
        dist[i] = LLMAX / 2;
    }
    dist[0] = -k;
    for(int i = 0 ; i < n-1 ; i++){
        for(auto curEdge : edgeList){
            ll node1 = curEdge[0], node2 = curEdge[1], weight = curEdge[2];
            dist[node2] = min(dist[node2], (dist[node1] + weight < 0 ? dist[node1] + weight : dist[node2]));
        }
    }
    string ans = "NO";
    for(auto curEdge : edgeList){
        ll node1 = curEdge[0], node2 = curEdge[1], weight = curEdge[2];
        if(dist[node2] != LLMAX/2 && dist[node2] > dist[node1] + weight && pathExists[node2]){
            ans = "YES";
            break;
        }
    }
    cout<<ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<fixed<<setprecision(10); // set cout to print up to 10 digits of precision
    ll testCaseCount = 1;
    //cin>>testCaseCount; //for test cases

    while(testCaseCount--) solve();
    return 0;
}
