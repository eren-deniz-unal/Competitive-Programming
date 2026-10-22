#include<bits/stdc++.h>
using namespace std;

#define ll int

ll n, sqrtN;
vector<vector<ll>> adjList;
vector<ll> allAns;
vector<ll> dfsMemo;
vector<ll> dfsOrder;

void dfsPrecompute(){
    stack<pair<ll, ll>> s;//{node, par}
    dfsOrder.resize(n, -1);
    s.push({0, 0});
    ll index = 0;
    while(!s.empty()){
        ll curNode = s.top().first;
        ll curPar = s.top().second;
        s.pop();
        dfsOrder[index] = curNode;
        index++;

        for(int i = 0 ; i < adjList[curNode].size() ; i++){
            if(adjList[curNode][i] != curPar){
                s.push({adjList[curNode][i], curNode});
            }
        }
    }
    reverse(dfsOrder.begin(), dfsOrder.end());
}

ll dfs(ll dfsK){
    ll dfsAns = 0;
    vector<ll> dfsAllAns(n, -1);
    for(int i = 0 ; i < n ; i++){
        ll curNode = dfsOrder[i];
        ll curMax = 0;
        for(int i = 0 ; i < adjList[curNode].size() ; i++){
            ll curNegVal = dfsAllAns[adjList[curNode][i]];
            if(curNegVal + curMax > dfsK){
                dfsAns++;
                curMax = min(curNegVal, curMax);
            }
            else{
                curMax = max(curMax, curNegVal);
            }
        }
        dfsAllAns[curNode] = curMax + 1;
    }
    return dfsAns;
}

ll binSearch(ll target){
    ll l = sqrtN;
    ll r = n;

    while(l <= r){
        ll mid = (l+r) / 2;
        if(dfsMemo[mid] == -1) dfsMemo[mid] = dfs(mid);
        ll midAns = dfsMemo[mid];
        if(midAns >= target){
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    return l;
}

void solve(){
    cin>>n;
    adjList.resize(n);
    allAns.resize(n + 5, -1);
    dfsMemo.resize(n + 5, -1);
    ll constSqrtN = 300;
    sqrtN = (n > 3000 ? constSqrtN : sqrt(n));
    for(int i = 0 ; i < n-1 ; i++){
        ll a, b;
        cin>>a>>b;
        adjList[--a].push_back(--b);
        adjList[b].push_back(a);
    }
    dfsPrecompute();

    for(int i = 1 ; i <= sqrtN ; i++){
        allAns[i] = dfs(i);
    }
    ll indexL = sqrtN + 1;
    while(indexL <= n){
        if(dfsMemo[indexL] == -1) dfsMemo[indexL] = dfs(indexL);;
        ll indexR = binSearch(dfsMemo[indexL]);

        for(int i = indexL ; i < indexR ; i++){
            allAns[i] = dfsMemo[indexL];
        }

        indexL = indexR;
    }

    for(int i = 1 ; i <= n ; i++){
        cout<<allAns[i]<<" ";
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

// hello