# 本py脚本用于自动改写B1DetectorConstruction.cc中屏蔽板的厚度,rundemo.mac中的能量及发射粒子数量，steppingaction.cc中的能量判选
particleNum = 500000#总粒子数
# exceptNum = 300000
i = 10

while i <= 1000:#循环过程

    #以读取方式打开需要修改的文件为f
    f = open('/home/apricot/Documents/Science/HPGe_Geant4/workdir/{}egr/src/EventAction.cc'.format(i), 'r', encoding='utf-8')
    
    #将文件中的内容写入数组new[]
    new=[]
    for line in f:
        new.append(line)
    f.close()

    #在数组new[]中修改需要改变的参数
    new[41]='G4double particleEnergy = {}*CLHEP::keV;\n'.format(i)
    new[84]='  if (fEdep >= particleEnergy-0.01*CLHEP::keV)\n'
    # new[84]='  if (fEdep == particleEnergy)\n'

    #以覆盖写的方式打开需要修改的文件
    f = open('/home/apricot/Documents/Science/HPGe_Geant4/workdir/{}egr/src/EventAction.cc'.format(i), 'w', encoding='utf-8')

    #将数组new[]中的内容覆盖写到文件中
    for n in new:
        f.write(n)
    f.close()



    #以下两个文件的修改与上述过程类似
    f1 = open('/home/apricot/Documents/Science/HPGe_Geant4/workdir/{}egr/src/HistoManager.cc'.format(i), 'r', encoding='utf-8')
    new1=[]
    for line in f1:
        new1.append(line)
    f1.close()
    new1[86]='    G4double xmax = {}*keV;\n'.format(i+5)
    f1 = open('/home/apricot/Documents/Science/HPGe_Geant4/workdir/{}egr/src/HistoManager.cc'.format(i), 'w', encoding='utf-8')
    for n in new1:
        f1.write(n)
    f1.close()

    f3 = open('/home/apricot/Documents/Science/HPGe_Geant4/workdir/{}egr/build/runuser2.mac'.format(i), 'r', encoding='utf-8')
    new3=[]
    for line in f3:
        new3.append(line)
    f3.close()
    new3[8]='/gun/energy {} keV\n'.format(i)
    new3[10]='/run/beamOn {}\n'.format(particleNum)
    f3 = open('/home/apricot/Documents/Science/HPGe_Geant4/workdir/{}egr/build/runuser2.mac'.format(i), 'w', encoding='utf-8')
    for n in new3:
        f3.write(n)
    f3.close()


    i += 10