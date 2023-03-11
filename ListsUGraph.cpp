#include "ListsUGraph.h"

#include <fstream>
#include <future>
#include <algorithm>

void ListsUGraph::_create_list(){
    auto start=std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < n_nodes; i++){
        
        std::vector<unsigned long long> row;

        lists.push_back(row);
    }

    for(auto edge:edges){
        
        size_t i=edge.first;
        size_t j=edge.second;

        lists.at(i).push_back(j);
        lists.at(j).push_back(i);
    }
    
    auto stop=std::chrono::high_resolution_clock::now();
    auto elapsed=std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    construction_time=elapsed.count();
}

ListsUGraph::ListsUGraph(std::string dirname):UndirectedGraph(dirname){
    _create_list();
}

ListsUGraph::ListsUGraph(UndirectedGraph ug):UndirectedGraph(ug){
    _create_list();
}

void ListsUGraph::print_row(size_t row){
    
    for (auto j: lists.at(row)){
        std::cout << j << ' ';
    } 
    
}

void ListsUGraph::print_graph(bool to_file){
    
    if(!to_file){

        for (size_t i = 0; i < n_nodes; i++){

            std::cout<<"["<<i<<"]: ";

            for (auto j: lists.at(i)){
                std::cout << j << ' ';
            }

            std::cout<<std::endl;
        }

        std::cout << std::endl;
    }
    else{
        std::ofstream file("graph_print.txt");

        for (size_t i = 0; i < n_nodes; i++){

            file<<"["<<i<<"]: ";

            for (auto j: lists.at(i)){
                file << j << ' ';
            }

            file<<std::endl;
        }
        
        file << std::endl;
    }
}

unsigned long long ListsUGraph::get_construction_time(){
    return construction_time;
}

unsigned long long ListsUGraph::_count_triangles(ListsUGraph *g, size_t id, size_t skip){

    unsigned long long n_triangles=0;

    for (size_t j = id; j < g->edges.size(); j+=skip){

        size_t a=g->edges[j].first;
        size_t b=g->edges[j].second;

        std::vector<size_t> c;

        set_intersection(g->lists.at(a).begin(),g->lists.at(a).end(),
                            g->lists.at(b).begin(),g->lists.at(b).end(),
                            back_inserter(c));

        n_triangles+=c.size();
    }
    
    return n_triangles;
}

void ListsUGraph::_sort(ListsUGraph *g, size_t id, size_t skip){
    for (size_t j = id; j < g->lists.size(); j+=skip){
        std::sort(g->lists.at(j).begin(),g->lists.at(j).end());
    }
}

std::pair<unsigned long long,unsigned long long> ListsUGraph::count_triangles(){
    auto start=std::chrono::high_resolution_clock::now();

    _sort(this);

    unsigned long long n_triangles=_count_triangles(this)/3;

    auto stop=std::chrono::high_resolution_clock::now();
    auto elapsed=std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    return std::pair<unsigned long long,unsigned long long>(n_triangles,elapsed.count());
}


std::pair<unsigned long long,unsigned long long> ListsUGraph::count_triangles_multi(size_t n_threads){

    auto start=std::chrono::high_resolution_clock::now();

    //List sorting
    std::vector<std::thread> threads(n_nodes);

    for (size_t i = 0; i < n_threads; i++){
        threads[i]=std::thread(_sort,this,i,n_threads);
    }

    for (size_t i = 0; i < n_threads; i++){
        threads[i].join();
    }
    
    //Triangle counting
    std::future<unsigned long long> future[n_threads]; 

    for (size_t i = 0; i < n_threads; i++){
        future[i]=std::async(std::launch::async,_count_triangles,this,i,n_threads);
    }

    unsigned long long n_triangles=0;
    
    for (size_t i = 0; i < n_threads; i++){
        n_triangles+=future[i].get();
    }

    n_triangles/=3;

    auto stop=std::chrono::high_resolution_clock::now();
    auto elapsed=std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    return std::pair<unsigned long long,unsigned long long>(n_triangles,elapsed.count());
}