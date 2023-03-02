#include <vector>
#include <array>
#include <iostream>

using namespace std;

#define N 10

int main(int argc, char const *argv[])
{
    array<vector<int>, N> matrix;

    for (size_t i = 0; i < N; i++)
    {
        matrix[i].insert(matrix[i].begin(),N-i,0);
    }

    for (size_t i = 0; i < N; i++)
    {
        for (auto j: matrix[i]){
            cout << j << ' ';
        }
        cout<<endl;
    }

    return 0;
}