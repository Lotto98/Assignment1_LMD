#include "SparseUGraph.h"
#include <algorithm>

SparseUGraph::SparseUGraph(string filename): UndirectedGraph(filename){

    for (size_t i = 0; i < n_nodes; i++){
        
        vector<size_t> row;

        v.push_back(row);
    }

    for(auto edge:edges){
        
        size_t i=edge.first;
        size_t j=edge.second;

        v.at(i).push_back(j);
        v.at(j).push_back(i);
    }

    for(auto e:v){
        sort(e.begin(),e.end());
    }
}

void SparseUGraph::print_row(size_t row){
    
    for (auto j: v.at(row)){
        cout << j << ' ';
    } 
    
}

void SparseUGraph::print_graph(bool to_file){
    
    if(!to_file){

        for (size_t i = 0; i < n_nodes; i++){

            cout<<"["<<i<<"]: ";

            for (auto j: v.at(i)){
                cout << j << ' ';
            }

            cout<<endl;
        }

        cout << endl;
    }
    else{
        ofstream file("graph_print.txt");

        for (size_t i = 0; i < n_nodes; i++){

            file<<"["<<i<<"]: ";

            for (auto j: v.at(i)){
                file << j << ' ';
            }

            file<<endl;
        }
        
        file << endl;
    }
}


bool SparseUGraph::check(size_t a, size_t b){


    if(a==b || a<0 || b<0 || a>n_nodes || a>n_nodes){
        cerr<<"invalid indexes: "<<a<<","<<b<<endl;
        return false;
    }

    return find(v.at(b).begin(), v.at(b).end(), a) != v.at(b).end() && 
        find(v.at(a).begin(), v.at(a).end(), b) != v.at(a).end();
}

size_t SparseUGraph::_count_triangles(SparseUGraph *g, size_t id, size_t skip){

    int n_triangles=0;

    for (size_t j = id; j < g->edges.size(); j+=skip){

        auto edge=g->edges[j];

        size_t a=edge.first;
        size_t b=edge.second;

        vector<size_t> c;
        set_intersection(g->v.at(a).begin(),g->v.at(a).end(),g->v.at(b).begin(),g->v.at(b).end(),back_inserter(c));

        n_triangles+=c.size();

    }
    
    return n_triangles;
}

pair<size_t,size_t> SparseUGraph::count_triangles(){
    auto start=chrono::high_resolution_clock::now();

    size_t t=_count_triangles(this)/3;

    auto stop=chrono::high_resolution_clock::now();
    auto elapsed=chrono::duration_cast<chrono::milliseconds>(stop-start);

    return make_pair(t,elapsed.count());
}


pair<size_t,size_t> SparseUGraph::count_triangles_multi(size_t n_threads){

    auto start=chrono::high_resolution_clock::now();

    future<size_t> future[n_threads]; 
    
    for (size_t i = 0; i < n_threads; i++){
        future[i]=async(launch::async,_count_triangles,this,i,n_threads);
    }

    size_t n_triangles=0;
    
    for (size_t i = 0; i < n_threads; i++){
        n_triangles+=future[i].get();
    }

    n_triangles=n_triangles/3;

    auto stop=chrono::high_resolution_clock::now();
    auto elapsed=chrono::duration_cast<chrono::milliseconds>(stop-start);

    return make_pair(n_triangles,elapsed.count());
}