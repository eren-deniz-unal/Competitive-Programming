#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

void solve(){
    ll n, p, q;
    string s;
    cin>>n>>s>>p>>q;
    ll sqrtN = sqrt(n) + 1;
    vector<vector<ll>> queries(q);
    vector<ll> suffixes(n + 1, 0);
    vector<ll> ans(q);
    vector<ll> modFreq(p, 0);
    vector<vector<vector<ll>>> splitQueries(sqrtN);
    for(int i = 0 ; i < q ; i++){
        ll l, r;
        cin>>l>>r;
        queries[i] = {--r, --l, i};
        splitQueries[l / sqrtN].push_back(queries[i]);
    }
    if(p == 2 || p == 5){
        vector<ll> c(n+1), w(n+1);
        for(int i = 1 ; i <= n ; i++){
            bool isDivByP = (s[i-1]-'0') % p == 0;
            c[i] = c[i-1] + isDivByP;
            w[i] = w[i-1] + (isDivByP * i);
        }
        for(int i = 0 ; i < q ; i++){
            ll l = queries[i][1], r = queries[i][0];
            cout<<w[r+1] - w[l] - l * (c[r+1] - c[l])<<endl;
        }
        return;
    }
    ll curPow = 1;
    suffixes[n] = 0;
    for(int i = n-1 ; i >= 0 ; i--){
        suffixes[i] = (suffixes[i+1] + (s[i]-'0') * curPow) % p;
        (curPow *= 10) %= p;
    }
    for(int i = 0 ; i < sqrtN ; i++){
        sort(splitQueries[i].begin(), splitQueries[i].end());
    }
    ll curL = 0, curR = 0, curAns = ((s[0]-'0') % p == 0);
    modFreq[suffixes[0]]++;
    modFreq[suffixes[1]]++;
    for(int i = 0 ; i < sqrtN ; i++){
        for(int j = 0 ; j < splitQueries[i].size() ; j++){
            ll tarR = splitQueries[i][j][0];
            ll tarL = splitQueries[i][j][1];
            ll index = splitQueries[i][j][2];

            while(curL < tarL){
                modFreq[suffixes[curL]]--;
                curAns -= modFreq[suffixes[curL]];
                curL++;
            }
            while(curL > tarL){
                curL--;
                curAns += modFreq[suffixes[curL]];
                modFreq[suffixes[curL]]++;
            }

            while(curR < tarR){
                curR++;
                curAns += modFreq[suffixes[curR+1]];
                modFreq[suffixes[curR+1]]++;
            }
            while(curR > tarR){
                modFreq[suffixes[curR+1]]--;
                curAns -= modFreq[suffixes[curR+1]];
                curR--;
            }

            ans[index] = curAns;
        }
    }
    for(int i = 0 ; i < q ; i++){
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
