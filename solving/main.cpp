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
vector<vector<ll>> adjList;
vector<ll> dsuPar, dsuSize;
vector<ll> dsuIn;

ll dsu(ll curNode){
    if(dsuPar[curNode] == curNode) return curNode;
    return dsuPar[curNode] = dsu(dsuPar[curNode]);
}

void dsuMerge(ll node1, ll node2){
    node1 = dsu(node1);
    node2 = dsu(node2);
    if(node1 == node2) return;
    if(dsuSize[node1] < dsuSize[node2]){
        swap(node1, node2);
    }
    dsuSize[node1] += dsuSize[node2];
    dsuSize[node2] = 0;
    dsuPar[node2] = node1;
}

void solve(){
    // for each component its component size * incoming edge count
    cin>>n>>m;
    adjList.resize(n);
    dsuPar.resize(n);
    dsuSize.resize(n, 1);
    dsuIn.resize(n, 0);
    for(int i = 0 ; i < n ; i++){
        dsuPar[i] = i;
    }
    for(int i = 0 ; i < m ; i++){
        ll a, b;
        cin>>a>>b;
        adjList[--a].push_back(--b);
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
