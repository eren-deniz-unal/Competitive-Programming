#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngNum(ll l, ll r){ return uniform_int_distribution<ll>(l, r)(rng); }
ll rngOddNum(ll l, ll r){ ll val = uniform_int_distribution<ll>(l, r)(rng); if(val%2 == 0) val++; if(val > r) val = l + (l%2 == 0); return val; }

struct doubleHash{
    static inline ll mod1 = 1000000007, mod2 = mod1+2;
    static inline ll base1 = rngOddNum(131, mod1 - 10), base2 = rngOddNum(131, mod2 - 10);
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
        if(l < 0 || r >= preHash1.size()-1 || l > r) return{-1, -1};
        ll hash1 = ((preHash1[r+1] - preHash1[l] * pows1[rangeSize]) % mod1 + mod1) % mod1;
        ll hash2 = ((preHash2[r+1] - preHash2[l] * pows2[rangeSize]) % mod2 + mod2) % mod2;
        return {hash1, hash2};
    }
};

void solve(){
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
