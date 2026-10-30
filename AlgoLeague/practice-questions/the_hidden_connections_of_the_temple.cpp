#include<bits/stdc++.h>
using namespace std;

#define ll int
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll n, sqrtN, compN, ans;
vector<vector<ll>> arr;
vector<ll> flatArr;
map<ll, ll> compress;
vector<ll> revCompress;
vector<vector<pair<ll, ll>>> pairedCoords; //{x, y}

queue<array<ll, 4>> q; //{x, y, group, dist}
vector<vector<ll>> vis1; //-1 means not visited
vector<vector<ll>> vis2; //-1 means not visited
vector<vector<ll>> dist1;
vector<vector<ll>> dist2;

void visitNode(ll nodeX, ll nodeY, ll curGroup, ll curDist){
    if(vis1[nodeX][nodeY] == curGroup || vis2[nodeX][nodeY] == curGroup) return;

    if(vis1[nodeX][nodeY] == -1){
        vis1[nodeX][nodeY] = curGroup;
        dist1[nodeX][nodeY] = curDist + 1;
    }
    else{
        vis2[nodeX][nodeY] = curGroup;
        dist2[nodeX][nodeY] = curDist + 1;
    }

    q.push({nodeX, nodeY, curGroup, curDist+1});
}

void solve(){
    cin>>sqrtN;
    n = sqrtN * sqrtN;
    arr.resize(sqrtN, vector<ll>(sqrtN));
    for(int i = 0 ; i < sqrtN ; i++){
        for(int j = 0 ; j < sqrtN ; j++){
            cin>>arr[i][j];
            flatArr.push_back(arr[i][j]);
        }
    }
    revCompress = flatArr;
    sort(revCompress.begin(), revCompress.end());
    revCompress.erase(unique(revCompress.begin(), revCompress.end()), revCompress.end());
    compN = revCompress.size();
    for(int i = 0 ; i < compN ; i++){
        compress[revCompress[i]] = i;
    }
    pairedCoords.resize(compN);
    for(int i = 0 ; i < sqrtN ; i++){
        for(int j = 0 ; j < sqrtN ; j++){
            pairedCoords[compress[arr[i][j]]].push_back({i, j});
        }
    }
    for(int i = 0 ; i < compN ; i++){
        if(pairedCoords[i].size() > sqrtN*3){
            ll groupsLeft = pairedCoords[i].size();
            vis1.assign(sqrtN, vector<ll>(sqrtN, -1));
            vis2.assign(sqrtN, vector<ll>(sqrtN, -1));
            dist1.assign(sqrtN, vector<ll>(sqrtN, 0));
            dist2.assign(sqrtN, vector<ll>(sqrtN, 0));
            for(int j = 0 ; j < pairedCoords[i].size() ; j++){
                q.push({pairedCoords[i][j].first, pairedCoords[i][j].second, j, 0});
                visitNode(pairedCoords[i][j].first, pairedCoords[i][j].second, j, 0);
            }
            while(!q.empty()){
                ll curX = q.front()[0];
                ll curY = q.front()[1];
                ll curGroup = q.front()[2];
                ll curDist = q.front()[3];
                q.pop();

                if(curX-1 >= 0 && (vis1[curX-1][curY] == -1 || vis2[curX-1][curY] == -1)){
                    visitNode(curX-1, curY, curGroup, curDist);
                }
                if(curX+1 < sqrtN && (vis1[curX+1][curY] == -1 || vis2[curX+1][curY] == -1)){
                    visitNode(curX+1, curY, curGroup, curDist);
                }
                if(curY-1 >= 0 && (vis1[curX][curY-1] == -1 || vis2[curX][curY-1] == -1)){
                    visitNode(curX, curY-1, curGroup, curDist);
                }
                if(curY+1 < sqrtN && (vis1[curX][curY+1] == -1 || vis2[curX][curY+1] == -1)){
                    visitNode(curX, curY+1, curGroup, curDist);
                }
            }
            
            ll curAns = 0;
            for(int j = 0 ; j < pairedCoords[i].size() ; j++){
                ll curX = pairedCoords[i][j].first;
                ll curY = pairedCoords[i][j].second;
                curAns += dist2[curX][curY];
            }
            ans += curAns;
        }
        else{
            if(pairedCoords[i].size() == 1){
                continue;
            }
            for(int j = 0 ; j < pairedCoords[i].size() ; j++){
                ll curAns = INT_MAX-100;
                for(int k = 0 ; k < pairedCoords[i].size() ; k++){
                    if(j == k) continue;
                    pair<ll, ll> coord1 = pairedCoords[i][j];
                    pair<ll, ll> coord2 = pairedCoords[i][k];
                    curAns = min(curAns, abs(coord1.first - coord2.first) + abs(coord1.second - coord2.second));
                }
                ans += curAns;
            }
        }
    }
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
