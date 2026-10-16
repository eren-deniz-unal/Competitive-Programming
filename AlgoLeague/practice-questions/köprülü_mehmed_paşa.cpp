#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll n, m, newN;
vector<vector<ll>> adjList;
vector<vector<ll>> newAdjList;
vector<ll> newNodes;
vector<ll> inTime;
vector<ll> minTime;
vector<ll> dsu;
vector<bool> vis;

ll dsuFind(ll node){
    if(dsu[node] == node) return node;
    return dsu[node] = dsuFind(dsu[node]);
}

void dsuCombine(ll node1, ll node2){
    node1 = dsuFind(node1);
    node2 = dsuFind(node2);
    dsu[node1] = node2;
}

ll curTime = 0;
void dfs(ll curNode, ll curPar){
    ll curDsuTarget = curNode;
    inTime[curNode] = ++curTime;
    minTime[curNode] = inTime[curNode];
    vis[curNode] = true;
    for(int i = 0 ; i < adjList[curNode].size() ; i++){
        ll curNeg = adjList[curNode][i];
        if(curNeg == curPar) continue;
        if(!vis[curNeg]){
            dfs(curNeg, curNode);
        }
        if(minTime[curNode] >= minTime[curNeg]){
            minTime[curNode] = minTime[curNeg];
            curDsuTarget = curNeg;
        }
    }
    dsuCombine(curNode, curDsuTarget);
}

void solve(){
    //found to search for cycles and compress them to single nodes myself
    //looked how to do search for cycles in linear time from gemini
    cin>>n>>m;
    inTime.resize(n, -1);
    minTime.resize(n, -1);
    newNodes.resize(n, -1);
    adjList.resize(n);
    vis.resize(n, false);
    dsu.resize(n);
    for(int i = 0 ; i < n ; i++){
        dsu[i] = i;
    }
    for(int i = 0 ; i < m ; i++){
        ll a, b;
        cin>>a>>b;
        adjList[--a].push_back(--b);
        adjList[b].push_back(a);
    }
    dfs(0, 0);
    newN = 0;
    for(int i = 0 ; i < n ; i++){
        if(newNodes[dsuFind(i)] == -1){
            newNodes[dsuFind(i)] = newN;
            newN++;
        }
    }
    if(newN == 1){
        cout<<0;
        return;
    }
    newAdjList.resize(newN);
    for(int curNode = 0 ; curNode < n ; curNode++){
        for(int j = 0 ; j < adjList[curNode].size() ; j++){
            ll curNeg = adjList[curNode][j];
            ll newCurNode = newNodes[dsuFind(curNode)];
            ll newCurNeg = newNodes[dsuFind(curNeg)];

            if(newCurNode != newCurNeg && find(newAdjList[newCurNode].begin(), newAdjList[newCurNode].end(), newCurNeg) == newAdjList[newCurNode].end()){
                newAdjList[newCurNode].push_back(newCurNeg);
                newAdjList[newCurNeg].push_back(newCurNode);
            }
        }
    }
    ll leafCount = 0;
    for(int i = 0 ; i < newN ; i++){
        if(newAdjList[i].size() == 1){
            leafCount++;
        }
    }
    cout<<(leafCount+1) / 2;
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
