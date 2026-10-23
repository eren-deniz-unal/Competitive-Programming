#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll n, m, logN;
vector<ll> c;
vector<ll> ans;
vector<ll> diffArr;
vector<vector<ll>> adjList;
vector<vector<ll>> lcaPars;
vector<vector<ll>> lcaSums;
vector<vector<ll>> lcaIndexSums;
vector<ll> depth;

void lcaPrecompute(){
    lcaPars.resize(n, vector<ll>(logN, -1));
    lcaSums.resize(n, vector<ll>(logN, -1));
    lcaIndexSums.resize(n, vector<ll>(logN, -1));
    depth.resize(n, -1);
    queue<vector<ll>> q;
    q.push({0, -1, 0});
    while(!q.empty()){
        ll curNode = q.front()[0];
        ll curPar = q.front()[1];
        depth[curNode] = q.front()[2];
        q.pop();
        lcaPars[curNode][0] = curPar;

        for(int i = 0 ; i < adjList[curNode].size() ; i++){
            ll curNeg = adjList[curNode][i];
            if(curNeg != curPar){
                q.push({curNeg, curNode, depth[curNode] + 1});
            }
        }
    }
    for(int i = 1 ; i < n ; i++){
        lcaSums[i][0] = c[lcaPars[i][0]];
        lcaIndexSums[i][0] = c[lcaPars[i][0]];
    }
    for(int j = 1 ; j < logN ; j++){
        for(int i = 1 ; i < n ; i++){
            if((1<<j) > depth[i]) continue;
            lcaPars[i][j] = lcaPars[lcaPars[i][j-1]][j-1];
            lcaSums[i][j] = lcaSums[lcaPars[i][j-1]][j-1] + lcaSums[i][j-1];
            lcaIndexSums[i][j] = lcaIndexSums[i][j-1] + (lcaIndexSums[lcaPars[i][j-1]][j-1] * (1<<j));
        }
    }
}

void solve(){
    cin>>n>>m;
    c.resize(n);
    diffArr.resize(n, 0);
    adjList.resize(n);
    ans.resize(n, 0);
    logN = log2(n) + 1;
    for(int i = 0 ; i < n ; i++){
        cin>>c[i];
    }
    for(int i = 0 ; i < n - 1 ; i++){
        ll a, b;
        cin>>a>>b;
        adjList[--a].push_back(--b);
        adjList[b].push_back(a);
    }
    lcaPrecompute();
    for(int i = 0 ; i < m ; i++){
        vector<ll> test;
        ll startNode, startMoney;
        cin>>startNode>>startMoney;
        ll curNode = --startNode, usedMoney = c[startNode], curPow = 1;
        if(usedMoney > startMoney){
            ans[startNode] += startMoney;
            continue;
        }
        for(int j = logN - 1 ; j >= 0 ; j--){
            if(lcaPars[curNode][j] == -1) continue;
            if(usedMoney + ((curPow * lcaSums[curNode][j]) + lcaIndexSums[curNode][j]) <= startMoney){
                usedMoney += ((curPow * lcaSums[curNode][j]) + lcaIndexSums[curNode][j]);
                curNode = lcaPars[curNode][j];
                curPow += (1<<j);
                test.push_back(j);
            }
        }
        diffArr[startNode]++;
        if(lcaPars[curNode][0] != -1) diffArr[lcaPars[curNode][0]]--;
        ans[startNode] += startMoney - usedMoney;
    }
    //use bottom up dfs to reconstruct any given money to cities
    for(int i = 0 ; i < n ; i++){
        cout<<ans[i]<<endl;
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
