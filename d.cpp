//输入：s = "00110"
//输出：1
//输入：s = "010110"
//输出：2
//输入：s = "00011000"
//输出：2
//
//undefined

#ifdef zz
#include "bits/stdc++.h"
#define newline (getline(cin, line), line)
#endif
using namespace std;
// @lc code=start
#define rep(i, j, n) for (int i = (j); i < (n); i++)
#define per(i, n, j) for (int i = (n) -1; i >= (j); --i)
#define sz(a) ((int) a.size())

void print() { puts(""); }

#ifdef zz
#define dea2(a, n, m)               \
    rep(_i, 0, n) {                 \
        rep(_j, 0, m) O(a[_i][_j]); \
        puts("");                   \
    };                              \
    puts("")
#define dea(a, n)           \
    rep(_i, 0, n) O(a[_i]); \
    puts("")
#define O(i) printf("%d ", i)
#define On(i) printf("%d\n", i)
template <typename T, typename... Types>
void print(const T &first, const Types &... args) {
    cout << first << " ";
    print(args...);
}
#else
#define dea2(a, n, m) 0
#define dea(a, n) 0
#define O(i) 0
#define On(i) 0

template <typename T, typename... Types>
inline void print(const T &first, const Types &... args) {
    return;
}
#endif

#define PII pair<int, int>
vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // 右下左上 顺时针
#define ULL unsigned long long
const int inf = 0x3f3f3f3f;
#define VI vector<int>
// @test("00110")=1
// @test("010110")=2
// @test("00011000")=2

class Solution {
  public:
    int minFlipsMonoIncr(string s) {
        int n = s.size();
        int l = 0, r = n - 1;
        int now = 0;
        while (l < r) {
            while (l < s.size() && s[l] == '0') l++;
            while (r >= 0 && s[r] == '1') r--;
            if (l < r) now += 2;
            l++, r--;
        }
        return now;
    }
};

// @lc code=end

#ifdef mainfuc
int main() {
    string line;
    bool ok = true;
    while (!cin.eof()) {
        Solution *s = new Solution();
        newline;
        if (line.find("// @test(") != 0) continue;
        auto input = parseInput(line);
        auto out = input[sz(input) - 1];
        auto arg0 = parseString(input[0]);
        auto o = s->minFlipsMonoIncr(arg0);
        auto res = serializeInteger(o);

        print("---out", res, res == out ? "OOOO" : "XXXX");
        if (res != out) ok = false;
    }
    puts(ok ? "OOOOOOOOOOOOOOOOO" : "XXXXXXXXXXXXXXXXX");
    if (ok) return 0;
    return 1;
}
#endif
