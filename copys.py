#!/bin/python3
import sys

ss = ""
with open(sys.argv[1]) as w:
    buff = w.read()
    buff = buff.split("\n")
    # print(buff)
    start = False
    for i in range(len(buff)):
        # print(i)
        if '// @lc code=end' in buff[i]:
            break
        # print(i,start,buff[i])
        if start:
            ss+=buff[i] + '\n'
        if '// @lc code=start' in buff[i]:
            start = True
# print(ss) 
        
with open('buffer.txt', 'w') as f:
    f.write(ss)
print("COPYED, just go √√√√√√√√√√√√√√√√√√√√√√√√√√√√√√√√√√√√√√√√")