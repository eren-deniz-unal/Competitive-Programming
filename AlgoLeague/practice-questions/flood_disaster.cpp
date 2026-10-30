#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll n, m, a, b, k, minHeight;

ll myVal(ll x, ll y){
    return (abs(a - x) * abs(b - y)) * (abs(a - x) * abs(b - y));
}

void solve(){
    cin>>n>>m>>a>>b>>k;
    map<pair<ll, ll>, bool> vis;
    minHeight = LLMAX;
    priority_queue<array<ll, 3>> pq; //{value, x, y}
    pq.push({myVal(n, m), n, m});
    pq.push({myVal(n, 0), n, 0});
    pq.push({myVal(0, m), 0, m});
    pq.push({myVal(0, 0), 0, 0});
    vis[{n, m}] = true;
    vis[{n, 0}] = true;
    vis[{0, m}] = true;
    vis[{0, 0}] = true;
while(!pq.empty() && k > 0){
        ll curX = pq.top()[1];
        ll curY = pq.top()[2];
        pq.pop();

        minHeight = min(minHeight, myVal(curX, curY));
        k--;

        if(curX+1 <= n && !vis[{curX+1, curY}]){
            pq.push({myVal(curX+1, curY), curX+1, curY});
            vis[{curX+1, curY}] = true;
        }
        if(curX-1 >= 0 && !vis[{curX-1, curY}]){
            pq.push({myVal(curX-1, curY), curX-1, curY});
            vis[{curX-1, curY}] = true;
        }
        if(curY+1 <= m && !vis[{curX, curY+1}]){
            pq.push({myVal(curX, curY+1), curX, curY+1});
            vis[{curX, curY+1}] = true;
        }
        if(curY-1 >= 0 && !vis[{curX, curY-1}]){
            pq.push({myVal(curX, curY-1), curX, curY-1});
            vis[{curX, curY-1}] = true;
        }
    }
    cout<<minHeight<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<fixed<<setprecision(10); // set cout to print up to 10 digits of precision
    ll testCaseCount = 1;
    cin>>testCaseCount; //for test cases

    while(testCaseCount--) solve();
    return 0;
}
