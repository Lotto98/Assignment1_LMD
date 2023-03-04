#include <vector>
#include <iostream>

using namespace std;

class NodeLists
{
private:
    vector<vector<int>> list_of_lists;
public:
    NodeLists();
    void Init(size_t size);
    void insert(size_t index, int val);
    void print();
};

NodeLists::NodeLists(){}

void NodeLists::Init(size_t size){
    for (size_t i = 0; i < size; i++){
        vector<int> list;
        list_of_lists.push_back(list);
    }
}

void NodeLists::insert(size_t index, int val){
    list_of_lists[index].push_back(val);
    //to sort???
}

void NodeLists::print(){
    size_t index=0;
    for (auto v:list_of_lists){
        cout<<"["<<index<<"]: ";
        index++;

        for(auto elem:v){
            cout<<elem<<' ';
        }
        cout<<endl;
    }
}


