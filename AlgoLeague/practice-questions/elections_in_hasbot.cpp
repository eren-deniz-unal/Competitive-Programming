#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll n, m, logN;
vector<vector<ll>> adjList;
vector<vector<ll>> pars;
vector<ll> depth;
vector<ll> treeDiffArr;
vector<ll> treeCountArr;
vector<ll> ans;

void lcaSetup(){
    stack<pair<ll, ll>> s;
    s.push({0, 0});
    depth[0] = 0;
    while(!s.empty()){
        ll curNode = s.top().first;
        ll curPar = s.top().second;
        s.pop();
        depth[curNode] = depth[curPar] + 1;
        pars[curNode][0] = curPar;

        for(int i = 0 ; i < adjList[curNode].size() ; i++){
            if(adjList[curNode][i] != curPar) s.push({adjList[curNode][i], curNode});
        }
    }

    for(int j = 1 ; j < logN ; j++){
        for(int i = 0 ; i < n ; i++){
            pars[i][j] = pars[pars[i][j - 1]][j - 1];
        }
    }
}

ll lca(ll node1, ll node2){
    if(depth[node1] < depth[node2]) swap(node1, node2);
    ll depthDist = depth[node1] - depth[node2];
    for(int i = 0 ; i < logN ; i++){
        if(((depthDist >> i) & 1) == 1){
            node1 = pars[node1][i];
        }
    }
    if(node1 == node2) return node1;

    for(int i = logN - 1 ; i >= 0 ; i--){
        if(pars[node1][i] != pars[node2][i]){
            node1 = pars[node1][i];
            node2 = pars[node2][i];
        }
    }
    return pars[node1][0];
}

void dfs(ll curNode, ll curPar){
    for(int i = 0 ; i < adjList[curNode].size() ; i++){
        if(adjList[curNode][i] == curPar) continue;

        dfs(adjList[curNode][i], curNode);
        treeDiffArr[curNode] += treeDiffArr[adjList[curNode][i]];
        treeCountArr[curNode] += treeCountArr[adjList[curNode][i]];
    }

    ans[curNode] = treeDiffArr[curNode] - (depth[curNode] * treeCountArr[curNode]);
}

void solve(){
    //couldnt do it and looked from gemini
    //learned what diff array on tree is
    cin>>n;
    logN = log2(n) + 1;
    adjList.resize(n);
    pars.resize(n, vector<ll>(logN, 0));
    depth.resize(n);
    treeCountArr.resize(n, 0);
    treeDiffArr.resize(n, 0);
    ans.resize(n);

    for(int i = 0 ; i < n - 1 ; i++){
        ll a, b;
        cin>>a>>b;
        adjList[--a].push_back(--b);
        adjList[b].push_back(a);
    }
    lcaSetup();

    cin>>m;
    for(int i = 0 ; i < m ; i++){
        ll start, end;
        cin>>start>>end;
        ll curLca = lca(--start, --end);

        treeCountArr[start]++;
        treeCountArr[end]--;
        treeCountArr[curLca]++;
        if(curLca != 0) treeCountArr[pars[curLca][0]]--;

        treeDiffArr[start] += depth[start] + 1;
        treeDiffArr[end] += depth[start] - 2*depth[curLca] + 1;
        treeDiffArr[curLca] -= depth[start] - 2*depth[curLca] + 1;
        if(curLca != 0) treeDiffArr[pars[curLca][0]] -= depth[start] + 1;
    }

    dfs(0, -1);
    //bottom up dfs
    //ans[curNode] = treeDiffArr[curNode] - (treeCountArr[curNode] * depth[curNode][0])

    for(int i = 0 ; i < n ; i++){
        cout<<ans[i]<<" ";
    }
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
