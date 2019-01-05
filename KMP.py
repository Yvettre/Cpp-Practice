# coding=utf-8

'''
python实现KMP算法，求B串在A串中首次出现的位置，若没有出现则返回-1

与KMP.cpp搭配食用=。=
当然也有很多看起来很简单的方法实现的，我实在折腾不动了，还是做个安静的调包侠吧=。=
'''

def generatePartMatchList(B_string):
  '''
  根据子串生成部分匹配表，例如：
  "ABCDABD" => [0,0,0,0,1,2,0]
  '''
  prefix = set()
  postfix = set()
  result = [0]
  for i in xrange(1, len(B_string)):
    prefix.add(B_string[:i])
    postfix = {B_string[j:i+1] for j in xrange(1,i+1)}
    # 求交集并取最长的元素求长度
    result.append(len((prefix&postfix or {''}).pop()))
  return result


def findAppearance(A_string, A_len, B_string, B_len):
  '''
  KMP算法匹配第一个位置，若不存在，返回-1
  '''
  partList = generatePartMatchList(B_string)
  curA = 0 # 起始指针
  curB = 0
  while curA <= (A_len-B_len):
    for i in xrange(curB, B_len):
      if A_string[i+curA] != B_string[i]:
        # cur向后移动位数 = 已匹配的字符数-对应的部分匹配值
        if i==0:
          curA = curA+1
          curB = 0
        else:
          curA = curA + max(i - partList[i-1], 1)
          curB = partList[i-1]
        break
      if i == (B_len-1):
        return curA
  return -1


def main():
  A_string = 'BBC ABCDAB ABCDABCDABDE'
  B_string = 'ABCDABD'

  A_len = len(A_string)
  B_len = len(B_string)

  print "A:{}".format(A_string)
  print "B:{}".format(B_string)

  pos = findAppearance(A_string, A_len, B_string, B_len)

  print pos


if __name__ == '__main__':
  main()