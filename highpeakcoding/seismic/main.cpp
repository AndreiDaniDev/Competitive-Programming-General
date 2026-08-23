#include <fstream>

using namespace std;

ifstream in("seismic.in");
ofstream out("seismic.out");

const int nmax = 1e3;
int task, n, a[nmax + 2][nmax + 2];

int maxlength = 0;
int cnt = 0; 

int getsumm(int xx1, int yy1, int xx2, int yy2){
    return a[xx2][yy2] - a[xx1 - 1][yy2] - a[xx2][yy1 - 1] + a[xx1 - 1][yy1 - 1];
}

int getperimeter(int xx, int yy, int length){
    xx += (length >> 1); yy += (length >> 1);
    return (
        getsumm(xx - length + 1, yy - length + 1, xx, yy) -
        getsumm(xx - length + 2, yy - length + 2, xx - 1, yy - 1)
    ); 
}

int main(){

    in>>task>>n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            in>>a[i][j]; a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    for(int i = 2; i <= n - 1; i++){
        for(int j = 2; j <= n - 1; j++){
            if(getperimeter(i, j, 3) == 0 && getsumm(i - 1, j - 1, i + 1, j + 1) == 1){
                cnt++; int length = 3; 

                for(int bit = 0; min(i, j) - (length >> 1) >= 1 && max(i, j) + (length >> 1) <= n; bit ^= 1){
                    if(getperimeter(i, j, length) == bit * 4 * (length - 1)){
                        length += 2; 
                    }else{ break; }
                }

                maxlength = max(maxlength, length - 2);
            };
        }
    }

    out<<((task == 1) ? cnt : maxlength)<<"\n";

    return 0;
}