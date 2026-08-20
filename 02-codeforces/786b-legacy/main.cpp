#include <iostream>
#define in cin
#define out cout

#include <vector>

#include <utility>
#define x first
#define y second

#include <queue>
#include <set>
#include <bitset>

using namespace std;

typedef pair <int, int> pii;
const int nmax = 1e5;
int n, m, starternode;
int typee, xx, leftt, rightt, ww;

/// segment tree with all ranges for O(q log n) edges in total ///
/// we designate a node for entering edges and one for exiting edges ///

/// node is of type : {propagate up / propagate down (only one of these two)}
int64_t mindistt[8 * nmax + 2];

int nodes, whatleaf[nmax + 2];
int propagup[4 * nmax + 2];
int propagdown[4 * nmax + 2];

vector <pii> edges[8 * nmax + 2];

void build(int node, int st, int dr){
    propagup[node] = (++nodes); mindistt[nodes] = (1ll << 60);
    propagdown[node] = (++nodes); mindistt[nodes] = (1ll << 60);
    
    /// super simple because if i can propagate up i can't propagate down no more ///
    edges[propagdown[node]].push_back(make_pair(propagup[node], 0));

    if(st != dr){
        int mij = (st + dr) >> 1;
        build((node << 1), st, mij);
        build((node << 1) | 1, mij + 1, dr);

        /// propagate downwards to all children ///
        edges[propagdown[node]].push_back(make_pair(propagdown[(node << 1)], 0));
        edges[propagdown[node]].push_back(make_pair(propagdown[(node << 1) | 1], 0));

        edges[propagup[(node << 1)]].push_back(make_pair(propagup[node], 0));
        edges[propagup[(node << 1) | 1]].push_back(make_pair(propagup[node], 0));
    }else{ whatleaf[st] = node; }

    return;
}

void addedges(int node, int st, int dr, int leftt, int rightt, int xx, int ww, int typee){
    if(leftt <= st && dr <= rightt){
        if(typee == 2){ 
            edges[propagdown[xx]].push_back(make_pair(propagdown[node], ww)); 
            edges[propagup[xx]].push_back(make_pair(propagdown[node], ww)); 
        }
        if(typee == 3){ 
            edges[propagdown[node]].push_back(make_pair(propagdown[xx], ww)); 
            edges[propagup[node]].push_back(make_pair(propagdown[xx], ww)); 
        }
    }else{
        int mij = (st + dr) >> 1;
        if(leftt <= mij) addedges((node << 1), st, mij, leftt, rightt, xx, ww, typee);
        if(mij < rightt) addedges((node << 1) | 1, mij + 1, dr, leftt, rightt, xx, ww, typee);
    }; return;
}

int main(){

    in.tie(NULL); out.tie(NULL);
    ios_base::sync_with_stdio(false);

    in>>n>>m>>starternode; 
    
    /// initialize tree ///
    build(1, 1, n);

    /// initialize edges ///
    for(int i = 1; i <= m; i++){
        in>>typee>>xx; 
        if(typee == 1){ 
            in>>leftt>>ww; typee = 2; rightt = leftt;
        }else if(typee == 2 || typee == 3){ 
            in>>leftt>>rightt>>ww;
        }

        /// add segment tree like edges - O(q log n) edges in total :) ///
        addedges(1, 1, n, leftt, rightt, whatleaf[xx], ww, typee);
    }

    /// super simple dijkstra's algorithm ///
    priority_queue <pair <int64_t, int>, vector <pair <int64_t, int>>, greater <pair <int64_t, int>>> pq;
    
    /// big ahh initialization ///
    pq.push(make_pair(0, propagdown[whatleaf[starternode]])); 
    mindistt[propagdown[whatleaf[starternode]]] = 0;

    for(; !pq.empty(); ){
        auto [costt, node] = pq.top(); pq.pop();
        
        /// was already improved ///
        if(mindistt[node] < costt){ continue; }
    
        /// check neighbours ///
        for(auto &[nxt, weight] : edges[node]){
            if(mindistt[nxt] > costt + weight){
                mindistt[nxt] = costt + weight;
                pq.push(make_pair(mindistt[nxt], nxt));
            }
        }
    }

    /// output all distances ///
    for(int node = 1; node <= n; node++){
        int64_t smth = mindistt[propagdown[whatleaf[node]]];
        out<<((smth == (1ll << 60)) ? -1 : smth)<<" ";
    }

    return 0;
}