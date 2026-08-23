#include <fstream>

using namespace std;

ifstream in("flip.in");
ofstream out("flip.out");

const int nmax = 1e3;
int task, n, a[nmax + 2][nmax + 2];

int ops[nmax + 2][nmax + 2];

int main(){

    in>>task>>n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            in>>a[i][j];
        }
    }

    for(int i = n; i >= 1; i--){
        for(int j = n; j >= 1; j--){
            ops[i][j] = ops[i + 1][j] + ops[i][j + 1] - ops[i + 1][j + 1];
            ops[i][j] += (a[i][j] ^ (ops[i][j] & 1));
        }
    }

    if(task == 1){ 
        out<<((ops[1][1] == 1) ? "DA\n" : "NU\n");
    }else{ out<<ops[1][1]<<"\n"; }

    return 0;
}