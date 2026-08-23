#include <fstream>
#include <bitset>

using namespace std;

ifstream in("sir.in");
ofstream out("sir.out");

const int valmax = 2e5;
int task, n; bitset <valmax + 2> ciur;

int isprime(int xx){
    for(int div = 2; div * div <= xx; div++){
        if(xx % div == 0){ return 0; }
    }
    return 1;
}

int main(){

    in>>task>>n;
    if(task == 1){ out<<(isprime(n) ? "NU\n" : "DA\n"); return 0; }

    /// find the kth prime number ///
    ciur[1] = 1;
    for(int i = 2; i * i <= valmax; i++){
        if(ciur[i]){ continue; }
        for(int j = i * i; j <= valmax; j += i){
            ciur[j] = 1; /// composite number
        }
    }

    for(int i = 1; i <= valmax; i++){
        n -= ciur[i];
        if(!n){ out<<i<<"\n"; return 0; }
    }

    return 0;
}