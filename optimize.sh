#! /bin/zsh

cd /home/apricot/Desktop/run2407/   
rm -rf build
mkdir build
cp toHis.cpp build
cp haddhis.cc build
cd build
cmake ..
for i in {1..9}
do
    cd /home/apricot/Desktop/run2407/
    # 调整参数  
    python3 adPara.py $i
    # Geant4模拟
    cd build
    make
    for j in {18..20}
    do
        ./exampleB1 run${j}55.mac > log.txt
        rm log.txt
        root -l -q 'toHis.cpp'
        mv AnaEx01.root 55AnaEx01.root
        ./exampleB1 run${j}57.mac > log.txt
        rm log.txt
        root -l -q 'toHis.cpp'
        mv AnaEx01.root 57AnaEx01.root
        ./exampleB1 run${j}58.mac > log.txt
        rm log.txt
        root -l -q 'toHis.cpp'
        mv AnaEx01.root 58AnaEx01.root
        root -l -q 'haddhis.cc'
        cp AnaEx01.root ../../gamma_ana/sim_root2407/${j}AnaEx01.root
        mv AnaEx01.root ../rootfile/${j}AnaEx01_${i}.root
    done

    # 生成效率数据
    cd ../../gamma_ana
    python3 ./src/sim_rundemo.py ${i}
    python3 ./src/plot_compare_demo.py ${i}

    # 存储数据
    rm ./sim_root2407/*AnaEx01.root
    cp ./sim_root2407/*.txt ../run2407/simulatedEffdata/
    # rm -rf ./sim_root2407/*.txt

    # 运行提示
    echo 'succeed for' ${i} 'times'
done    