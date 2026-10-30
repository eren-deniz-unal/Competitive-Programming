#include<bits/stdc++.h>
using namespace std;

#define ll int
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = 911;

vector<vector<ll>> adjList;
vector<vector<ll>> newAdjList;
vector<pair<ll, ll>> edgeList;
vector<ll> oldToNewNode;
vector<ll> dsu;
vector<ll> dsuSizes;
vector<ll> inTime;
vector<ll> minTime;
vector<bool> vis;
vector<bool> newVis;
ll n, m, newN;

ll dsuQuerry(ll node){
    if(dsu[node] == node) return node;
    return dsu[node] = dsuQuerry(dsu[node]);
}

void dsuMerge(ll node1, ll node2){
    node1 = dsuQuerry(node1);
    node2 = dsuQuerry(node2);
    if(node1 == node2) return;
    if(dsuSizes[node1] > dsuSizes[node2]) swap(node1, node2);
    dsuSizes[node2] += dsuSizes[node1];
    dsuSizes[node1] = -1;
    dsu[node1] = node2;
}

pair<ll, ll> bfs(ll startNode){ //{dist, farthest node}
    ll maxDist = 0;
    ll farthestNode = startNode;
    
    queue<array<ll, 3>> q; //{node, par, dist}
    q.push({startNode, startNode, 0});
    while(!q.empty()){
        ll curNode = q.front()[0];
        ll curPar = q.front()[1];
        ll curDist = q.front()[2];
        q.pop();
        newVis[curNode] = true;

        if(curDist > maxDist){
            maxDist = curDist;
            farthestNode = curNode;
        }

        for(int i = 0 ; i < newAdjList[curNode].size() ; i++){
            ll curNeg = newAdjList[curNode][i];
            if(curNeg != curPar){
                q.push({curNeg, curNode, curDist + 1});
            }
        }
    }

    return {maxDist, farthestNode};
}

void solve(){
    // got help while writing the dfs cycle to node reduction
    cin>>n>>m;
    adjList.resize(n);
    dsu.resize(n);
    inTime.resize(n, -1);
    minTime.resize(n, -1);
    dsuSizes.resize(n, 1);
    vis.resize(n, false);
    for(int i = 0 ; i < m ; i++){
        ll a, b;
        cin>>a>>b;
        if(a > b) swap(a, b);
        edgeList.push_back({a, b});
    }
    for(int i = 0 ; i < n ; i++){
        dsu[i] = i;
    }
    sort(edgeList.begin(), edgeList.end());
    for(int i = 0 ; i < m ; i++){
        if(i != 0 && edgeList[i] == edgeList[i-1]){
            dsuMerge(edgeList[i].first, edgeList[i].second);
        }
        else if(edgeList[i].first != edgeList[i].second){
            adjList[edgeList[i].first].push_back(edgeList[i].second);
            adjList[edgeList[i].second].push_back(edgeList[i].first);
        }
    }
    stack<array<ll, 3>> s; //{node, par, state} (state is 1 for in or 0 for out)
    for(int i = 0 ; i < n ; i++){
        if(!vis[i]){
            ll curTime = 0;
            s.push({i, i, 0});
            while(!s.empty()){
                ll curNode = s.top()[0];
                ll curPar = s.top()[1];
                bool stateIsOut = s.top()[2];
                s.pop();

                if(!stateIsOut){
                    if(vis[curNode]) continue;
                    vis[curNode] = true;

                    inTime[curNode] = curTime++;
                    minTime[curNode] = inTime[curNode];
                    s.push({curNode, curPar, true});
                    for(int j = 0 ; j < adjList[curNode].size() ; j++){
                        ll curNeg = adjList[curNode][j];
                        if(!vis[curNeg]){
                            s.push({curNeg, curNode, false});
                        }
                    }
                }
                else{
                    ll curTarget = -1;
                    for(int j = 0 ; j < adjList[curNode].size() ; j++){
                        ll curNeg = adjList[curNode][j];
                        if(curNeg == curPar) continue;
                        if(minTime[curNode] > minTime[curNeg]){
                            minTime[curNode] = minTime[curNeg];
                            curTarget = curNeg;
                        }
                    }
                    if(curTarget != -1){
                        dsuMerge(curNode, curTarget);
                    }
                }
            }
        }
    }
    newN = 0;
    oldToNewNode.resize(n, -1);
    for(int i = 0 ; i < n ; i++){
        if(dsuSizes[i] != -1){
            oldToNewNode[i] = newN++;
        }
    }
    newAdjList.resize(newN);
    for(int i = 0 ; i < m ; i++){
        ll curNode1 = dsuQuerry(edgeList[i].first), curNode2 = dsuQuerry(edgeList[i].second);
        if(curNode1 != curNode2){
            newAdjList[oldToNewNode[curNode1]].push_back(oldToNewNode[curNode2]);
            newAdjList[oldToNewNode[curNode2]].push_back(oldToNewNode[curNode1]);
        }
    }
    ll ans = 0;
    newVis.resize(newN);
    for(int i = 0 ; i < newN ; i++){
        if(!newVis[i]){
            ll targetNode = bfs(i).second;
            ans += bfs(targetNode).first + 1;
        }
    }
    ans -= 1;
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
