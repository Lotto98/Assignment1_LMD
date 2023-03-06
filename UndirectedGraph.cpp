#include <sstream>
#include "UndirectedGraph.h"

UndirectedGraph::UndirectedGraph(string dirname){

    string line; //buffer

    //read n nodes
    ifstream nodes_file("data/"+dirname+"/nodes.txt");
    getline(nodes_file, line);

    istringstream ss_nodes(line);
    ss_nodes>>n_nodes;

    nodes_file.close();
    
    //read edges
    ifstream edges_file("data/"+dirname + "/edges.txt");

    this->n_edges=0;

    while( getline (edges_file, line) ){
        
        istringstream ss_edges(line);
        
        size_t a,b;
        ss_edges>> a;
        ss_edges>> b;

        edges.push_back(pair<size_t,size_t>(a,b));

        this->n_edges++;

    }

    edges_file.close();

    //read n triangles
    ifstream triangles_file("data/"+dirname+"/triangle.txt");
    getline(triangles_file, line);

    istringstream ss_triangles(line);
    ss_triangles>>true_n_triangles;

    triangles_file.close();
}

void UndirectedGraph::print_edges(){
    for (auto j: edges){
        cout << j.first <<' '<< j.second << endl;
    } 
}

void UndirectedGraph::print_variables(){
    
    cout<<"N° of edges "<<this->n_edges<<endl;
    cout<<"N° of nodes "<<this->n_nodes<<endl;
    cout<<"N° of triangles "<<this->true_n_triangles<<endl;

    cout<<"Density: "<<double(2*n_edges)/double(n_nodes*(n_nodes-1))<<endl<<endl;
}