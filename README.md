# Minimum-Sum-Coloring
## Breif Introduction
### Directory Structure
├── alpha

├── comple.cpp

├── control.py

├── Graph

├── KPLEX.cpp

├── LB.cpp

├── MaxBG.cpp

├── Out

└── README.md

### Enviroment you need
* Linux(Suggest you to use Ubuntu)
* python3
* g++ with standard c++11
### How to use this solver
First, set enviroment:
```shell
sudo apt-get install g++
sudo apt-get install python3
```
After setting all the enviroment, compile all the cpp files:
```shell
g++ comple.cpp -o comple -O2 std=c++11
g++ KPLEX.cpp -o KPLEX -O2 std=c++11
g++ LB.cpp -o LB -O2 std=c++11
g++ MaxBG.cpp -o MaxBG std=c++11
```
And then, put your input file into *Graph* folder, your input file should be in the format of DIMACS.
After that, use *control.py* to get the maximum bipartite subgraph file in folder *Out*:
```shell
python3 control.py
```
Finally, you can use *LB* to calculate all four lower bounds mentioned in our paper.
