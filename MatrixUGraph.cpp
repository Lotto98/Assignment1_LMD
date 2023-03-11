#include "MatrixUGraph.h"

#include <fstream>
#include <chrono>
#include <future>

void MatrixUGraph::_create_matrix(){

    auto start=std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < n_nodes; i++){
        
        std::vector<bool> row;
        row.insert(row.begin(),n_nodes,0);

        matrix.push_back(row);
    }

    for(auto edge:edges){
        
        size_t i=edge.first;
        size_t j=edge.second;

        matrix.at(i).at(j)=true;
    }

    auto stop=std::chrono::high_resolution_clock::now();
    auto elapsed=std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    construction_time=elapsed.count();
}

MatrixUGraph::MatrixUGraph(std::string dirname): UndirectedGraph(dirname){

    _create_matrix();
}

MatrixUGraph::MatrixUGraph(UndirectedGraph ug): UndirectedGraph(ug){

    _create_matrix();
}

void MatrixUGraph::print_row(size_t row){
    
    for (auto j: matrix.at(row)){
        std::cout << j << ' ';
    } 
    
}

void MatrixUGraph::print_graph(bool to_file){
    
    if(!to_file){

        for (auto row:matrix){

            for (auto elem: row){
                std::cout << elem << ' ';
            }
            std::cout<<std::endl;
        }

        std::cout << std::endl;
    }
    else{
        std::ofstream file("graph_print.txt");

        for (auto row:matrix){

            for (auto elem: row){
                file << elem << ' ';
            }
            file<<std::endl;
        }

        file << std::endl;
    }
}

unsigned long long MatrixUGraph::get_construction_time(){
    return construction_time;
}

void MatrixUGraph::_count_triangles(MatrixUGraph *g, std::vector<std::vector<int>> mult3,size_t id, size_t skip){

    std::vector<std::vector<int>> mult2(g->n_nodes, std::vector<int> (g->n_nodes, 0));

    for(size_t i = id; i < g->n_nodes; i+=skip)
        for(size_t j = 0; j < g->n_nodes; ++j)
            for(size_t k = 0; k < g->n_nodes; ++k){
                mult2[i][j] += g->matrix[i][k] && g->matrix[k][j];
            }
    
    for(size_t i = id; i < g->n_nodes; i+=skip)
        for(size_t j = 0; j < g->n_nodes; ++j)
            for(size_t k = 0; k < g->n_nodes; ++k){
                mult3[i][j] += g->matrix[i][k] * mult2[k][j];
            }
}

std::pair<unsigned long long,unsigned long long> MatrixUGraph::count_triangles(){
    
    auto start=std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> mult3(n_nodes, std::vector<int> (n_nodes, 0));

    _count_triangles(this,mult3);

    unsigned long long n_triangles=0;

    for (size_t i = 0; i < n_nodes; i++){
        n_triangles+=mult3[i][i];
    }

    auto stop=std::chrono::high_resolution_clock::now();
    auto elapsed=std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    return std::pair<unsigned long long,unsigned long long>(n_triangles/6,elapsed.count());
}

std::pair<unsigned long long,unsigned long long> MatrixUGraph::count_triangles_multi(size_t n_threads){

    auto start=std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> mult3;

    std::thread threads[n_threads];
    
    for (size_t i = 0; i < n_threads; i++){
        threads[i]=std::thread(_count_triangles,this,mult3,i,n_threads);
    }

    unsigned long long n_triangles=0;
    
    for (size_t i = 0; i < n_threads; i++){
        n_triangles+=mult3[i][i];
    }

    auto stop=std::chrono::high_resolution_clock::now();
    auto elapsed=std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    return std::pair<unsigned long long,unsigned long long>(n_triangles/6,elapsed.count());
}