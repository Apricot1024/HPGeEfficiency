#! /bin/zsh

cd /home/apricot/Desktop/HPGeEfficiency/

cd build
make

rm /home/apricot/Desktop/gamma_ana/sim_eff2408/*.txt

for run in {1400..10000}
do
    cd /home/apricot/Desktop/HPGeEfficiency/
    python3 adegr.py ${run}
    cd build
# make
    ./exampleB1 runeffdemo.mac > log.txt
    rm log.txt
    root -l -q 'toHis.cpp'
    mv AnaEx01.root ../../gamma_ana/sim_eff2408/${run}AnaEx01.root

    cd ../../gamma_ana
    python3 ./src/sim_eff_rundemo.py ${run}

    echo ${run} 'keV simulation done'
done

# python3 ./src/plot_eff_demo.py