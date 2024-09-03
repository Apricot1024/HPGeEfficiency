import sys

ad_path = '/home/apricot/Desktop/run2407/build/runeffdemo.mac'

f = open(ad_path, 'r', encoding='utf-8')

# 检查是否有足够的参数传入
if len(sys.argv) < 2:
    print("Usage: python3 adPara.py <parameter>")
    sys.exit(1)  # 退出程序
    
run = eval(sys.argv[1])

# run = 2

new=[]
for line in f:
    new.append(line)
f.close()

new[15] = f"/gun/energy {run} keV\n"

f = open(ad_path, 'w', encoding='utf-8')

for n in new:
    f.write(n)
f.close()