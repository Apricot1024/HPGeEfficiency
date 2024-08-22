#! /bin/zsh

cd /home/apricot/Documents/Science/HPGe_Geant4/workdir/run0808/rootfile/
g++ ./efficency.cpp -o efficency `root-config --cflags --libs`
./efficency
# echo 'succeed' ${i}
