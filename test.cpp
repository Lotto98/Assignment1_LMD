//#include "MatrixUGraph.h"
#include "ListsUGraph.h"

#include <iostream>
#include <fstream>

#define N_THREADS 20
#define N_ITERATION 2

void to_txt(unsigned long long construction_times[N_THREADS],
            unsigned long long algorithm_times[N_THREADS],
            std::string graph_name){

    std::ofstream file_const("results/"+graph_name+"_construction"+".txt");
    
    for (size_t i = 0; i < N_THREADS; i++){
        
        file_const << construction_times[i] << ' ';
    }

    std::ofstream file_algo("results/"+graph_name+"_algo"+".txt");
    
    for (size_t i = 0; i < N_THREADS; i++){
        
        file_algo << algorithm_times[i] << ' ';
    }
    
}

void test_lists(std::string graph_name){

    std::cout<<graph_name<<std::endl;

    ListsUGraph ug(graph_name);
    ug.print_variables();

    unsigned long long triangles,construction_time,algorithm_time;
    unsigned long long construction_times[N_THREADS]={0};
    unsigned long long algorithm_times[N_THREADS]={0};
    
    for (size_t j = 0; j < N_ITERATION; j++){

        std::cout <<"Iteration "<<j<<std::endl;

        std::tie(triangles,construction_time,algorithm_time)=ug.count_triangles();

        construction_times[0]+=construction_time;
        algorithm_times[0]+=algorithm_time;
        
        std::cout <<"N° triangles single core: "<<triangles <<std::endl;

        for (unsigned int i = 2; i <= N_THREADS; i++){

            std::tie(triangles,construction_time,algorithm_time)=ug.count_triangles_multi(i);

            construction_times[i-1]+=construction_time;
            algorithm_times[i-1]+=algorithm_time;

            std::cout <<"N° triangles "<<i<<" threads: "<<triangles <<std::endl;
        }
        std::cout<<std::endl;
    }
    
    std::cout<<std::endl;
    
    for (size_t i = 0; i < N_THREADS; i++){
        construction_times[i]=construction_times[i]/N_ITERATION;
        algorithm_times[i]=algorithm_times[i]/N_ITERATION;

        if (i==0) std::cout<<"*** Single core ***"<<std::endl<<std::endl;
        if(i==1) std::cout<<"*** Multi core ***"<<std::endl<<std::endl;

        std::cout<<"N° threads: "<<i+1<<std::endl;
        std::cout<<"Construction elapsed time: "<< construction_times[i] <<"ms or "<<double(construction_times[i])/1000.0<<"s"<<std::endl;
        std::cout <<"Triangle counting elapsed time: "<< algorithm_times[i] <<"ms or "<<double(algorithm_times[i])/1000.0<<"s"<<std::endl;
        std::cout <<"Total elapsed time: "<< algorithm_times[i]+construction_times[i] <<"ms or "<<double(algorithm_times[i]+construction_times[i])/1000.0<<"s"<<std::endl;
        std::cout<<std::endl;
    }
    std::cout<<std::endl<<std::endl;

    to_txt(construction_times,algorithm_times,graph_name);
}

/*void test_matrix(string graph_name){

    UndirectedGraph ug(graph_name);
    ug.print_variables();

    unsigned long long triangles,elapsed,construction;
    
    {
    cout<<"*** Single core ***"<<endl<<endl;

    MatrixUGraph dg(ug);

    construction=dg.get_construction_time();

    tie(triangles,elapsed)=dg.count_triangles();
    
    cout <<"N° triangles: "<<triangles <<endl;

    cout<<"Construction elapsed time: "<< construction <<"ms or "<<double(construction)/1000.0<<"s"<<endl;
    cout <<"Triangle counting elapsed time: "<< elapsed <<"ms or "<<double(elapsed)/1000.0<<"s"<<endl;

    cout <<"Total elapsed time: "<< elapsed+construction <<"ms or "<<double(elapsed+construction)/1000.0<<"s"<<endl;

    cout<<endl;
    }

    cout<<"*** Multi core ***"<<endl<<endl;

    for (unsigned int i = 2; i <= 20; i++){
        
        cout <<"N° threads: "<<i<<endl;

        MatrixUGraph dg(ug);

        construction=dg.get_construction_time();

        tie(triangles,elapsed)=dg.count_triangles_multi(i);

        cout <<"N° triangles: "<<triangles <<endl;

        cout<<"Construction elapsed time: "<< construction <<"ms or "<<double(construction)/1000.0<<"s"<<endl;
        cout <<"Triangle counting elapsed time: "<< elapsed <<"ms or "<<double(elapsed)/1000.0<<"s"<<endl;

        cout <<"Total elapsed time: "<< elapsed+construction <<"ms or "<<double(elapsed+construction)/1000.0<<"s"<<endl;

        cout<<endl;
    }
}*/

int main(int argc, char const *argv[])
{

    std::string graph_names[]={"facebook","4039_dense_graph","45100_sparse_graph"};

    for (size_t i = 0; i < 3; i++){
        test_lists(graph_names[i]);
    }

    //ListsUGraph g("facebook");
    //g.count_triangles();
    
    //test_matrix("4039_dense_graph");
    return 0;
}