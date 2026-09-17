#include <iostream>
#define in cin
#define out cout

#include <cassert>

using namespace std;

const int mod = 1e9 + 7;
int64_t n;

int addmod(int xx, int yy){
    xx += yy;
    if(xx >= mod){
        xx -= mod;
    }
    return xx;
}

const int kkmax = 2;
int auxmat[kkmax][kkmax];

struct matrix{
    int xx, yy, mat[kkmax][kkmax];

    void setdim(int _xx, int _yy){ xx = _xx; yy = _yy; };

    void multiply(const matrix &aa, const matrix &bb){

        assert(aa.yy == bb.xx);

        for(int i = 0; i < aa.xx; i++){
            for(int j = 0; j < bb.yy; j++){
                for(int pp = 0; pp < aa.yy; pp++){
                    auxmat[i][j] = addmod(auxmat[i][j], 1ll * aa.mat[i][pp] * bb.mat[pp][j] % mod);
                }
            }
        }

        xx = aa.xx; yy = bb.yy;
        for(int i = 0; i < xx; i++){
            for(int j = 0; j < yy; j++){
                mat[i][j] = auxmat[i][j];
                auxmat[i][j] = 0;
            }
        }

        return;
    }

} ans, wwbit;

int main(){

    in>>n; n--;
    
    ans.setdim(2, 1);
    ans.mat[0][0] = 1;
    ans.mat[1][0] = 1;

    wwbit.setdim(2, 2);
    wwbit.mat[0][0] = 1; wwbit.mat[0][1] = 2;
    wwbit.mat[1][0] = 1; wwbit.mat[1][1] = 4;

    for(int bit = 0; (1ll << bit) <= n; bit++){
        if(n & (1ll << bit)){
            ans.multiply(wwbit, ans);
        }
        wwbit.multiply(wwbit, wwbit);
    }

    out<<ans.mat[1][0]<<"\n";

    return 0;
}