import sys

ad_path = '/home/apricot/Desktop/run2407/include/SizeConstant.hh'
#以读取方式打开需要修改的文件为f
f = open(ad_path, 'r', encoding='utf-8')

# 检查是否有足够的参数传入
if len(sys.argv) < 2:
    print("Usage: python3 adPara.py <parameter>")
    sys.exit(1)  # 退出程序
    
de = eval(sys.argv[1])

#将文件中的内容写入数组new[]
new=[]
for line in f:
    new.append(line)
f.close()

# de = eval(input())
parameter = 1 - de / 10
#在数组new[]中修改需要改变的参数
new[21]=f'const G4double dHolderpDz = {parameter} / 2.0 * CLHEP::mm;\n'
# new[16]=f'const G4double dBoAlpDz = {parameter}/2.0 * CLHEP::mm;\n'
# new[84]='  if (fEdep == particleEnergy)\n'

#以覆盖写的方式打开需要修改的文件
f = open(ad_path, 'w', encoding='utf-8')

#将数组new[]中的内容覆盖写到文件中
for n in new:
    f.write(n)
f.close()

