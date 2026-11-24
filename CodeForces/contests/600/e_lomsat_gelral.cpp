#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngNum(ll l, ll r){ return uniform_int_distribution<ll>(l, r)(rng); }

ll n;
vector<vector<ll>> adjList;
vector<ll> colors;
vector<ll> ans;
vector<map<ll, ll>> allMaps;

array<ll, 2> dfs(ll curNode, ll curPar){
    map<ll, ll>& myMap = allMaps[curNode];
    myMap[colors[curNode]] = 1;
    ll myMaxCount = 1;
    ll myMaxSum = colors[curNode];

    for(int i = 0 ; i < adjList[curNode].size() ; i++){
        ll curNeg = adjList[curNode][i];
        if(curNeg == curPar) continue;
        auto curNegRet = dfs(curNeg, curNode);
        map<ll, ll>& curNegMap = allMaps[curNeg];
        ll curNegMaxCount = curNegRet[0];
        ll curNegMaxSum = curNegRet[1];
        if(myMap.size() < curNegMap.size()){
            swap(curNegMap, myMap);
            myMaxCount = curNegMaxCount;
            myMaxSum = curNegMaxSum;
        }

        for(auto it : curNegMap){
            myMap[it.first] += it.second;
            if(myMap[it.first] > myMaxCount){
                myMaxCount = myMap[it.first];
                myMaxSum = it.first;
            }
            else if(myMap[it.first] == myMaxCount){
                myMaxSum += it.first;
            }
        }
    }
    
    ans[curNode] = myMaxSum;
    return {myMaxCount, myMaxSum};
}

void solve(){
    cin>>n;
    colors.resize(n);
    ans.resize(n);
    adjList.resize(n);
    allMaps.resize(n);
    for(int i = 0 ; i < n ; i++){
        cin>>colors[i];
    }
    for(int i = 0 ; i < n-1 ; i++){
        ll a, b;
        cin>>a>>b;
        adjList[--a].push_back(--b);
        adjList[b].push_back(a);
    }
    dfs(0, 0);
    for(int i = 0 ; i < n ; i++){
        cout<<ans[i]<<" ";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<fixed<<setprecision(10); // set cout to print up to 10 digits of precision

    if(fopen("name.in", "r")){
        freopen("name.in", "r", stdin);
        freopen("name.out", "w", stdout);
    } //for usaco site

    ll testCaseCount = 1;
    //cin>>testCaseCount; //for test cases

    while(testCaseCount--) solve();
    return 0;
}
