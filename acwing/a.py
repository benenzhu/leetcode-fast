startss = '''
#ifdef zz
#include "bits/stdc++.h"
#define newline (getline(cin,line),line)
#endif
using namespace std;
// @lc code=start
#define rep(i, j, n)    for(int i=(j);i<(n);i++)
#define per(i, n, j)    for(int i=(n)-1;i>=(j);--i)
#define sz(a)         ((int)a.size())

void print() { puts(""); }

#ifdef zz
#define dea2(a,n,m)    rep(_i, 0, n) { rep(_j, 0, m) O(a[_i][_j]); puts(""); };puts("")
#define dea(a,n)	       rep(_i,0,n)O(a[_i]);puts("")
#define O(i)            printf("%d ",i)
#define On(i)           printf("%d\\n",i)
template<typename T, typename... Types>
void print(const T& first, const Types&... args) {
    cout << first << " ";
    print(args...);
}
#else
#define dea2(a,n,m)     0
#define dea(a,n)	    0
#define O(i)            0
#define On(i)           0

template<typename T, typename... Types>
inline void print(const T& first, const Types&... args){
    return;
}
#endif

#define PII pair<int, int>
vector<vector<int>> dir = {{0,1},{1,0},{0,-1},{-1,0}}; // 右下左上 顺时针
#define ULL unsigned long long
const int inf = 0x3f3f3f3f;
#define VI vector<int>
'''



