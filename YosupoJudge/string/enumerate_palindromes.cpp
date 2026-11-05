#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll n;

struct doubleHash{
    static inline ll mod1 = 1000000007, mod2 = mod1+2;
    static inline ll base1 = 31, base2 = 223;
    static inline vector<ll> pows1, pows2;

    static void initialize(ll hashN){
        pows1.assign(hashN+1, 1);
        pows2.assign(hashN+1, 1);
        for(int i = 1 ; i < hashN+1 ; i++){
            pows1[i] = (pows1[i-1] * base1) % mod1;
            pows2[i] = (pows2[i-1] * base2) % mod2;
        }
    }

    vector<ll> preHash1, preHash2;

    doubleHash(const string& s){
        preHash1.assign(s.size()+1, 0);
        preHash2.assign(s.size()+1, 0);
        for(int i = 1 ; i <= s.size() ; i++){
            preHash1[i] = (preHash1[i-1] * base1 + (s[i-1]-'a'+1)) % mod1;
            preHash2[i] = (preHash2[i-1] * base2 + (s[i-1]-'a'+1)) % mod2;
        }
    }

    pair<ll, ll> get(ll l, ll r) const{
        ll rangeSize = r - l + 1;
        if(l < 0 || r >= n) return{-1, -1};
        ll hash1 = ((preHash1[r+1] - preHash1[l] * pows1[rangeSize]) % mod1 + mod1) % mod1;
        ll hash2 = ((preHash2[r+1] - preHash2[l] * pows2[rangeSize]) % mod2 + mod2) % mod2;
        return {hash1, hash2};
    }
};

void solve(){
    string s;
    cin>>s;
    n = s.size();
    string revS(s.rbegin(), s.rend());
    doubleHash::initialize(n);
    doubleHash s_hash(s), revS_hash(revS);
    vector<ll> ans(2*n-1);
    for(ll index = 0 ; index < 2*n-1 ; index++){
        ll l = 0, r = n-1;
        while(l < r){
            ll mid = (l+r+1)/2;
            ll up, down;
            if(index % 2 == 0) up = (index/2) + mid, down = (index/2) - mid;
            else up = (index/2) + mid, down = (index/2) - mid + 1;

            if(down >= 0 && up < n && s_hash.get(down, up) == revS_hash.get(n-1 - up, n-1 - down)){
                l = mid;
            }
            else{
                r = mid-1;
            }
        }
        if(index % 2 == 0) ans[index] = 2*l+1;
        else ans[index] = 2*l;
    }
    for(int i = 0 ; i < 2*n-1 ; i++){
        cout<<ans[i]<<" ";
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
