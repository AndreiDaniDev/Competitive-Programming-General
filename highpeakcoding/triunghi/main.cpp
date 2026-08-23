#include <fstream>

using namespace std;

ifstream in("triunghi.in");
ofstream out("triunghi.out");

int task, xx, yy, vall;

int64_t gauss(int64_t xx){
    return 1ll * xx * (xx + 1) / 2;
}

int main(){

    in>>task;
    if(task == 1){
        in>>xx>>yy;
        out<<gauss(gauss(xx + yy - 1))<<"\n";
        return 0;
    }

    if(task == 2){
        in>>xx>>yy;
        int diag = xx + yy - 1;

        int loww = gauss(diag - 1) + 1;
        out<<((diag & 1) ? loww + diag - xx : loww + diag - yy)<<"\n";;
    }

    if(task == 3){
        in>>vall;

        int diag = 0;
        for(diag = 1; gauss(diag) < vall; diag++);

        if(diag & 1){
            xx = diag; yy = 1;
            xx -= vall - (gauss(diag - 1) + 1);
            yy += vall - (gauss(diag - 1) + 1);
        }else{
            xx = 1; yy = diag;
            xx += vall - (gauss(diag - 1) + 1);
            yy -= vall - (gauss(diag - 1) + 1);    
        }

        out<<xx<<" "<<yy<<"\n";
    }

    return 0;
}