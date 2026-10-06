#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

void solve(){
    ll n;
    string s;
    cin>>n>>s;
    ll i = 0, j = -1, ans = LLMAX;
    ll cntR = 0, cntB = 0, cntT = 0, cntO = 0;
    while(i < n && j < n){
        if(cntR >= 1 && cntB >= 1 && cntT >= 1 && cntO >= 2){
            ans = min(ans, j - i + 1);
            if(s[i] == 'R') cntR--;
            else if(s[i] == 'B') cntB--;
            else if(s[i] == 'T') cntT--;
            else cntO--;
            i++;
        }
        else{
            j++;
            if(s[j] == 'R') cntR++;
            else if(s[j] == 'B') cntB++;
            else if(s[j] == 'T') cntT++;
            else cntO++;
        }
    }
    if(ans == LLMAX) ans = -1;
    cout<<ans;
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
