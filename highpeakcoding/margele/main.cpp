#include <fstream>

using namespace std;

ifstream in("margele.in");
ofstream out("margele.out");

const int nmax = 250000;
int task, n, xx, a[nmax + 2];

void solvetask1(){
    
    int maxlength = 0, length = 0;
    for(int i = 1, maxx; i <= n; ){
        length = 0; maxx = 0;
        for(int j = i; j <= n; j++){
            maxx = max(maxx, a[j]);
            if(a[j] < maxx){
                break;
            }
            length++;
        }

        if(maxx == 1) maxlength = max(maxlength, length);
        i += length;
    }

    out<<maxlength<<"\n";
    
    return;
}

void solvetask2(){

    int cuts = 0;
    for(int i = 1, j; i <= n; ){
        for(j = i; j <= n && a[i] == a[j]; j++);
        cuts++; i = j;
    }

    if(a[1] == 1 && a[n] == 0 && cuts == 2){
        out<<"1\n"; return;
    }

    out<<max(cuts - 2, 0)<<"\n";

    return;
}

int main(){

    in>>task>>n;
    for(int i = 1; i <= n; i++){
        in>>a[i]; /// mi-e lene sa fac O(1) mem
    }

    if(task == 1){ solvetask1(); return 0; }
    if(task == 2){ solvetask2(); return 0; }

    return 0;
}