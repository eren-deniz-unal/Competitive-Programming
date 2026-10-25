#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll n, q, m, logN;
vector<vector<pair<int, ll>>> adjList; //{neighbor, weight}
vector<int> activeNodes;
vector<int> eulerTour;
vector<int> depth;
vector<ll> distToRoot;
vector<int> firstInstance;
vector<vector<pair<int, int>>> lcaSparseTable; //{depth, node}

void lcaDfs(int curNode, int curPar){
    firstInstance[curNode] = eulerTour.size();
    eulerTour.push_back(curNode);
    depth[curNode] = depth[curPar] + 1;

    for(int i = 0 ; i < adjList[curNode].size() ; i++){
        int curNeg = adjList[curNode][i].first;
        ll curWeight = adjList[curNode][i].second;
        if(curNeg != curPar){
            distToRoot[curNeg] = distToRoot[curNode] + curWeight;
            lcaDfs(curNeg, curNode);
            eulerTour.push_back(curNode);
        }
    }
}

void lcaPrecalculate(){
    int tourSize = 2*n - 1;
    firstInstance.resize(n);
    depth.resize(n, -1);
    distToRoot.resize(n, 0);
    lcaDfs(0, 0);
    lcaSparseTable.resize(tourSize, vector<pair<int, int>>(logN+3));
    for(int i = 0 ; i < tourSize ; i++){
        lcaSparseTable[i][0] = {depth[eulerTour[i]], eulerTour[i]};
    }
    for(int j = 1 ; j < logN+3 ; j++){
        for(int i = 0 ; i + (1 << j) <= tourSize ; i++){
           lcaSparseTable[i][j] = min(lcaSparseTable[i][j-1], lcaSparseTable[i + (1 << (j-1))][j-1]);
        }
    }
}

int lcaCalculate(int node1, int node2){
    if(firstInstance[node1] < firstInstance[node2]) swap(node1, node2);
    int maxPow = __lg(firstInstance[node1] - firstInstance[node2] + 1);
    return min(lcaSparseTable[firstInstance[node2]][maxPow], lcaSparseTable[firstInstance[node1] - (1 << (maxPow)) + 1][maxPow]).second;
}

void solve(){
    cin>>n;
    adjList.resize(n);
    logN = __lg(n);
    for(int i = 0 ; i < n-1 ; i++){
        int a, b, c;
        cin>>a>>b>>c;
        adjList[--a].push_back({--b, c});
        adjList[b].push_back({a, c});
    }
    lcaPrecalculate();
    cin>>q;
    while(q--){
        cin>>m;
        activeNodes.clear();
        for(int i = 0 ; i < m ; i++){
            int a;
            cin>>a;
            activeNodes.push_back(--a);
        }
        ll ans = 0;
        ll farNode1 = activeNodes[0];
        ll farNode2 = activeNodes[0];
        for(int i = 1 ; i < m ; i++){
            int curNode = activeNodes[i];
            int curLca = lcaCalculate(farNode1, curNode);
            ll newDist1 = distToRoot[farNode1] + distToRoot[curNode] - (2*distToRoot[curLca]);
            curLca = lcaCalculate(farNode2, curNode);
            ll newDist2 = distToRoot[farNode2] + distToRoot[curNode] - (2*distToRoot[curLca]);
            if(newDist1 > newDist2){
                if(ans < newDist1){
                    farNode2 = curNode;
                    ans = newDist1;
                }
            }
            else{
                if(ans < newDist2){
                    farNode1 = curNode;
                    ans = newDist2;
                }
            }
        }
        cout<<ans<<endl;
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
