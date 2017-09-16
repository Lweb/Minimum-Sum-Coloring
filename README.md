# Minimum-Sum-Coloring
## Breif Introduction
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
And then, put your input file into *Graph* folder.
After that, use *control.py* to get the maximum bipartite subgraph file in folder *Out*:
```shell
python3 control.py
```
Finally, you can use *LB* to calculate all four lower bounds mentioned in our paper.
## Some precautions
### Format of your input file
You can download some wiedly used graph file from [this link](http://mat.gsia.cmu.edu/COLOR04/).
Our solver require input files in a format similar to the format of graph files downloaded from that link. To achieve our requirement, the only thing you need to do is to delete lines begin with a charater `c`.
For example, the graph *myciel3* can be found from [this link](http://mat.gsia.cmu.edu/COLOR04/INSTANCES/myciel3.col), with content:
```
c FILE: myciel3.col
c SOURCE: Michael Trick (trick@cmu.edu)
c DESCRIPTION: Graph based on Mycielski transformation. 
c              Triangle free (clique number 2) but increasing
c              coloring number
p edge 11 20
e 1 2
e 1 4
e 1 7
e 1 9
e 2 3
e 2 6
e 2 8
e 3 5
e 3 7
e 3 10
e 4 5
e 4 6
e 4 10
e 5 8
e 5 9
e 6 11
e 7 11
e 8 11
e 9 11
e 10 11
```
You suppose to delete all the lines begin with a character `c`:
```
p edge 11 20
e 1 2
e 1 4
e 1 7
e 1 9
e 2 3
e 2 6
e 2 8
e 3 5
e 3 7
e 3 10
e 4 5
e 4 6
e 4 10
e 5 8
e 5 9
e 6 11
e 7 11
e 8 11
e 9 11
e 10 11
```