#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngNum(ll l, ll r){ return uniform_int_distribution<ll>(l, r)(rng); }

string s;
ll n, q;
vector<ll> segTreeLetters;
vector<ll> segTreePalindromes;
#define add_no_mod 0
#define add_with_mod 1
#define set_no_mod 2
#define range_type 3
#define point_type 4

void segTreeUpdate(vector<ll>& segTree, ll segTreeN, ll tarL, ll tarR, ll tarVal, ll op, ll type){
    stack<array<ll, 3>> stk;
    stk.push({1, 0, segTreeN - 1});
    while(!stk.empty()){
        ll curIndex = stk.top()[0];
        ll curL = stk.top()[1];
        ll curR = stk.top()[2];
        stk.pop();

        if(curL > tarR || curR < tarL) continue;
        if(type == point_type || (type == range_type && curL >= tarL && curR <= tarR)){
            if(op == add_no_mod) segTree[curIndex] += tarVal;
            if(op == add_with_mod) (segTree[curIndex] += tarVal) %= 26;
            if(op == set_no_mod) segTree[curIndex] = tarVal;
        }
        if(curL >= tarL && curR <= tarR) continue;

        ll curMid = (curL + curR) / 2;
        stk.push({curIndex*2, curL, curMid});
        stk.push({curIndex*2 + 1, curMid + 1, curR});
    }
}

ll segTreeQuery(vector<ll>& segTree, ll segTreeN, ll tarL, ll tarR, ll type){
    ll curVal = 0;
    stack<array<ll, 3>> stk;
    stk.push({1, 0, segTreeN - 1});
    while(!stk.empty()){
        ll curIndex = stk.top()[0];
        ll curL = stk.top()[1];
        ll curR = stk.top()[2];
        stk.pop();

        if(curL > tarR || curR < tarL) continue;
        if(curL >= tarL && curR <= tarR){
            curVal += segTree[curIndex];
            continue;
        }
        if(type == point_type){
            curVal += segTree[curIndex];
        }

        ll curMid = (curL + curR) / 2;
        stk.push({curIndex*2, curL, curMid});
        stk.push({curIndex*2 + 1, curMid + 1, curR});
    }
    return curVal;
}

void checkAndUpdateSmallPalindrome(ll l, ll r){
    if(l < 0 || r >= n) return;
    ll palinIndex = 2*l + (r - l - 1);  
    ll char1 = segTreeQuery(segTreeLetters, n, l, l, point_type);
    ll char2 = segTreeQuery(segTreeLetters, n, r, r, point_type);
    ll curPalindromeChange = ((char1 % 26) == (char2 % 26)) - segTreeQuery(segTreePalindromes, 2*n-1, palinIndex, palinIndex, range_type);
    segTreeUpdate(segTreePalindromes, 2*n-1, palinIndex, palinIndex, curPalindromeChange, add_no_mod, point_type);
}

void solve(){
    //found the theory in 20-25ish minutes, writing the code took 2-3 hours
    cin>>n>>q>>s;
    segTreeLetters.assign(n*4, 0);
    segTreePalindromes.assign(n*8, 0);
    for(int i = 0 ; i < n ; i++){
        segTreeUpdate(segTreeLetters, n, i, i, (s[i]-'a'), set_no_mod, range_type);
    }
    for(int i = 0 ; i < 2*n - 1 ; i++){
        if(i % 2 == 0) segTreeUpdate(segTreePalindromes, 2*n-1, i, i, (s[i/2] == s[i/2+1]), add_no_mod, point_type);
        else segTreeUpdate(segTreePalindromes, 2*n-1, i, i, (s[i/2] == s[i/2+2]), add_no_mod, point_type);
    }
    while(q--){
        ll op, l, r, x;
        cin>>op>>l>>r;
        l--; r--;
        if(op == 1) cin>>x;

        if(op == 1){
            segTreeUpdate(segTreeLetters, n, l, r, x, add_with_mod, range_type);

            checkAndUpdateSmallPalindrome(l-1, l);
            checkAndUpdateSmallPalindrome(l-2, l);
            checkAndUpdateSmallPalindrome(l-1, l+1);

            checkAndUpdateSmallPalindrome(r, r+1);
            checkAndUpdateSmallPalindrome(r, r+2);
            checkAndUpdateSmallPalindrome(r-1, r+1);
        }
        else{
            if(l < r && segTreeQuery(segTreePalindromes, 2*n-1, 2*l, 2*r-2, range_type) > 0){
                cout<<"NO"<<endl;
            }
            else{
                cout<<"YES"<<endl;
            }
        }
    }
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
