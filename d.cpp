//输入：s = "aacecaaa"
//输出："aaacecaaa"
//输入：s = "abcd"
//输出："dcbabcd"
//
//undefined

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
// @test("aacecaaa")="aaacecaaa"
// @test("abcd")="dcbabcd"




class Solution {
public:
    const int P = 131;    
    string shortestPalindrome(string s) {
        string sre = s; 
        int n = sz(s);
        vector<ULL> p(n), h(n), hre(n);
        reverse(sre.begin(), sre.end());
        p[0] = 1;
        rep(i,1,n+1){
            p[i] = p[i-1] * P;
            h[i] = h[i-1] * P + s[i -1];
            hre[i] = hre[i-1] *P + sre[i -1];
        }
        auto get = [&](int l, int r, vector<ULL>& u){
            return u[r] - u[l-1] * p[r-l+1];
        };
         
        for(int i = n; i >0; i--) {
            print(i,s.substr(0, i - 1), sre.substr(n - i, n - 1));
            if(get(1, i, h)
                == get(n - i + 1, n, hre)) 
                return sre.substr(0 ,n - i) + s;

            // for(int j = 0; j < i; j++){
            //     if(s[j] != sre[n - i + j]){
            //         ok = false;
            //         break; 
            //     }
            // }
        }
        return sre + s;
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
        auto arg0 = parseString(input[0]);
        auto o = s-> shortestPalindrome(arg0);
        auto res = serializeString(o);
 
        print("---out", res, res == out ? "OOOO" : "XXXX");
        if (res != out) ok = false;
    }
    puts(ok ? "OOOOOOOOOOOOOOOOO" : "XXXXXXXXXXXXXXXXX");
    if(ok) return 0;
    return 1;
}
#endif
