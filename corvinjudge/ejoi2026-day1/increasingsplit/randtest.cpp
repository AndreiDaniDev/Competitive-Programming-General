#include <iostream>
#include <random>

using namespace std;

int main(){
    int n; cin>>n;

    uniform_int_distribution <int> dist(1, 1e9);

    std::random_device rd;
    std::mt19937 g(rd());

    cout<<n<<"\n";
    for(int i = 1; i <= n; i++){
        cout<<dist(g)<<" ";
    }

    return 0;
}