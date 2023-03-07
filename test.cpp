#include <chrono>
#include <iostream>
#include <tuple>
#include <thread>

#include "DenseUGraph.h"
#include "SparseUGraph.h"

using namespace std;

void test_dense(string filename){

    size_t triangles,elapsed_single,elapsed;

    DenseUGraph dg(filename);
    dg.print_variables();

    cout<<"*** Single core ***"<<endl<<endl;

    tie(triangles,elapsed_single)=dg.count_triangles();
    
    cout <<"N° triangles: "<<triangles <<endl;

    cout <<"Elapsed: "<< elapsed_single <<"ms or "<<double(elapsed_single)/1000.0<<"s"<<endl;

    cout<<endl;

    cout<<"*** Multi core ***"<<endl<<endl;

    for (unsigned int i = 1; i <= thread::hardware_concurrency(); i++){
        
        cout <<"N° threads: "<<i<<endl;

        tie(triangles,elapsed)=dg.count_triangles_multi(i);
        
        cout <<"N° triangles: "<<triangles <<endl;

        cout <<"Elapsed: "<< elapsed <<"ms or "<<double(elapsed)/1000.0<<"s"<<endl;

        if(i==1 && elapsed>elapsed_single){
            cout<<"Overhead: "<<elapsed-elapsed_single<<"ms"<<endl;
        }

        cout<<endl;
    }
}

void test_sparse(string filename){

    size_t triangles,elapsed_single,elapsed;

    SparseUGraph dg(filename);
    dg.print_variables();

    dg.print_graph(true);

    cout<<"*** Single core ***"<<endl<<endl;

    tie(triangles,elapsed_single)=dg.count_triangles();
    
    cout <<"N° triangles: "<<triangles <<endl;

    cout <<"Elapsed: "<< elapsed_single <<"ms or "<<double(elapsed_single)/1000.0<<"s"<<endl;

    cout<<endl;

    
    cout<<"*** Multi core ***"<<endl<<endl;

    for (unsigned int i = 1; i <= thread::hardware_concurrency(); i++){
        
        cout <<"N° threads: "<<i<<endl;

        tie(triangles,elapsed)=dg.count_triangles_multi(i);
        
        cout <<"N° triangles: "<<triangles <<endl;

        cout <<"Elapsed: "<< elapsed <<"ms or "<<double(elapsed)/1000.0<<"s"<<endl;

        if(i==1 && elapsed>elapsed_single){
            cout<<"Overhead: "<<elapsed-elapsed_single<<"ms"<<endl;
        }

        cout<<endl;
    }
}

int main(int argc, char const *argv[])
{
    //test_sparse("4039_dense_graph");
    test_dense("4039_dense_graph");
    return 0;
}