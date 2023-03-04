#include <vector>
#include <iostream>

using namespace std;


class TriangularMatrix{
    private:
        size_t size; //actual size

        vector<vector<bool>> matrix;
    public:
        TriangularMatrix(size_t size); //empty triangular matrix
        void print_row(int i);
        void pretty_print();
        void insert_modify(size_t i, size_t j, bool val);

};

TriangularMatrix::TriangularMatrix(size_t size){

    this->size=size-1;

    for (size_t i = 0; i < this->size; i++){
        
        vector<bool> row;
        row.insert(row.begin(),this->size-i,0);

        matrix.push_back(row);
    }
}

void TriangularMatrix::print_row(int row){
    
    for (auto j: matrix.at(row)){
        cout << j << ' ';
    } 
    
}

void TriangularMatrix::pretty_print(){
    for (size_t i = 0; i < this->size; i++){

        for (size_t k=0; k<this->size-matrix[i].size()+1; k++){
            cout<<"* ";
        }

        for (auto j: matrix.at(i)){
            cout << j << ' ';
        }
        cout<<endl;
    }

    for (size_t i = 0; i < this->size+1; i++){
        cout<<"* ";
    }

    cout << endl;
}

void TriangularMatrix::insert_modify(size_t i, size_t j, bool val=1){

    if (i<j)
        this->matrix.at(i).at(j-i-1)=val;
    else
        this->matrix.at(j).at(i-j-1)=val;
}