#include <iostream>
#include <algorithm>
#include <stack>
#include <math.h>
#include <memory>
using namespace std;
const int k=2;
#ifndef KDTREE_H
#include "kdtree.h"
#endif
int main()
{   
    vectordata<double,int>set[100]; //build empty set
    //测试分到另一个文件，clangformat，*template*，内存，智能指针（sharedptr，uniqueptr）基于模板
    //socket programming通信库，Epoll，kubenetes

    double x, y;
    int id = 0;
    set[0].number[0] = 3;
    set[0].number[1] = 6;
    set[1].number[0] = 17;
    set[1].number[1] = 15;
    set[2].number[0] = 13;
    set[2].number[1] = 15;
    set[3].number[0] = 6;
    set[3].number[1] = 12;
    set[4].number[0] = 9;
    set[4].number[1] = 1;
    set[5].number[0] = 2;
    set[5].number[1] = 7;
    set[6].number[0] = 10;
    set[6].number[1] = 19; //input set value
    id = 7;                //total number of set

    //cout<<id;
    //struct Tnode<double,int> *root = NULL;
    shared_ptr<Tnode<double,int>> root(new Tnode<double,int>) ;
    root = build_kdtree<double,int>(set, id, root);

    double point1[] = {0, 6}; //a new set

    insertnew<double,int>(root, point1, set, id);//insert new data

    //test
    cout << set[7].number[0] << set[7].number[1] << "\n";
    cout << set[6].number[0] << set[6].number[1] << "\n";
    (search<double,int>(root, point1)) ? cout << "Found\n" : cout << "Not Found\n";

    root = deleteNode<double,int>(root, point1);
    id = deletedata<double,int>(set, point1, id); //delete
    
    root = NULL;
    root=build_kdtree(set, id, root);//update

    //test
    (search<double,int>(root, point1)) ? cout << "Found\n" : cout << "Not Found\n";
    cout << root->left->left->da.number[0] << root->left->left->da.number[1] << "\n";
    cout << root->split << "\n";
    cout << id;
}