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
template <typename T>
struct UF {
    int cnt = 0;
    unordered_map<T, T> p;
    unordered_map<T, int> size;
    UF(int x = 0){};
    void add(T x) {
        if (!p.count(x)) p[x] = x, size[x] = 1, cnt++;
    }
    bool have(T x) {
        return p.count(x);
    }
    T find(T x) {
        add(x);
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }
    void uni(T x, T y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (cnt[x] > cnt[y]) swap(x, y);
        p[x] = y;
        cnt--;
        size[y] += size[x];
    }
};