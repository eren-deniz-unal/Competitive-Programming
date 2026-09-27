#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN

void solve(){
    //got a hint from gemini => last characters match -> theyre in, last characters dont match -> one of them isnt in
    string s, t;
    cin>>s>>t;
    ll n = s.size(), m = t.size();
    s = "-" + s;
    t = "-" + t;

    vector<ll> dp[n + 1][m + 1]; //dp[i][j] => i -> last char of s, j -> last char of t, dp -> {size, where ive come from)}
    for(int i = 0 ; i <= n ; i++){
        dp[i][0] = {0};
    }
    for(int i = 1 ; i <= m ; i++){
        dp[0][i] = {0};
    }

    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            //cur chars match -> prev ans + 1
            //cur chars dont match -> ans of one of theirs last one
            if(s[i] == t[j]){
                vector<ll> temp {0, i - 1, j - 1};
                temp[0] = dp[i - 1][j - 1][0] + 1;
                dp[i][j] = temp;
            }
            else if(dp[i - 1][j][0] > dp[i][j - 1][0]){
                dp[i][j] = {dp[i - 1][j][0], i - 1, j};
            }
            else{
                dp[i][j] = {dp[i][j - 1][0], i, j - 1};
            }
        }
    }

    ll i = n, j = m;
    string ans;
    while(i > 0 && j > 0){ //construct ans (otherwise mem limit)
        if(dp[i][j][1] < i && dp[i][j][2] < j) ans += s[i]; //diagonal jump -> ive added this char
        ll tempi = i;
        i = dp[i][j][1];
        j = dp[tempi][j][2];
    }
    reverse(ans.begin(), ans.end());
    cout<<ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}