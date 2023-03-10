#include "ListsUGraph.h"

#include <fstream>
#include <future>
#include <algorithm>

void ListsUGraph::_create_list(){

    auto start=std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < n_nodes; i++){
        
        std::vector<size_t> row;

        lists.push_back(std::pair<std::vector<size_t>,bool>(row,false));
    }

    for(auto edge:edges){
        
        size_t i=edge.first;
        size_t j=edge.second;

        lists.at(i).first.push_back(j);
        lists.at(j).first.push_back(i);
    }
    
    auto stop=std::chrono::high_resolution_clock::now();
    auto elapsed=std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    construction_time=elapsed.count();
}

ListsUGraph::ListsUGraph(std::string dirname):UndirectedGraph(dirname){
    _create_list();
}

ListsUGraph::ListsUGraph(UndirectedGraph ug) :UndirectedGraph(ug){
    _create_list();
}

void ListsUGraph::print_row(size_t row){
    
    for (auto j: lists.at(row).first){
        std::cout << j << ' ';
    } 
    
}

void ListsUGraph::print_graph(bool to_file){
    
    if(!to_file){

        for (size_t i = 0; i < n_nodes; i++){

            std::cout<<"["<<i<<"]: ";

            for (auto j: lists.at(i).first){
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

            for (auto j: lists.at(i).first){
                file << j << ' ';
            }

            file<<std::endl;
        }
        
        file << std::endl;
    }
}

size_t ListsUGraph::get_construction_time(){
    return construction_time;
}

size_t ListsUGraph::_count_triangles(ListsUGraph *g, size_t id, size_t skip){

    int n_triangles=0;

    for (size_t j = id; j < g->edges.size(); j+=skip){

        auto edge=g->edges[j];

        size_t a=edge.first;
        size_t b=edge.second;

        std::vector<size_t> c;


        std::vector<size_t> a_vec=g->lists.at(a).first;
        std::vector<size_t> b_vec=g->lists.at(b).first;

        if(!g->lists.at(a).second){
            sort(a_vec.begin(),a_vec.end());
            g->lists.at(a).second=true;

            for (size_t i = 0; i < a_vec.size(); i++)
            {
                if(a_vec[i]!=g->lists.at(a).first[i]){
                    std::cout<<"ops";
                }
            }
            
        }

        if(!g->lists.at(b).second){
            sort(b_vec.begin(),b_vec.end());
            g->lists.at(b).second=true;
        }

        set_intersection(a_vec.begin(),a_vec.end(),b_vec.begin(),b_vec.end(),back_inserter(c));

        n_triangles+=c.size();
    }
    
    return n_triangles;
}

std::pair<size_t,size_t> ListsUGraph::count_triangles(){
    auto start=std::chrono::high_resolution_clock::now();

    size_t n_triangles=_count_triangles(this)/3;

    auto stop=std::chrono::high_resolution_clock::now();
    auto elapsed=std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    return std::pair<size_t,size_t>(n_triangles,elapsed.count());
}


std::pair<size_t,size_t> ListsUGraph::count_triangles_multi(size_t n_threads){

    auto start=std::chrono::high_resolution_clock::now();

    std::future<size_t> future[n_threads]; 
    
    for (size_t i = 0; i < n_threads; i++){
        future[i]=std::async(std::launch::async,_count_triangles,this,i,n_threads);
    }

    size_t n_triangles=0;
    
    for (size_t i = 0; i < n_threads; i++){
        n_triangles+=future[i].get();
    }

    n_triangles=n_triangles/3;

    auto stop=std::chrono::high_resolution_clock::now();
    auto elapsed=std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    return std::pair<size_t,size_t>(n_triangles,elapsed.count());
}