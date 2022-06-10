#!/bin/python3

import sys

with open(sys.argv[1]) as w:
    a = w.read()
with open(sys.argv[1]) as w:
    lines = w.readlines()
if(a.find('mainfuc')!=-1):
    if a.count("include") >= 2:
        with open(sys.argv[1], "w") as f:
            for i in lines:
                if "include" in i and "bits/stdc++.h" not in i:
                    continue 
                f.write(i)
        exit(0)
    else:
        exit(0)
aline = a.split("\n") # 读出来以后分行
for i in range(len(aline)):
    if("public:" in aline[i]):
        main = aline[i+1]
        break
ss = main.strip() # main函数来判断都有哪些

for i in range(len(ss)):
    if ss[i] == "(":
        for j in range(i,0,-1):
            if(ss[j]==' '):
                outpos = j # 这个是提取出来的函数返回值
                break
        break


# outpos = ss.find(" ") # ss[:outpos]
funcpos = ss.find("(")
a = ss[funcpos + 1:ss.find(")")].split(',')  # 这个是每一个参数是什么
ins = []
print(ss)
out = ss[:outpos] # 返回值
for i in a:
    line = i.strip().split(' ')[0] # 每一个类型
    if line[-1] == '&':
        line = line[:-1]
    ins.append(line) # 类型后面加上去
funcname = ss[outpos:funcpos]
ins, out,funcname
print(out)

indic = {
# 字符
"bool":["","serializeBool"],
"char":["parseChar","serializeChar"],
"vector<char>":["parseCharArr","serializeCharArr"],
"vector<vector<char>>":["parseCharArrArr" ,"serializeCharArrArr"],
# 浮点数
"float":["parseFloat","serializeFloat"],
"double":["parseFloat","serializeInteger"],
# 整形
"int":["parseInteger","serializeInteger"],
"vector<int>":["parseIntegerArr","serializeIntegerArr"],
"vector<vector<int>>":["parseIntegerArrArr","serializeIntegerArrArr"],
# 长整形
"long":["parseInteger","serializeInteger"],
"long long":["parseInteger","serializeInteger"],
## todo
# 链表
"ListNode":["parseListNode","serializeListNode"],
"vector<ListNode*>":["parseListNodeArr","serializeListNodeArr"],
# 字符串
"string":["parseString","serializeString"],
"vector<string>":["parseStringArr","serializeStringArr"],
"vector<vector<string>>":["parseStringArrArr","serializeStringArrArr"],
#
"Node":["parseNode","serializeNode"], #// todo
"TreeNode":["parseTreeNode","serializeTreeNode"],
"vector<TreeNode *>":["parseTreeNodeArr","serializeTreeNodeArr"],
}
# outdic = {
# # "bool":"serializeBool",
# "char":"serializeChar",
# "vector<char>":"serializeCharArr",
# "vector<vector<char>>":"serializeCharArrArr",
# "double":"serializeFloat",
# "int":"serializeInteger",
# "long long":"serializeInteger",
# # "long":"serializeInteger",
# "vector<int>":"serializeIntegerArr",
# "vector<vector<int>>":"serializeIntegerArrArr",
# "ListNode*":"serializeListNode",
# "vector<ListNode*>":"serializeListNodeArr",
# "string":"serializeString",
# "vector<string>":"serializeStringArr",
# "vector<vector<string>>":"serializeStringArrArr",
# "TreeNode*":"serializeTreeNode",
# "vector<TreeNode*>":"serializeTreeNodeArr"
# }
s = """
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
"""
for i in range(len(ins)):
    s+= f"auto arg{i} = {indic[ins[i]][0]}(input[{i}]);\n"
s+= f"auto o = s->{funcname}(arg0"
for i in range(1, len(ins)):
    s+= f",arg{i}"
# print(out)
s+= f");\n        auto res = {indic[out][1]}(o);\n"
s+=''' 
        print("---out", res, res == out ? "OOOO" : "XXXX");
        if (res != out) ok = false;
    }
    puts(ok ? "OOOOOOOOOOOOOOOOO" : "XXXXXXXXXXXXXXXXX");
    if(ok) return 0;
    return 1;
}
#endif
'''
#         auto arg0 = parseIntegerArr(input[0]);
#         auto arg1 = parseInteger(input[1]);
#         auto res = serializeBool(s->containsNearbyDuplicate(arg0, arg1));
#         print("---out", res, res == out ? "√            √": "XX");
#     }
#     return 0;
# print(s)

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
ss = ""

for i in range(len(aline)):
    j = aline[i]
    if("输入" in j): 
        j = j[j.index("输入")+3:]
        #print(j)
        tt,start = 0,0
        inpu = []
        for k in range(len(j)):
            if(j[k] == '['):tt+=1
            elif j[k] == ']':tt-=1
            elif tt==0 and j[k] == ',':
                inpu.append(j[start:k])
                start = k + 1
        inpu.append(j[start:])
        inputs = []
        for o in inpu:
            inputs.append(o.split('=')[-1].strip())

        ss += f'// @test({",".join(inputs)})='
        j = aline[i+1]
        ss += (j.split('：')[-1]).split(':')[-1] + '\n' # 这个可能不完美吧
print(ss)
for i in range(len(aline)):
    # print(i)
    if(aline[i].strip() == ""): 
        aline[i] = startss + ss
        break









# print(aline)
with open(sys.argv[1], 'w') as f:
    for i in aline:
        f.write(i + '\n')
    f.write('\n'*1+s)
