#include <sstream>
#include <fstream>

#include "UndirectedGraph.h"

UndirectedGraph::UndirectedGraph(UndirectedGraph& g){

    //ref copy
    this->edges=g.edges;

    //copy
    this->n_edges=g.edges.size();
    this->n_nodes=g.n_nodes;
}

UndirectedGraph::UndirectedGraph(std::string dirname){

    std::string line; //buffer

    //read n nodes
    std::ifstream nodes_file("data/"+dirname+"/nodes.txt");
    getline(nodes_file, line);

    std::istringstream ss_nodes(line);
    ss_nodes>>n_nodes;

    nodes_file.close();
    
    //read edges
    std::ifstream edges_file("data/"+dirname + "/edges.txt");

    this->n_edges=0;

    while( getline (edges_file, line) ){
        
        std::istringstream ss_edges(line);
        
        size_t a,b;
        ss_edges>> a;
        ss_edges>> b;

        edges.push_back(std::pair<size_t,size_t>(a,b));

        this->n_edges++;

    }

    edges_file.close();

}

void UndirectedGraph::print_edges(){
    for (auto j: edges){
        std::cout << j.first <<' '<< j.second << std::endl;
    } 
}

void UndirectedGraph::print_variables(){
    
    std::cout<<"N° of edges "<<this->n_edges<<std::endl;
    std::cout<<"N° of nodes "<<this->n_nodes<<std::endl;

    std::cout<<"Density: "<<double(2*n_edges)/double(n_nodes*(n_nodes-1))<<std::endl<<std::endl;
}