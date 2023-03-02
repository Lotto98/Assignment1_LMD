#include <vector>
#include <array>
#include <iostream>

using namespace std;

#define N 5


class TriangularMatrix{
    private:
        size_t static const n=N-1; //actual size

        array<vector<bool>, n> matrix;
    public:
        TriangularMatrix(/* args */);
        void print_row(int i);
        void pretty_print();

};

TriangularMatrix::TriangularMatrix(/* args */){
    for (size_t i = 0; i < n; i++){
        matrix[i].insert(matrix[i].begin(),n-i,0);
    }
}

void TriangularMatrix::print_row(int row){
    if (row>n){
        throw invalid_argument( "received invalid row index" );
    }
    else{
        for (auto j: matrix[row]){
            cout << j << ' ';
        } 
    }
}

void TriangularMatrix::pretty_print(){
    for (size_t i = 0; i < n; i++){

        for (size_t k=0; k<n-matrix[i].size()+1; k++){
            cout<<"* ";
        }

        for (auto j: matrix[i]){
            cout << j << ' ';
        }
        cout<<endl;
    }

    for (size_t i = 0; i < N; i++){
        cout<<"* ";
    }    

    cout<<endl;
}


int main(int argc, char const *argv[])
{
    auto tm=TriangularMatrix();
    //tm.pretty_print();

    tm.print_row(-1);
    return 0;
}