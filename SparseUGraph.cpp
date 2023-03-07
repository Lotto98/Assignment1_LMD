#include "SparseUGraph.h"
#include <algorithm>

SparseUGraph::SparseUGraph(string filename): UndirectedGraph(filename){

    auto start=chrono::high_resolution_clock::now();

    for (size_t i = 0; i < n_nodes; i++){
        
        vector<size_t> row;

        v.push_back(make_pair(row,false));
    }

    for(auto edge:edges){
        
        size_t i=edge.first;
        size_t j=edge.second;

        v.at(i).first.push_back(j);
        v.at(j).first.push_back(i);
    }
    
    auto stop=chrono::high_resolution_clock::now();
    auto elapsed=chrono::duration_cast<chrono::milliseconds>(stop-start);

    construction_time=elapsed.count();
}

void SparseUGraph::print_row(size_t row){
    
    for (auto j: v.at(row).first){
        cout << j << ' ';
    } 
    
}

void SparseUGraph::print_graph(bool to_file){
    
    if(!to_file){

        for (size_t i = 0; i < n_nodes; i++){

            cout<<"["<<i<<"]: ";

            for (auto j: v.at(i).first){
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

            for (auto j: v.at(i).first){
                file << j << ' ';
            }

            file<<endl;
        }
        
        file << endl;
    }
}

size_t SparseUGraph::get_construction_time(){
    return construction_time;
}

size_t SparseUGraph::_count_triangles(SparseUGraph *g, size_t id, size_t skip){

    int n_triangles=0;

    for (size_t j = id; j < g->edges.size(); j+=skip){

        auto edge=g->edges[j];

        size_t a=edge.first;
        size_t b=edge.second;

        vector<size_t> c;

        vector<size_t> a_vec=g->v.at(a).first;
        vector<size_t> b_vec=g->v.at(b).first;

        if(!g->v.at(a).second){
            sort(a_vec.begin(),a_vec.end());
            g->v.at(a).second=true;
        }

        if(!g->v.at(b).second){
            sort(b_vec.begin(),b_vec.end());
            g->v.at(b).second=true;
        }

        set_intersection(a_vec.begin(),a_vec.end(),b_vec.begin(),b_vec.end(),back_inserter(c));

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