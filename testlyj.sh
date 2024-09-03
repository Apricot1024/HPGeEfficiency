#! /bin/zsh


cd /home/apricot/Desktop/run2407/
# 调整参数  
# python3 adPara.py $i
# Geant4模拟
cd build
make

./exampleB1 runlyjeudemo1.mac > log.txt
rm log.txt
root -l -q 'toHis.cpp'
mv AnaEx01.root 147AnaEx01.root
./exampleB1 runlyjcodemo1.mac > log.txt
rm log.txt
root -l -q 'toHis.cpp'
mv AnaEx01.root 56AnaEx01.root
root -l -q 'hisaddlyj.cc'
cp AnaEx01.root ../../gamma_ana/sim_root2407/AnaEx01.root
# mv AnaEx01.root ../rootfile/${j}AnaEx01_50.root

# # 生成效率数据
cd ../../gamma_ana
python3 ./src/sim_runlyj.py 50
python3 ./src/plot_comparelyj.py 50

# # 存储数据
# rm ./sim_root2407/*AnaEx01.root
# cp ./sim_root2407/*.txt ../run2407/simulatedEffdata/
# # rm -rf ./sim_root2407/*.txt