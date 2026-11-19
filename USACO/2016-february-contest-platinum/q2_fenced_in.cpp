#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngNum(ll l, ll r){ return uniform_int_distribution<ll>(l, r)(rng); }

ll A, B, n, m, ans = 0;
vector<ll> vertWall;
vector<ll> hortWall;
vector<ll> vertDiff;
vector<ll> hortDiff;
vector<pair<ll, char>> allDiff; //{size, type (V or H)}

void solve(){
    cin>>A>>B>>n>>m;
    vertWall.resize(n+1, 0);
    hortWall.resize(m+1, 0);
    for(int i = 1 ; i <= n ; i++){
        cin>>vertWall[i];
    }
    vertWall.push_back(A);
    for(int i = 1 ; i <= m ; i++){
        cin>>hortWall[i];
    }
    hortWall.push_back(B);
    sort(vertWall.begin(), vertWall.end());
    sort(hortWall.begin(), hortWall.end());
    vertDiff.resize(n+1);
    hortDiff.resize(m+1);
    for(int i = 0 ; i < n+1 ; i++){
        vertDiff[i] = vertWall[i+1] - vertWall[i];
        allDiff.push_back({vertDiff[i], 'V'});
    }
    for(int i = 0 ; i < m+1 ; i++){
        hortDiff[i] = hortWall[i+1] - hortWall[i];
        allDiff.push_back({hortDiff[i], 'H'});
    }
    sort(allDiff.begin(), allDiff.end());

    ll hCount = 0, vCount = 0;
    for(int i = 0 ; i < n + m + 2 ; i++){
        ll m2 = m-hCount+1;
        ll n2 = n-vCount+1;
        if(vCount == 0 || hCount == 0){
            n2 = n;
            m2 = m;
        }
        ll val = allDiff[i].first;
        char type = allDiff[i].second;
        if(type == 'V'){
            ans += val * m2;
            vCount++;
        }
        else{
            ans += val * n2;
            hCount++;
        }
    }
    cout<<ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<fixed<<setprecision(10); // set cout to print up to 10 digits of precision

    if(fopen("fencedin.in", "r")){
        freopen("fencedin.in", "r", stdin);
        freopen("fencedin.out", "w", stdout);
    } //for usaco site

    ll testCaseCount = 1;
    //cin>>testCaseCount; //for test cases

    while(testCaseCount--) solve();
    return 0;
}
