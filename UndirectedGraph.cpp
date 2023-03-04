#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <future>
#include <thread>
#include "TriangularMatrix.cpp"

using namespace std;

class UndirectedGraph
{
private:
    TriangularMatrix graph;
    int n_nodes;
    int n_edges;
    int true_n_triangles;

    vector<pair<int,int>> edges;

    int static _count_triangles(UndirectedGraph *graph,size_t id=0, size_t skip=1);
public:
    UndirectedGraph(string filename);
    
    void print_edges();
    void print_graph();
    void print_variables();

    int count_triangles();
    int count_triangles_multi(size_t n_threads);
};

UndirectedGraph::UndirectedGraph(string dirname){

    string line; //buffer

    //read n nodes
    ifstream nodes_file(dirname+"/nodes.txt");
    getline(nodes_file, line);

    n_nodes=stoi(line);

    nodes_file.close();
    
    //cout<<n_nodes;
    this->graph.Init(n_nodes); //matrix init
    
    // read edges

    ifstream edges_file(dirname + "/edges.txt");

    this->n_edges=0;

    while( getline (edges_file, line) ){
        
        istringstream ss(line);
        
        string a;
        ss>> a;

        string b;
        ss>> b;

        try
        {
            graph.insert_modify(stoi(a),stoi(b));
        }
        catch(const std::exception& e)
        {
            cout<<a<<' '<<b<<' '<<graph.get_size()<<endl;
            
            break;
        }

        edges.push_back(pair<int,int>(stoi(a),stoi(b)));

        this->n_edges++;

    }

    edges_file.close();

    //read n triangles
    ifstream triangles_file(dirname+"/triangle.txt");
    getline(triangles_file, line);

    true_n_triangles=stoi(line);

    triangles_file.close();
}

void UndirectedGraph::print_edges(){
    for (auto j: edges){
        cout << j.first <<' '<< j.second << endl;
    } 
}

void UndirectedGraph::print_graph(){
    this->graph.pretty_print();
}

void UndirectedGraph::print_variables(){
    
    cout<<"N° of edges "<<this->n_edges<<endl;
    cout<<"N° of nodes "<<this->n_nodes<<endl;
    cout<<"N° of triangles "<<this->true_n_triangles<<endl;

    cout<<double(2*n_edges)/double(n_nodes*(n_nodes-1));
}

int UndirectedGraph::_count_triangles(UndirectedGraph *g, size_t id, size_t skip){

    int n_triangles=0;

    for (size_t j = id; j < g->edges.size(); j+=skip){

        auto edge=g->edges[j];

        //cout<<edge.first<<' '<<edge.second<<endl;
        for (size_t i = 0; i <= g->graph.get_size(); i++){

            //cout<<edge.first<<' '<<i<<endl;
            //cout<<edge.second<<' '<<i<<endl<<endl;

            if (edge.first!=i && edge.second!=i && 
                    g->graph.check(edge.first,i) && 
                    g->graph.check(edge.second,i) ){

                n_triangles++;
            }
        }
    }
    
    return n_triangles;
}

int UndirectedGraph::count_triangles(){
    return _count_triangles(this)/3;
}

int UndirectedGraph::count_triangles_multi(size_t n_threads){

    future<int> future[n_threads]; 
    
    for (size_t i = 0; i < n_threads; i++){
        future[i]=async(launch::async,_count_triangles,this,i,n_threads);
    }

    int n_triangles=0;
    
    for (size_t i = 0; i < n_threads; i++){
        n_triangles+=future[i].get();
    }

    return n_triangles/3;
}

int main(int argc, char const *argv[])
{
    UndirectedGraph ug("facebook");

    auto start=chrono::high_resolution_clock::now();
    int t=ug.count_triangles();
    auto stop=chrono::high_resolution_clock::now();

    auto elapsed=chrono::duration_cast<chrono::milliseconds>(stop-start);
    
    cout << t <<endl;

    cout <<"Elapsed: "<< elapsed.count() <<"ms or "<<double(elapsed.count())/1000.0<<"s"<<endl;


    start=chrono::high_resolution_clock::now();
    auto threads=thread::hardware_concurrency();
    cout<<threads<<endl;
    t=ug.count_triangles_multi(threads);
    stop=chrono::high_resolution_clock::now();

    elapsed=chrono::duration_cast<chrono::milliseconds>(stop-start);
    
    cout << t <<endl;

    cout <<"Elapsed: "<< elapsed.count() <<"ms or "<<double(elapsed.count())/1000.0<<"s"<<endl;

    ug.print_variables();

    return 0;
}

int main1(int argc, char const *argv[])
{
    auto n_nodes=4847571;
    auto n_edges=68993773;
    cout<<double(2*n_edges)/double(n_nodes*(n_nodes-1));
    return 0;
}