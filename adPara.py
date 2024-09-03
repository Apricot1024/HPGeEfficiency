import sys

ad_path = '/home/apricot/Desktop/run2407/include/SizeConstant.hh'
#以读取方式打开需要修改的文件为f
f = open(ad_path, 'r', encoding='utf-8')

# 检查是否有足够的参数传入
if len(sys.argv) < 2:
    print("Usage: python3 adPara.py <parameter>")
    sys.exit(1)  # 退出程序
    
de = eval(sys.argv[1])

if de <= 15:
    #将文件中的内容写入数组new[]
    new=[]
    for line in f:
        new.append(line)
    f.close()

    # de = eval(input())
    parameter = 75 + de
    # parameter = 349000 - 1000*de  
    #在数组new[]中修改需要改变的参数
    new[6]=f'const G4double dGepDz = {parameter} / 2.0 * CLHEP::mm; //const\n'
    # new[12]=f'const G4double dTAlpRMax = dTAlpRMin + {parameter} * CLHEP::mm;//const\n'
    # new[16]=f'const G4double dBoAlpDz = {parameter}/2.0 * CLHEP::mm;\n'
    # new[9]=f'const G4double dWellpRMax = sqrt((CLHEP::pi * dGepRMax * dGepRMax * dGepDz * 2 - {parameter}) / (dWellpDz * 2 * CLHEP::pi));\n'
    # parameter = 75 + de
    # new[5] = f'const G4double dGepRMax = {parameter} / 2.0 * CLHEP::mm;\n'
    # new[6] = f'const G4double dGepDz = {parameter} / 2.0 * CLHEP::mm;\n'
    # parameter = 14 + de/5
    # new[11] = f'const G4double dTAlpRMin = {parameter} / 2 * CLHEP::mm;\n'
    

    #以覆盖写的方式打开需要修改的文件
    f = open(ad_path, 'w', encoding='utf-8')

    #将数组new[]中的内容覆盖写到文件中
    for n in new:
        f.write(n)
    f.close()
elif de <= 30:
    #将文件中的内容写入数组new[]
    new=[]
    for line in f:
        new.append(line)
    f.close()

    new[6]=f'const G4double dGepDz = 80 / 2.0 * CLHEP::mm; //const\n'
    # de = eval(input())
    parameter = 60 + de
    #在数组new[]中修改需要改变的参数
    new[5]=f'const G4double dGepRMax = {parameter} / 2.0 * CLHEP::mm;\n'
    # new[16]=f'const G4double dBoAlpDz = {parameter}/2.0 * CLHEP::mm;\n'
    # new[84]='  if (fEdep == particleEnergy)\n'

    #以覆盖写的方式打开需要修改的文件
    f = open(ad_path, 'w', encoding='utf-8')

    #将数组new[]中的内容覆盖写到文件中
    for n in new:
        f.write(n)
    f.close()
elif de <= 45:
    #将文件中的内容写入数组new[]
    new=[]
    for line in f:
        new.append(line)
    f.close()

    new[6]=f'const G4double dGepDz = 80 / 2.0 * CLHEP::mm; //const\n'
    # de = eval(input())
    # parameter = 60 + de
    #在数组new[]中修改需要改变的参数
    new[5]=f'const G4double dGepRMax = 80 / 2.0 * CLHEP::mm;\n'
    # new[16]=f'const G4double dBoAlpDz = {parameter}/2.0 * CLHEP::mm;\n'
    # new[84]='  if (fEdep == particleEnergy)\n'
    parameter = 379000 - 1000*de      
    new[9]=f'const G4double dWellpRMax = sqrt((CLHEP::pi * dGepRMax * dGepRMax * dGepDz * 2 - {parameter}) / (dWellpDz * 2 * CLHEP::pi));\n'

    #以覆盖写的方式打开需要修改的文件
    f = open(ad_path, 'w', encoding='utf-8')

    #将数组new[]中的内容覆盖写到文件中
    for n in new:
        f.write(n)
    f.close()
