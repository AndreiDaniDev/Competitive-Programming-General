#include <vector>

#include <iostream>
#include <cassert>

#include <bitset>

using namespace std;

const int nmax = 4e5, max32_t = (1 << 30);  
bitset <nmax + 2> dp;

vector <bool> increasing_split(vector<int> a){
    int n = a.size();
    
    vector <bool> ans(n + 1, 0);

    vector <int> pos, isprefmax(n);
    for(int i = 0, maxx = -max32_t; i < n; i++){
        if(a[i] > maxx){
            pos.push_back(i);
            maxx = a[i];
            isprefmax[i] = 1;
        }
    }

    pos.push_back(n); /// last value

    for(int i = 0, lastt = -max32_t; i < pos.size() - 1; i++){
        int isincreasing = 1;
        for(int j = pos[i] + 1; j < pos[i + 1]; j++){
            isincreasing &= (lastt < a[j]);
            lastt = a[j];
        }

        if(!isincreasing){ /// no solution :) ///
            return ans; /// a[i] >= a[j] >= a[k] with i < j < k
        }
    }

    /// helper function ///
    auto myabs = [](int xx){ return ((xx < 0) ? -xx : xx); };

    /// we have a solution :) ///
    int offset = 0; vector <int> freq(n + 2, 0);
    
    int p1 = pos.size() - 1, cntprefmax = 0, sz = 0;
    for(int i = n - 1, suffmin = +max32_t; i >= 0; i--){
        for(; p1 >= 0 && pos[p1] > i; p1--); /// keep prefix max 
        
        if(a[pos[p1]] < suffmin){
            offset += min(cntprefmax, sz - cntprefmax);
            freq[myabs(2 * cntprefmax - sz)]++;

            cntprefmax = 0, sz = 0;
        }

        cntprefmax += isprefmax[i]; sz++;
        suffmin = min(suffmin, a[i]);
    }

    /// final segment :) ///
    offset += min(cntprefmax, sz - cntprefmax);
    freq[myabs(2 * cntprefmax - sz)]++;

    dp.reset();

    dp[offset] = 1;
    for(int val = 1; val <= n; val++){
        for(int oo = 1; freq[val] > 0; oo *= 2){
            int cnt = min(oo, freq[val]); freq[val] -= cnt;
            dp |= (dp << (val * cnt));
        }
    }

    /// ans[*] == ans[n - *] ///
    for(int i = 0; i <= n; i++){
        ans[i] = dp[i];
    }

    for(int st = 0, dr = n; st <= dr; st++, dr--){
        ans[st] = (ans[st] | ans[dr]);
        ans[dr] = (ans[st] | ans[dr]);
    }

    return ans;
};