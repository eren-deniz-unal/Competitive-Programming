#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll n, sqrtN;
vector<vector<ll>> adjList;
vector<ll> allAns;
vector<ll> dfsMemo;

ll dfsAns, dfsK;
ll dfs(ll curNode, ll curPar){
    ll curMax = 0;
    for(int i = 0 ; i < adjList[curNode].size() ; i++){
        ll curNeg = adjList[curNode][i];
        if(curNeg != curPar){
            ll curNegVal = dfs(curNeg, curNode);
            if(curNegVal + curMax > dfsK){
                dfsAns++;
                curMax = min(curNegVal, curMax);
            }
            else{
                curMax = max(curMax, curNegVal);
            }
        }
    }
    return curMax + 1;
}

ll callDfs(ll k){
    dfsK = k;
    dfsAns = 0;
    dfs(0, 0);
    return dfsAns;
}

ll binSearch(ll target, bool findLastInstance){
    ll l = sqrtN;
    ll r = n;

    while(l <= r){
        ll mid = (l+r) / 2;
        if(dfsMemo[mid] == -1) dfsMemo[mid] = callDfs(mid);
        ll midAns = dfsMemo[mid];
        if(midAns < target || (findLastInstance && midAns == target)){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return l;
}

void solve(){
    cin>>n;
    adjList.resize(n);
    allAns.resize(n, -1);
    dfsMemo.resize(n, -1);
    sqrtN = sqrt(n)+1;
    for(int i = 0 ; i < n-1 ; i++){
        ll a, b;
        cin>>a>>b;
        adjList[--a].push_back(--b);
        adjList[b].push_back(a);
    }

    for(int i = 1 ; i <= sqrtN ; i++){
        allAns[i] = callDfs(i);
    }
    for(int i = 0 ; i < sqrtN ; i++){
        ll leftestVal = binSearch(i, false);
        ll rightestVal = binSearch(i, true);
        for(int j = leftestVal ; j <= rightestVal ; j++){
            allAns[j] = i;
        }
    }

    for(int i = 1 ; i <= n ; i++){
        cout<<callDfs(i)<<" ";
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
