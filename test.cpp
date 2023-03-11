//#include "MatrixUGraph.h"
#include "ListsUGraph.h"
#include <tuple>
#include <fstream>

using namespace std;

#define N_THREADS 20

void to_txt(unsigned long long exec_times[N_THREADS],string graph_name){
    ofstream file("results/"+graph_name+".txt");
    
    for (size_t i = 0; i < N_THREADS; i++){
        
        file << exec_times[i] << ' ';
    }
    
}

void test_lists(string graph_name){

    cout<<graph_name<<endl;

    UndirectedGraph ug(graph_name);
    ug.print_variables();

    unsigned long long triangles,elapsed,construction;

    unsigned long long exec_times[N_THREADS];
    
    {
    cout<<"*** Single core ***"<<endl<<endl;

    ListsUGraph dg(ug);

    construction=dg.get_construction_time();

    tie(triangles,elapsed)=dg.count_triangles();
    
    cout <<"N° triangles: "<<triangles <<endl;

    cout<<"Construction elapsed time: "<< construction <<"ms or "<<double(construction)/1000.0<<"s"<<endl;
    cout <<"Triangle counting elapsed time: "<< elapsed <<"ms or "<<double(elapsed)/1000.0<<"s"<<endl;

    cout <<"Total elapsed time: "<< elapsed+construction <<"ms or "<<double(elapsed+construction)/1000.0<<"s"<<endl;

    cout<<endl;

    exec_times[0]=elapsed+construction;
    }

    cout<<"*** Multi core ***"<<endl<<endl;

    for (unsigned int i = 2; i <= N_THREADS; i++){
        
        cout <<"N° threads: "<<i<<endl;

        ListsUGraph dg(ug);

        construction=dg.get_construction_time();

        tie(triangles,elapsed)=dg.count_triangles_multi(i);

        cout <<"N° triangles: "<<triangles <<endl;

        cout<<"Construction elapsed time: "<< construction <<"ms or "<<double(construction)/1000.0<<"s"<<endl;
        cout <<"Triangle counting elapsed time: "<< elapsed <<"ms or "<<double(elapsed)/1000.0<<"s"<<endl;

        cout <<"Total elapsed time: "<< elapsed+construction <<"ms or "<<double(elapsed+construction)/1000.0<<"s"<<endl;

        cout<<endl;

        exec_times[i-1]=elapsed+construction;
    }

    to_txt(exec_times,graph_name);
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
    string graph_names[]={"4039_dense_graph","45100_sparse_graph","facebook"};

    for (size_t i = 0; i < 3; i++){
        test_lists(graph_names[i]);
    }
    
    //test_matrix("4039_dense_graph");
    return 0;
}