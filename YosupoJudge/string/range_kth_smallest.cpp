#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngNum(ll l, ll r){ return uniform_int_distribution<ll>(l, r)(rng); }

ll n, q;
vector<ll> arr;
vector<ll> roots;
vector<ll> nodeLeft;
vector<ll> nodeRight;
vector<ll> nodeVal;
map<ll, ll> realToCompress;
vector<ll> compressToReal;

ll new_node(){
    nodeLeft.emplace_back();
    nodeRight.emplace_back();
    nodeVal.emplace_back();
    return nodeLeft.size() - 1;
}

void createSegTree(){
    queue<array<ll, 3>> que; //{left, right, curNode}
    roots.push_back(new_node());
    que.push({0, n-1, roots[0]});
    while(!que.empty()){
        ll curL = que.front()[0];
        ll curR = que.front()[1];
        ll curNode = que.front()[2];
        que.pop();
        
        nodeVal[curNode] = 0;
        if(curL != curR){
            nodeLeft[curNode] = new_node();
            nodeRight[curNode] = new_node();
            ll curMid = (curL + curR) / 2;
            que.push({curL, curMid, nodeLeft[curNode]});
            que.push({curMid + 1, curR, nodeRight[curNode]});
        }
    }
    for(int i = 0 ; i < n ; i++){
        ll curRoot = new_node();
        ll target = realToCompress[arr[i]];
        ll prevTreeNode = roots[roots.size()-1];
        que.push({0, n-1, curRoot});
        while(!que.empty()){
            ll curL = que.front()[0];
            ll curR = que.front()[1];
            ll curNode = que.front()[2];
            que.pop();

            nodeVal[curNode] = nodeVal[prevTreeNode] + 1;
            if(curL != curR){
                ll curMid = (curL + curR) / 2;
                if(curMid >= target){
                    //go left
                    nodeRight[curNode] = nodeRight[prevTreeNode];
                    nodeLeft[curNode] = new_node();
                    prevTreeNode = nodeLeft[prevTreeNode];
                    que.push({curL, curMid, nodeLeft[curNode]});
                }
                else{
                    //go right
                    nodeLeft[curNode] = nodeLeft[prevTreeNode];
                    nodeRight[curNode] = new_node();
                    prevTreeNode = nodeRight[prevTreeNode];
                    que.push({curMid + 1, curR, nodeRight[curNode]});
                }
            }
        }
        roots.push_back(curRoot);
    }
}

void solve(){
    cin>>n>>q;
    arr.resize(n);
    for(int i = 0 ; i < n ; i++){
        cin>>arr[i];
    }
    vector<ll> sortedArr = arr;
    sort(sortedArr.begin(), sortedArr.end());
    compressToReal.resize(n);
    for(int i = 0 ; i < n ; i++){
        realToCompress[sortedArr[i]] = i;
        compressToReal[i] = sortedArr[i];
    }
    createSegTree();
    for(int i = 0 ; i < q ; i++){
        ll l, r, k;
        cin>>l>>r>>k;
        k++;
        ll treeL = 0, treeR = n-1;
        ll tree1 = roots[l], tree2 = roots[r];
        while(treeL < treeR){
            if(nodeVal[nodeLeft[tree2]] - nodeVal[nodeLeft[tree1]] >= k){
                tree1 = nodeLeft[tree1];
                tree2 = nodeLeft[tree2];
                treeR = (treeL + treeR) / 2;
            }
            else{
                k -= nodeVal[nodeLeft[tree2]] - nodeVal[nodeLeft[tree1]];
                tree1 = nodeRight[tree1];
                tree2 = nodeRight[tree2];
                treeL = (treeL + treeR) / 2 + 1;
            }
        }
        cout<<compressToReal[treeL]<<endl;
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
