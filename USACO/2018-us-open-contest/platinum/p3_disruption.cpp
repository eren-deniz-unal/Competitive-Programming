#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngNum(ll l, ll r){ return uniform_int_distribution<ll>(l, r)(rng); }

ll n, m;
vector<vector<pair<ll, ll>>> adjList; //{neighbor, index}
vector<array<ll, 3>> bonusEdges; //{neighbor, weight}
vector<multiset<ll>> allMultisets; //weights of current edges
vector<set<ll>> allSets; //what edges are here
vector<ll> ans; //what edges are here

void dfs(ll curNode, ll curPar, ll curIndex){
    multiset<ll>& myMultiset = allMultisets[curNode];
    set<ll>& mySet = allSets[curNode];
    
    for(int i = 0 ; i < adjList[curNode].size() ; i++){
        ll curNeg = adjList[curNode][i].first;
        if(curNeg == curPar) continue;
        dfs(curNeg, curNode, adjList[curNode][i].second);
        multiset<ll>& curNegMultiset = allMultisets[curNeg];
        set<ll>& curNegSet = allSets[curNeg];

        if(mySet.size() < curNegSet.size()){
            swap(mySet, curNegSet);
            swap(myMultiset, curNegMultiset);
        }
        for(auto it : curNegSet){
            auto itLoc = mySet.find(it);
            if(itLoc == mySet.end()){
                mySet.insert(it);
                myMultiset.insert(bonusEdges[it][2]);
            }
            else{
                mySet.erase(itLoc);
                myMultiset.erase(myMultiset.find(bonusEdges[it][2])); //did not know it erased all instances
            }
        }
    }
    if(curIndex == -1) return;
    ans[curIndex] = myMultiset.empty() ? -1 : *myMultiset.begin(); //forgor -1
}

void solve(){
    cin>>n>>m;
    adjList.resize(n);
    allMultisets.resize(n);
    allSets.resize(n);
    ans.resize(n-1);
    for(int i = 0 ; i < n-1 ; i++){
        ll a, b;
        cin>>a>>b;
        adjList[--a].push_back({--b, i});
        adjList[b].push_back({a, i});
    }
    for(int i = 0 ; i < m ; i++){
        ll a, b, c;
        cin>>a>>b>>c;
        bonusEdges.push_back({--a, --b, c});
        allSets[a].insert(i);
        allMultisets[a].insert(c);
        allSets[b].insert(i);
        allMultisets[b].insert(c);
    }
    dfs(0, 0, -1);
    for(int i = 0 ; i < n-1 ; i++){
        cout<<ans[i]<<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<fixed<<setprecision(10); // set cout to print up to 10 digits of precision

    if(fopen("disrupt.in", "r")){
        freopen("disrupt.in", "r", stdin);
        freopen("disrupt.out", "w", stdout);
    } //for usaco site

    ll testCaseCount = 1;
    //cin>>testCaseCount; //for test cases

    while(testCaseCount--) solve();
    return 0;
}
