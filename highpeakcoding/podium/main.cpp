#include <fstream>

using namespace std;

ifstream in("podium.in");
ofstream out("podium.out");

const int nmax = 1e5;
int task, n, xx, a[nmax + 2], aquatic[nmax + 2];

int check(int xx){
    int maxx = 0;
    for(int i = 1; i <= n; i++){
        int hh = a[i] + xx * aquatic[i];

        if(maxx >= hh){ return 0; }
        maxx = hh;
    }
    return 1;
}

int minn[nmax + 2], maxx[nmax + 2];

int leftt[nmax + 2];
int rightt[nmax + 2];

int main(){

    in>>task>>n;
    for(int i = 1; i <= n; i++) in>>a[i];
    for(int i = 1; i <= n; i++) in>>aquatic[i];

    if(task == 1){ in>>xx; out<<(check(xx) ? "DA\n" : "NU\n"); return 0; }

    xx = 0; /// no need to increase

    for(int i = 1; i <= n; i++){
        leftt[i] = (aquatic[i] ? leftt[i - 1] : i);
        if(aquatic[i]) xx = max(xx, a[leftt[i]] - a[i] + 1);
    }

    out<<(check(xx) ? xx : -1)<<"\n";

    return 0;
}