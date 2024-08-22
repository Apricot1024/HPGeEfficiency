#! /bin/zsh
cd /home/apricot/Documents/Science/HPGe_Geant4/workdir/run0808/HPGeEfficency/build/
rm CMakeCache.txt
rm log*
cmake ..
make
for ((i=10; i<=10000; i+=1)); do
    # cd /home/apricot/Documents/Science/HPGe_Geant4/workdir/${i}egr/build
    ./exampleB1 ./macro/runuser${i}.mac > log${i}.txt
    # cp log${i}.txt ../../log/
    rm log*
    cp AnaEx01.root ../../rootfile/ana${i}.root
    echo 'succeed' ${i}
done