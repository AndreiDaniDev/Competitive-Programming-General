#include "increasing.h"
#include <cassert>
#include <cstdio>

int main() {
  int N;
  assert(1 == scanf("%d", &N));
  std::vector<int> A(N);
  for (int i = 0; i < N; i++) {
    assert(1 == scanf("%d", &A[i]));
  }
  fclose(stdin);

  std::vector<bool> ans = increasing_split(A);

  int sz = (int)ans.size();

  if (sz != N+1) {
    printf("WA: Returned array does not have size N+1\n");
  }
  else {
    for (int i = 0; i < sz; i++) {
        if (ans[i]) printf("1");
        else printf("0");
    }
    printf("\n");
  }

  fclose(stdout);
  return 0;
}
