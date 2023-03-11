#include "MatrixUGraph.h"
#include "ListsUGraph.h"
#include <tuple>

using namespace std;

void test_lists(string filename){

    UndirectedGraph ug(filename);
    ug.print_variables();

    unsigned long long triangles,elapsed,construction;
    
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
    }

    cout<<"*** Multi core ***"<<endl<<endl;

    for (unsigned int i = 2; i <= 20; i++){
        
        cout <<"N° threads: "<<i<<endl;

        ListsUGraph dg(ug);

        construction=dg.get_construction_time();

        tie(triangles,elapsed)=dg.count_triangles_multi(i);

        cout <<"N° triangles: "<<triangles <<endl;

        cout<<"Construction elapsed time: "<< construction <<"ms or "<<double(construction)/1000.0<<"s"<<endl;
        cout <<"Triangle counting elapsed time: "<< elapsed <<"ms or "<<double(elapsed)/1000.0<<"s"<<endl;

        cout <<"Total elapsed time: "<< elapsed+construction <<"ms or "<<double(elapsed+construction)/1000.0<<"s"<<endl;

        cout<<endl;
    }
}

void test_matrix(string filename){

    UndirectedGraph ug(filename);
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
}

int main(int argc, char const *argv[])
{
    //test_lists("4039_dense_graph");
    test_matrix("facebook");
    return 0;
}