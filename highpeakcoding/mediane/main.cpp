#include <fstream>

using namespace std;

ifstream in("mediane.in");
ofstream out("mediane.out");

const int nmax = 250000;
int task, n, partitions, kk, a[nmax + 2];

int check(int xx, int cnt){
    return (cnt <= xx) && (xx & 1) == (cnt & 1);
}

int main(){

    in>>task>>n>>partitions>>kk;
    for(int i = 1; i <= n; i++) in>>a[i]; /// it is sorted 

    if(task == 1){
        int64_t ways = 0;
        for(int i = 1; i <= n; i++){
            if(a[i] != kk){ continue; }
            ways += min(i, n - i + 1);
        }
        out<<ways<<"\n";
    }else if(task == 2){
        if(partitions == 1){
            out<<((a[(n + 1) >> 1] == kk) ? n : -1)<<"\n";
            return 0;
        }; 

        for(int i = 1; i <= n; i++){
            if(a[i] != kk){ continue; }

            /// the leftt side is odd and the right side is also odd ///
            
            if(check(i - 1, partitions >> 1) && check(n - i, partitions >> 1)){
                
                int xx, yy;
                for(xx = i - 1, yy = partitions >> 1; xx > 0 && yy > 1; xx--, yy--){
                    out<<1<<" ";
                }; out<<xx<<" "<<1<<" ";
                for(xx = n - i, yy = partitions >> 1; xx > 0 && yy > 1; xx--, yy--){
                    out<<1<<" ";
                }; out<<xx<<"\n";
                
                return 0;   
            }
        }

        for(int i = 2; i <= n - 1; i++){
            if(a[i] != kk){ continue; }

            /// the leftt side is odd and the right side is also odd ///
            
            if(check(i - 2, partitions >> 1) && check(n - i - 1, partitions >> 1)){
                
                int xx, yy;
                for(xx = i - 2, yy = partitions >> 1; xx > 0 && yy > 1; xx--, yy--){
                    out<<1<<" ";
                }; out<<xx<<" "<<3<<" ";
                for(xx = n - i - 1, yy = partitions >> 1; xx > 0 && yy > 1; xx--, yy--){
                    out<<1<<" ";
                }; out<<xx<<"\n";
                
                return 0;   
            }
        }

        out<<"-1\n"; /// doesn't exist  
    }

    return 0;
}