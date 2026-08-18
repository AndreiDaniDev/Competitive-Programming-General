#include <fstream>

#include <random>

using namespace std;

ifstream in("smth.in");
ofstream out("magikruks.in");

int main(){
    int n, nrq; in>>n>>nrq;
    
    std::random_device rd;
    std::mt19937 g(rd());

    std::uniform_int_distribution<> ahh(1, 1e9);

    out<<n<<" "<<nrq<<"\n";
    for(int i = 1; i <= n; i++){
        out<<ahh(g)<<" "<<ahh(g)<<"\n";
    }
    for(int itq = 1; itq <= nrq; itq++){
        out<<"2 "<<ahh(g)<<"\n";
    }

    return 0;
}