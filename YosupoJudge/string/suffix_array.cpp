#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll n, logN;

void solve(){
    string s;
    cin>>s;
    n = s.size();
    logN = log2(n)+1;
    vector<ll> sufArr(n);
    vector<ll> rankArr(n);
    for(int i = 0 ; i < n ; i++){
        rankArr[i] = s[i]-'a'+1;
    }
    for(int i = 0 ; i < logN ; i++){
        vector<array<ll, 3>> sufArrPaired(n);
        for(int j = 0 ; j < n ; j++){
            sufArrPaired[j] = {rankArr[j], (1<<i)+j < n ? rankArr[j + (1<<i)] : -1, j};
        }
        sort(sufArrPaired.begin(), sufArrPaired.end());
        ll curRank = 0;
        rankArr[sufArrPaired[0][2]] = curRank;
        for(int j = 1 ; j < n ; j++){
            if(sufArrPaired[j][0] != sufArrPaired[j-1][0] || sufArrPaired[j][1] != sufArrPaired[j-1][1]) curRank++;
            rankArr[sufArrPaired[j][2]] = curRank;
        }
    }
    for(int i = 0 ; i < n ; i++){
        sufArr[rankArr[i]] = i;
    }
    for(int i = 0 ; i < n ; i++){
        cout<<sufArr[i]<<" ";
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
