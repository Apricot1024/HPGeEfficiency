particleNum = 10#总粒子数
egr = 10#循环参数，从6循环至35
f = open('./build/rundemo.mac', 'r', encoding='utf-8')
new=[]
for line in f:
    new.append(line)
f.close()
f = open('./build/runuser.mac', 'w', encoding='utf-8')
for n in new:
    f.write(n)
f.close()
f = open('./build/runuser.mac', 'a', encoding='utf-8')
f.write('/gun/particle gamma\n')
while egr <= 1000:
    f.write('/gun/energy {} keV\n'.format(egr))
    f.write('#\n')
    f.write('/run/beamOn {}\n'.format(particleNum))
    f.write('#\n')
    egr += 1
f.close()
    
    
    






# while i <= 35:#循环过程
#     j = i % 6#j为i除以6的余数，在i从6到35的循环过程中，j从0-5循环5次

#     #以读取方式打开需要修改的文件为f
#     f = open('/home/apricot/Documents/GraduationProject/Geant4Work/scatteringRate/Inf0506/Pb/{}mud{}/src/B1DetectorConstruction.cc'.format(mud[i-6],enerNum[j]), 'r', encoding='utf-8')
    
#     #将文件中的内容写入数组new[]
#     new=[]
#     for line in f:
#         new.append(line)
#     f.close()

#     #在数组new[]中修改需要改变的参数
#     new[63]='  G4double mudh = {};\n'.format(hou[i-6])

#     #以覆盖写的方式打开需要修改的文件
#     f = open('/home/apricot/Documents/GraduationProject/Geant4Work/scatteringRate/Inf0506/Pb/{}mud{}/src/B1DetectorConstruction.cc'.format(mud[i-6],enerNum[j]), 'w', encoding='utf-8')

#     #将数组new[]中的内容覆盖写到文件中
#     for n in new:
#         f.write(n)
#     f.close()



#     #以下两个文件的修改与上述过程类似
#     f1 = open('/home/apricot/Documents/GraduationProject/Geant4Work/scatteringRate/Inf0506/Pb/{}mud{}/build/rundemo.mac'.format(mud[i-6],enerNum[j]), 'r', encoding='utf-8')
#     new1=[]
#     for line in f1:
#         new1.append(line)
#     f1.close()
#     new1[8]='#/tracking/verbose 1\n'
#     new1[13]='/gun/energy {} MeV\n'.format(energy[j])
#     new1[15]='/run/beamOn {}\n'.format(particleNum)
#     f1 = open('/home/apricot/Documents/GraduationProject/Geant4Work/scatteringRate/Inf0506/Pb/{}mud{}/build/rundemo.mac'.format(mud[i-6],enerNum[j]), 'w', encoding='utf-8')
#     for n in new1:
#         f1.write(n)
#     f1.close()

#     # f3 = open('/home/apricot/Documents/GraduationProject/Geant4Work/scatteringRate/Inf0506/Pb/{}mud{}/src/B1PrimaryGeneratorAction.cc'.format(mud[i-6],enerNum[j]), 'r', encoding='utf-8')
#     # new3=[]
#     # for line in f3:
#     #     new3.append(line)
#     # f3.close()
#     # new3[83]='  G4double mudh = {};\n'.format(hou[i-6])
#     # f3 = open('/home/apricot/Documents/GraduationProject/Geant4Work/scatteringRate/Inf0506/Pb/{}mud{}/src/B1PrimaryGeneratorAction.cc'.format(mud[i-6],enerNum[j]), 'w', encoding='utf-8')
#     # for n in new3:
#     #     f3.write(n)
#     # f3.close()

#     f4 = open('/home/apricot/Documents/GraduationProject/Geant4Work/scatteringRate/Inf0506/Pb/{}mud{}/src/B1SteppingAction.cc'.format(mud[i-6],enerNum[j]), 'r', encoding='utf-8')
#     new4=[]
#     for line in f4:
#         new4.append(line)
#     f4.close()
#     new4[58]='int eventIDflag[{}] = {{{}}};  //重复计数排除数组\n'.format(particleNum,particleNum+1)
#     new4[59]='int eventIDconvflag[{}] = {{{}}};  // 对发生电子对效应的粒子进行统计\n'.format(particleNum,particleNum+1)
#     new4[99]='      if (E == {})\n'.format(energy[j])
#     new4[119]='            if (E == {})\n'.format(energy[j])
#     new4[130]='    if ((eventID == {}) & (outputcode == 10))\n'.format(particleNum-1)
#     f4 = open('/home/apricot/Documents/GraduationProject/Geant4Work/scatteringRate/Inf0506/Pb/{}mud{}/src/B1SteppingAction.cc'.format(mud[i-6],enerNum[j]), 'w', encoding='utf-8')
#     for n in new4:
#         f4.write(n)
#     f4.close()

#     i = i + 1