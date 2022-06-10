// C++ includes used for precompiling -*- C++ -*-

// Copyright (C) 2003-2019 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file stdc++.h
 *  This is an implementation file for a precompiled header.
 */

// 17.4.1.2 Headers

// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
// #include <cuchar>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
// #include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#endif

#if __cplusplus >= 201402L
// #include <shared_mutex>
#endif

#if __cplusplus >= 201703L
#include <any>
#include <charconv>
// #include <execution>
#include <filesystem>
#include <memory_resource>
#include <optional>
#include <string_view>
#include <variant>
#endif

#if __cplusplus > 201703L
#include <bit>
// #include <compare>
// #include <span>
// #include <syncstream>
#include <version>
#endif
using namespace std;
void trim(string &s) {
    if (s.empty()) {
        return;
    }
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
}
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Node {
  public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};
string serializeNode(Node *root) {
    return "todo undefined";
}
void split(std::string param, char seg, std::vector<std::string> &arr) {
    std::string temp = "";
    for (auto it = param.begin(); it != param.end(); it++) {
        if (*it == seg) {
            arr.push_back(temp);
            temp = "";
        } else {
            temp += *it;
        }
    }
    arr.push_back(temp);
}
Node *parseNode(string param) {
    int len = param.length();
    if (len <= 2) {
        return nullptr;
    }
    std::vector<std::string> nodeData;
    split(param.substr(1, len - 2), ',', nodeData);
    if (nodeData.size() == 0) {
        return nullptr;
    }
    int cnt = 0; // todo
    // for (auto i : nodeData) print(++cnt, i);

    return nullptr;
}
int parseInteger(std::string param) {
    return atoi(param.data());
}
double parseFloat(std::string param) {
    std::string::size_type size;
    return stod(param, &size);
}
std::string serializeFloat(double param) {
    std::string str = std::to_string(param);
    return str.substr(0, str.length() - 1);
}
std::string serializeBool(bool t) {
    if (t == true) {
        return "true";
    }
    return "false";
}
std::vector<int> parseIntegerArr(std::string param) {
    std::vector<int> nums;
    if (param.length() <= 2) {
        return nums;
    }
    std::string temp = "";
    std::string::iterator it;
    for (it = param.begin() + 1; it != param.end() - 1; it++) {
        if (*it == ',') {
            nums.push_back(stoi(temp));
            temp = "";
        } else {
            temp += *it;
        }
    }
    if (temp != "") {
        nums.push_back(stoi(temp));
    }
    return nums;
}
std::vector<std::vector<int>> parseIntegerArrArr(std::string param) {
    std::vector<std::vector<int>> nums;
    int len = param.length();
    if (len <= 4) {
        return nums;
    }
    std::string subStr = param.substr(1, len - 2);
    for (int i = 1; i < len - 1; i++) {
        if (param[i] == '[') {
            std::string temp = "";
            temp += param[i++];
            while (param[i] != ']') {
                temp += param[i++];
            }
            temp += param[i++];
            std::vector<int> arr = parseIntegerArr(temp);
            nums.push_back(arr);
        }
    }
    return nums;
}
std::string parseString(std::string param) {
    if (param.length() <= 2) {
        return "";
    }
    std::string out = "";
    std::string::iterator it;
    for (int i = 1; i < param.length(); i++) {
        char c = param[i];
        if (c == '\\') {
            char n = param[i + 1];
            if (n == 'u') {
                std::string unicodeStr = param.substr(i + 2, 4);
                char16_t num = strtol(unicodeStr.data(), NULL, 16);
                out += num;
                i += 5;
            } else {
                char echars[8] = {'"', '\\', '/', 'b', 'f', 'n', 'r', 't'};
                char realChars[8] = {'"', '\\', '/', '\b', '\f', '\n', '\r', '\t'};
                bool has = false;
                for (int j = 0; j < 8; j++) {
                    if (echars[j] == n) {
                        has = true;
                        out += realChars[j];
                        i++;
                        break;
                    }
                }
                if (!has) {
                    std::cout << "parse string error in " + param.substr(0, i + 1);
                }
            }
        } else if (c == '"') {
            return out;
        } else {
            out += c;
        }
    }
    std::cout << "parse string error in " + param;
    return "";
}
std::vector<std::string> parseStringArr(std::string s) {
    std::vector<std::string> res;
    int n = s.size();
    int i = 0;
    int start = -1;
    while (i < n) {
        if (s[i] == '"') {
            if (start != -1) {
                res.push_back(s.substr(start, i - start));
                start = -1;
            } else
                start = i + 1;
        }
        i++;
    }
    return res;
}
std::vector<std::vector<std::string>> parseStringArrArr(std::string s) {
    s = s.substr(1, s.size() - 1);
    std::vector<std::vector<std::string>> res;
    for (int i = 0; i < s.size();) {
        int j = 1;
        while (i + j < s.size() && s[i + j] != ']') j++;
        auto s_sub = s.substr(i, j + 1);
        res.push_back(parseStringArr(s_sub));
        i += j + 2;
    }
    return res;
}

char parseChar(std::string param) {
    std::string str = parseString(param);
    return str.at(0);
}

std::vector<char> parseCharArr(std::string param) {
    std::vector<char> r;
    std::vector<std::string> strArr = parseStringArr(param);
    for (auto it = strArr.begin(); it != strArr.end(); it++) {
        r.push_back((*it).at(0));
    }
    return r;
}
std::vector<std::vector<char>> parseCharArrArr(std::string param) {
    std::vector<std::vector<char>> r;
    std::vector<std::vector<std::string>> strArrArr = parseStringArrArr(param);
    for (auto it = strArrArr.begin(); it != strArrArr.end(); it++) {
        std::vector<std::string> strArr = *it;
        std::vector<char> item;
        for (auto it2 = strArr.begin(); it2 != strArr.end(); it2++) {
            item.push_back((*it2).at(0));
        }
        r.push_back(item);
    }
    return r;
}
std::string serializeChar(char param) {
    std::string r = "\"";
    if (param == '\\' || param == '"') {

        r += '\\';
    }
    r += param;
    r += '"';
    return r;
}
std::string serializeCharArr(std::vector<char> param) {
    std::string r = "[";
    for (auto it = param.begin(); it != param.end(); it++) {
        if (it != param.begin()) {
            r += ",";
        }
        r += serializeChar(*it);
    }
    r += "]";
    return r;
}
std::string serializeCharArrArr(std::vector<std::vector<char>> param) {
    std::string r = "[";
    for (auto it = param.begin(); it != param.end(); it++) {
        if (it != param.begin()) {
            r += ",";
        }
        r += serializeCharArr(*it);
    }
    r += "]";
    return r;
}
// void print() { puts(""); }
// template<typename T, typename... Types>
// void print(const T& first, const Types&... args) {
//     std::cout << first << " ";
//     print(args...);
// }
TreeNode *parseTreeNode(std::string param) {
    int len = param.length();
    if (len <= 2) {
        return nullptr;
    }
    // [1,2,3,4,5,6,7]
    std::vector<std::string> nodeData;
    split(param.substr(1, len - 2), ',', nodeData);
    if (nodeData.size() == 0) {
        return nullptr;
    }

    int i = 0;
    // for (auto i : nodeData) print(i);
    int val = stoi(nodeData[i++]);
    TreeNode *root = new TreeNode(val);
    std::queue<TreeNode *> q;
    q.push(root);
    while (q.size() > 0) {
        TreeNode *node = q.front();
        q.pop();
        if (i == nodeData.size()) {
            return root;
        }

        std::string leftVal = nodeData[i++];
        if (leftVal != "null") {

            node->left = new TreeNode(stoi(leftVal));
            q.push(node->left);
        }
        if (i == nodeData.size()) {
            return root;
        }
        std::string rightVal = nodeData[i++];
        if (rightVal != "null") {

            node->right = new TreeNode(stoi(rightVal));
            q.push(node->right);
        }
    }
    return root;
}
ListNode *parseListNode(std::string param) {
    int len = param.length();
    if (len <= 2) {
        return nullptr;
    }
    std::vector<std::string> arr;
    split(param.substr(1, len - 2), ',', arr);
    ListNode *head = new ListNode();
    ListNode *p = head;

    for (auto it = arr.begin(); it != arr.end(); it++) {
        p->next = new ListNode(stoi(*it));
        p = p->next;
    }

    return head->next;
}
std::vector<ListNode *> parseListNodeArr(std::string param) {
    std::vector<ListNode *> result;
    int len = param.length();
    if (len <= 4) {
        return result;
    }
    std::string subStr = param.substr(1, len - 2);
    for (int i = 1; i < len - 1; i++) {
        if (param[i] == '[') {
            std::string temp = "";
            temp += param[i++];
            while (param[i] != ']') {
                temp += param[i++];
            }
            temp += param[i++];
            ListNode *arr = parseListNode(temp);
            result.push_back(arr);
        }
    }
    return result;
}
std::vector<TreeNode *> parseTreeNodeArr(std::string param) {
    std::vector<TreeNode *> result;
    int len = param.length();
    if (len <= 4) {
        return result;
    }
    std::string subStr = param.substr(1, len - 2);
    for (int i = 1; i < len - 1; i++) {
        if (param[i] == '[') {
            std::string temp = "";
            temp += param[i++];
            while (param[i] != ']') {
                temp += param[i++];
            }
            temp += param[i++];
            TreeNode *arr = parseTreeNode(temp);
            result.push_back(arr);
        }
    }
    return result;
}
std::string serializeInteger(int param) {
    std::string str = std::to_string(param);
    return str;
}
std::string serializeInteger(long long param) {
    std::string str = std::to_string(param);
    return str;
}
std::string serializeIntegerArr(std::vector<int> &arr) {
    std::string out = "";
    for (auto it = arr.begin(); it != arr.end(); it++) {
        if (it == arr.end() - 1) {
            out += serializeInteger(*it);
        } else {
            out += serializeInteger(*it) + ",";
        }
    }
    return "[" + out + "]";
}
std::string serializeIntegerArrArr(std::vector<std::vector<int>> &arr) {
    std::string out = "";
    for (auto it = arr.begin(); it != arr.end(); it++) {
        if (it == arr.end() - 1) {
            out += serializeIntegerArr(*it);
        } else {
            out += serializeIntegerArr(*it) + ",";
        }
    }
    return "[" + out + "]";
}
std::string serializeString(std::string param) {
    int pos = 0;
    std::string out = "";
    for (auto it = param.begin(); it != param.end(); it++) {
        if (*it == '\\' || *it == '"') {
            out += "\\" + *it;
        } else {
            out += *it;
        }
    }
    return "\"" + out + "\"";
}
std::string serializeStringArr(std::vector<std::string> &param) {
    std::string out = "";
    for (auto it = param.begin(); it != param.end(); it++) {
        if (it == param.end() - 1) {
            out += serializeString(*it);
        } else {
            out += serializeString(*it) + ",";
        }
    }
    return "[" + out + "]";
}
std::string serializeStringArrArr(std::vector<std::vector<std::string>> &param) {
    std::string out = "";
    for (auto it = param.begin(); it != param.end(); it++) {
        if (it == param.end() - 1) {
            out += serializeStringArr(*it);
        } else {
            out += serializeStringArr(*it) + ",";
        }
    }
    return "[" + out + "]";
}
std::string serializeListNode(ListNode *head) {
    std::string out = "";
    while (head != nullptr) {
        out += std::to_string(head->val);
        head = head->next;
        if (head != nullptr) {
            out += ",";
        }
    }
    return "[" + out + "]";
}
std::string serializeTreeNode(TreeNode *root) {
    if (root == nullptr) {
        return "[]";
    }

    std::vector<std::string> arr;
    std::queue<TreeNode *> q;
    q.push(root);
    while (q.size() > 0) {

        TreeNode *node = q.front();
        q.pop();
        if (node == nullptr) {
            arr.push_back("null");
        } else {
            arr.push_back(std::to_string(node->val));
            q.push(node->left);
            q.push(node->right);
        }
    }

    while (arr.back() == "null") {
        arr.pop_back();
    }
    std::string out = "";
    for (auto it = arr.begin(); it != arr.end(); it++) {
        if (it == arr.end() - 1) {
            out += *it;
        } else {
            out += *it + ",";
        }
    }
    return "[" + out + "]";
}
std::string serializeListNodeArr(std::vector<ListNode *> &lists) {
    std::string out = "";
    for (auto it = lists.begin(); it != lists.end(); it++) {
        if (it == lists.end() - 1) {
            out += serializeListNode(*it);
        } else {
            out += serializeListNode(*it) + ",";
        }
    }
    return "[" + out + "]";
}
std::string serializeTreeNodeArr(std::vector<TreeNode *> &arr) {
    std::string out = "";
    for (auto it = arr.begin(); it != arr.end(); it++) {
        if (it == arr.end() - 1) {
            out += serializeTreeNode(*it);
        } else {
            out += serializeTreeNode(*it) + ",";
        }
    }
    return "[" + out + "]";
}
std::vector<std::string> parseInput(std::string line) {
    std::cout << line << "\n";
    int idx = line.find("=");
    std::string ins = line.substr(9, idx - 10);
    std::string out = line.substr(idx + 1);
    std::vector<std::string> input;
    int start = 0, tt = 0;
    for (int i = 0; i < ins.size(); i++) {
        if (ins[i] == '[')
            tt++;
        else if (ins[i] == ']')
            tt--;
        else if (!tt && ins[i] == ',') {
            input.push_back(ins.substr(start, i - start));
            start = i + 1;
        }
    }
    input.push_back(ins.substr(start));
    input.push_back(out);
    for (auto &i : input) trim(i);
    return input;
}