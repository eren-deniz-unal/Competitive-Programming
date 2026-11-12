#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngNum(ll l, ll r){ return uniform_int_distribution<ll>(l, r)(rng); }

struct node{
    ll prefix0, suffix0, prefix1, suffix1, ans0, ans1, lazy;
};

ll n, q;
string s;
vector<node> segTree;

void push(ll index, ll l, ll r){
    segTree[index].lazy %= 2;

    if(segTree[index].lazy == 1){
        swap(segTree[index].prefix0, segTree[index].prefix1);
        swap(segTree[index].suffix0, segTree[index].suffix1);
        swap(segTree[index].ans0, segTree[index].ans1);
    }
    if(l != r){
        segTree[index*2].lazy += segTree[index].lazy;
        segTree[index*2 + 1].lazy += segTree[index].lazy;
    }
    segTree[index].lazy = 0;
}

void pull(ll index, ll l, ll r, ll mid){
    segTree[index].ans0 = max(segTree[2*index].suffix0 + segTree[2*index + 1].prefix0, max(segTree[2*index].ans0, segTree[2*index + 1].ans0));
    segTree[index].ans1 = max(segTree[2*index].suffix1 + segTree[2*index + 1].prefix1, max(segTree[2*index].ans1, segTree[2*index+ 1].ans1));

    segTree[index].prefix0 = segTree[2*index].prefix0 + (segTree[2*index].prefix0 == mid - l + 1 ? segTree[2*index + 1].prefix0 : 0);
    segTree[index].prefix1 = segTree[2*index].prefix1 + (segTree[2*index].prefix1 == mid - l + 1 ? segTree[2*index + 1].prefix1 : 0);
    segTree[index].suffix0 = segTree[2*index + 1].suffix0 + (segTree[2*index + 1].suffix0 == r - mid ? segTree[2*index].suffix0 : 0);
    segTree[index].suffix1 = segTree[2*index + 1].suffix1 + (segTree[2*index + 1].suffix1 == r - mid ? segTree[2*index].suffix1 : 0);
}

void segTreeInitialize(ll curIndex, ll curL, ll curR){
    if(curL == curR){
        segTree[curIndex].ans0 = (s[curL] == '0');
        segTree[curIndex].prefix0 = s[curL] == '0';
        segTree[curIndex].suffix0 = s[curL] == '0';
        segTree[curIndex].ans1 = s[curL] == '1';
        segTree[curIndex].prefix1 = s[curL] == '1';
        segTree[curIndex].suffix1 = s[curL] == '1';
        segTree[curIndex].lazy = 0;
    }

    if(curL == curR) return;

    ll curMid = (curL + curR) / 2;
    segTreeInitialize(2*curIndex, curL, curMid);
    segTreeInitialize(2*curIndex + 1, curMid + 1, curR);
    
    pull(curIndex, curL, curR, curMid);
}

void segTreeUpdate(ll tarL, ll tarR, ll curIndex, ll curL, ll curR){
    if(curL >= tarL && curR <= tarR) segTree[curIndex].lazy++;
    push(curIndex, curL, curR);
    
    if(curL >= tarL && curR <= tarR) return;
    if(curL > tarR || curR < tarL) return;

    ll curMid = (curL + curR) / 2;
    segTreeUpdate(tarL, tarR, 2*curIndex, curL, curMid);
    segTreeUpdate(tarL, tarR, 2*curIndex + 1, curMid + 1, curR);
    
    pull(curIndex, curL, curR, curMid);
}

ll segTreeQuery(ll tarL, ll tarR, ll curIndex, ll curL, ll curR){
    push(curIndex, curL, curR);
    
    if(curL >= tarL && curR <= tarR) return segTree[curIndex].ans1;
    if(curL > tarR || curR < tarL) return -1;

    ll curMid = (curL + curR) / 2;
    ll leftAns = segTreeQuery(tarL, tarR, 2*curIndex, curL, curMid);
    ll rightAns = segTreeQuery(tarL, tarR, 2*curIndex + 1, curMid + 1, curR);

    ll suffix = min(segTree[2*curIndex].suffix1, curMid - max(curL, tarL) + 1);
    ll prefix = min(segTree[2*curIndex + 1].prefix1, min(curR, tarR) - curMid);
    if(leftAns == -1 || rightAns == -1){
        suffix = 0;
        prefix = 0;
    }

    pull(curIndex, curL, curR, curMid);
    return max(suffix + prefix, max(leftAns, rightAns));
}

void solve(){
    //took like 15 minutes for theory
    cin>>n>>q>>s;
    segTree.resize(4*n, {0, 0, 0, 0, 0, 0, 0});
    segTreeInitialize(1, 0, n-1);
    while(q--){
        ll c, l, r;
        cin>>c>>l>>r;
        l--; r--;
        if(c == 1){
            segTreeUpdate(l, r, 1, 0, n-1);
        }
        else{
            cout<<segTreeQuery(l, r, 1, 0, n-1)<<endl;
        }
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
