//输入：tasks = [2,2,3,3,2,4,4,4,4,4]
//输出：4
//输入：tasks = [2,3,3]
//输出：-1

#include <unordered_map>
#include <vector>
#ifdef zz
#include "bits/stdc++.h"
#define newline (getline(cin,line),line)
#endif
using namespace std;
// @lc code=start
#define O(i)            printf("%d ",i)
#define On(i)           printf("%d\n",i)
#define rep(i, j, n)    for(int i=(j);i<(n);i++)
#define per(i, n, j)    for(int i=(n)-1;i>=(j);--i)
#define sz(a)         ((int)a.size())
#define dea2(a,n,m)    rep(_i, 0, n) { rep(_j, 0, m) O(a[_i][_j]); puts(""); }
#define dea(a,n)	       rep(_i,0,n)O(a[_i]);puts("")
void print() { puts(""); }
template<typename T, typename... Types>
void print(const T& first, const Types&... args) {
    cout << first << " ";
    print(args...);
}
const int dx[] = { 1,-1,0,0 }, dy[] = { 0,0,1,-1 };
#define ULL unsigned long long
const int inf = 0x3f3f3f3f;
#define VI vector<int>
// @test([2,2,3,3,2,4,4,4,4,4])=4
// @test([2,3,3])=-1


class Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        unordered_map<int, int>      um;
        for(auto i:tasks) um[i]++;
        int res = 0;
        for(auto [k,v]:um){
            if(v == 1) return -1;
            int i = v/3;
            while(i>=0){
                int left = v - i * 3; 
                if(left%2 == 0){
                    res += i + left/2;
                }
                i--;
            }
        }
        return res;
    }
};



// @lc code=end

#ifdef mainfuc
int main() {
    string line;
    bool ok = true;
    while (!cin.eof()) {
        Solution* s = new Solution();
        newline;
        if (line.find("// @test(") != 0) continue;
        auto input = parseInput(line);
        auto out = input[sz(input) - 1];
        auto arg0 = parseIntegerArr(input[0]);
        auto o = s-> minimumRounds(arg0);
        auto res = serializeInteger(o);
 
        print("---out", res, res == out ? "OOOO" : "XXXX");
        if (res != out) ok = false;
    }
    puts(ok ? "OOOOOOOOOOOOOOOOO" : "XXXXXXXXXXXXXXXXX");
    if(ok) return 0;
    return 1;
}
#endif
