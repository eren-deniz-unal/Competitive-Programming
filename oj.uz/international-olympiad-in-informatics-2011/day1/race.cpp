#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngNum(ll l, ll r){ return uniform_int_distribution<ll>(l, r)(rng); }

ll n, k, ans = LLMAX;
vector<pair<ll, ll>> edgeList;
vector<vector<pair<ll, ll>>> adjList;
vector<pair<set<pair<ll, ll>>, pair<ll, ll>>> sets; //{set{edge val, edge count}, {lazy val inc, lazy count inc}}

void dfs(ll curNode, ll curPar, ll curWeight){
    set<pair<ll, ll>>& mySet = sets[curNode].first;
    ll& myLazyVal = sets[curNode].second.first;
    ll& myLazyCount = sets[curNode].second.second;
    mySet.insert({0, 0});

    for(int i = 0 ; i < adjList[curNode].size() ; i++){
        ll curNeg = adjList[curNode][i].first;
        ll curNegWeight = adjList[curNode][i].second;
        if(curNeg == curPar) continue;
        dfs(curNeg, curNode, curNegWeight);
        set<pair<ll, ll>>& negSet = sets[curNeg].first;
        ll& negLazyVal = sets[curNeg].second.first;
        ll& negLazyCount = sets[curNeg].second.second;

        if(mySet.size() < negSet.size()){
            swap(mySet, negSet);
            swap(myLazyCount, negLazyCount);
            swap(myLazyVal, negLazyVal);
        }
        for(auto it : negSet){
            ll itLocTarget = k - (it.first + negLazyVal + myLazyVal);
            auto itLoc = mySet.lower_bound({itLocTarget, LLMIN});
            if(itLoc != mySet.end() && itLoc->first == itLocTarget){
                ans = min(ans, it.second + itLoc->second + negLazyCount + myLazyCount);
            }
        }
        for(auto it : negSet){
            mySet.insert({it.first + negLazyVal - myLazyVal, it.second + negLazyCount - myLazyCount});
        }
        negSet.clear();
    }
    myLazyVal += curWeight;
    myLazyCount++;
}

int best_path(int fn, int fk, int h[][2], int* l){
    n = fn;
    k = fk;
    sets.resize(n);
    adjList.resize(n);
    for(int i = 0 ; i < n-1 ; i++){
        ll a = h[i][0], b = h[i][1];
        cin>>a>>b;
        edgeList.push_back({a, b});
    }
    for(int i = 0 ; i < n-1 ; i++){
        ll a = l[i];
        adjList[edgeList[i].first].push_back({edgeList[i].second, a});
        adjList[edgeList[i].second].push_back({edgeList[i].first, a});
    }
    dfs(0, 0, 0);
    if(ans != LLMAX) return ans;
    else return -1;
}
