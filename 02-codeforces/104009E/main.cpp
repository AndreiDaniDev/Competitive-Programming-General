#include <iostream>
#include <iomanip>
#define in cin
#define out cout

#include <cmath>

using namespace std;

int n, kk; double xx;

int main(){

    in.tie(NULL); out.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tests; in>>tests;
    for(; tests > 0; tests--){
        in>>n>>kk>>xx;

        double ans = xx / (n - kk + 1);
        ans = pow(ans, 1 / double(kk));

        out<<fixed<<setprecision(8)<<ans<<"\n";
    }

    return 0;
}