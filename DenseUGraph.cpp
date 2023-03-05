#include "DenseUGraph.h"

DenseUGraph::DenseUGraph(string filename): UndirectedGraph(filename){

    size=n_nodes-1;

    for (size_t i = 0; i < this->size; i++){
        
        vector<bool> row;
        row.insert(row.begin(),this->size-i,0);

        triangular_matrix.push_back(row);
    }

    for(auto edge:edges){
        
        size_t i=edge.first;
        size_t j=edge.second;

        if (i<j)
            triangular_matrix.at(i).at(j-i-1)=1;
        else
            triangular_matrix.at(j).at(i-j-1)=1;
    }
}

void DenseUGraph::print_row(size_t row){
    
    for (auto j: triangular_matrix.at(row)){
        cout << j << ' ';
    } 
    
}

void DenseUGraph::print_graph(bool to_file){
    
    if(!to_file){

        for (size_t i = 0; i < this->size; i++){

            for (size_t k=0; k<this->size-triangular_matrix[i].size()+1; k++){
                cout<<"* ";
            }

            for (auto j: triangular_matrix.at(i)){
                cout << j << ' ';
            }
            cout<<endl;
        }

        for (size_t i = 0; i < this->size+1; i++){
            cout<<"* ";
        }

        cout << endl;
    }
    else{
        ofstream file("graph_print.txt");

        for (size_t i = 0; i < this->size; i++){

            for (size_t k=0; k<this->size-triangular_matrix[i].size()+1; k++){
                file<<"* ";
            }

            for (auto j: triangular_matrix.at(i)){
                file << j << ' ';
            }
            file<<endl;
        }

        for (size_t i = 0; i < this->size+1; i++){
            file<<"* ";
        }

        file << endl;
    }
}

bool inline DenseUGraph::check(size_t a, size_t b){


    if(a==b || a<0 || b<0 || a>size || b>size){
        cerr<<"invalid indexes: "<<a<<","<<b<<endl;
        return false;
    }

    bool to_return;

    if (a<b)
        to_return=triangular_matrix.at(a).at(b-a-1);
    else
        to_return=triangular_matrix.at(b).at(a-b-1);

    return to_return;
}

size_t DenseUGraph::_count_triangles(DenseUGraph *g, size_t id, size_t skip){

    int n_triangles=0;

    for (size_t j = id; j < g->edges.size(); j+=skip){

        auto edge=g->edges[j];

        for (size_t i = 0; i <= g->size; i++){

            if (edge.first!=i && edge.second!=i && 
                    g->check(edge.first,i) && 
                    g->check(edge.second,i) ){

                n_triangles++;
            }
        }
    }
    
    return n_triangles;
}

pair<size_t,size_t> DenseUGraph::count_triangles(){
    auto start=chrono::high_resolution_clock::now();

    size_t t=_count_triangles(this)/3;

    auto stop=chrono::high_resolution_clock::now();
    auto elapsed=chrono::duration_cast<chrono::milliseconds>(stop-start);

    return make_pair(t,elapsed.count());
}

pair<size_t,size_t> DenseUGraph::count_triangles_multi(size_t n_threads){

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