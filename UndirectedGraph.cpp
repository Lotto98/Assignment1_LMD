#include <vector>
#include <iostream>
#include "TriangularMatrix.cpp"

using namespace std;

class UndirectedGraph
{
private:
    TriangularMatrix* graph;
    //vector<tuple<int,int>> file; 
public:
    UndirectedGraph(string filename);
};

UndirectedGraph::UndirectedGraph(string filename){
    this->graph=new TriangularMatrix(5);

    this->graph->pretty_print();
    this->graph->insert_modify(2,3);
    this->graph->pretty_print();
}

int main(int argc, char const *argv[])
{
    auto si=UndirectedGraph("ciao");

    return 0;
}