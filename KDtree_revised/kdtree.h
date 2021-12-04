#include <iostream>
#include <algorithm>
#include <stack>
#include <math.h>
#include <memory>
using namespace std;
#ifndef KDTREE_H
#define KDTREE_H

//const int k=i;//写成变量
template <class T, class T1>
struct vectordata 
{
    T number[k];
};
template <class T, class T1>
struct Tnode
{
    struct vectordata<T, T1> da;
    T1 split;
    struct shared_ptr<Tnode<T, T1>> left;
    struct shared_ptr<Tnode<T, T1>> right;
};
template <class T, class T1>
struct shared_ptr<Tnode<T, T1>> newnode(T arr[])
{
    struct shared_ptr<Tnode<T, T1>> temp(new Tnode<double, int>);
    for (int i = 0; i < k; i++)
        temp->da.number[i] = arr[i];
    temp->left = temp->right = NULL;
    temp->split = 0;
    return temp;
} template <class T, class T1>
void sorting(vectordata<T, T1> set[], T1 size, T1 &split)
{
    vectordata<T, T1> tmp;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = size - 1; j > i; j--)
        {
            if (set[j].number[split] < set[j - 1].number[split])
            {
                tmp = set[j];
                set[j] = set[j - 1];
                set[j - 1] = tmp;
            }
        }
    }

} //sort the vectordata set in an increasing order, consider the given dimension
template <class T, class T1>
bool equal(vectordata<T, T1> &a, vectordata<T, T1> &b) //常量引用，不用value
{
    for (int i = 0; i < k; i++)
    {
        if (a.number[i] != b.number[i])
        {
            return false;
        }
    }
    return true;
}
template <class T, class T1>
void ChooseSplit(vectordata<T, T1> set[], T1 size, T1 &split, vectordata<T, T1> &SplitChoice)
{

    double tmp1, tmp2;
    double v1, v2;
    tmp1 = tmp2 = 0;
    v1 = v2 = 0;
    split = 0;
    for (int j = 0; j < k; j++)
    {
        for (int i = 0; i < size; i++)
        {
            tmp1 += 1.0 / (double)size * set[i].number[j] * set[i].number[j];
            tmp2 += 1.0 / (double)size * set[i].number[j];
        }
        v1 = tmp1 - tmp2 * tmp2; //compute variance on the each dimension
        tmp1 = tmp2 = 0;
        if (v1 > v2)
        {
            split = j;
            v2 = v1;
        }

    }                                 //choose dimension with the largest variance
    sorting<T, T1>(set, size, split); //不要自己写排序

    //set the split point value
    for (int l = 0; l < k; l++)
    {
        SplitChoice.number[l] = set[size / 2].number[l];
    }
}
template <class T, class T1>
shared_ptr<Tnode<T, T1>> build_kdtree(vectordata<T, T1> set[], T1 size, shared_ptr<Tnode<T, T1>> Tn) //c++,模板参数template
{
    //call ChooseSplit to choose the dimension and split point
    if (size == 0)
    {
        return NULL;
    }
    else
    {
        int split;
        vectordata<T, T1> da;
        ChooseSplit(set, size, split, da);
        vectordata<T, T1> set_right[100];
        vectordata<T, T1> set_left[100];
        int sizeleft, sizeright;
        sizeleft = sizeright = 0;
        for (int i = 0; i < size; ++i)
        {

            if (!equal(set[i], da) && set[i].number[split] <= da.number[split])
            {
                for (int l = 0; l < k; l++)
                {
                    set_left[sizeleft].number[l] = set[i].number[l];
                }
                sizeleft++;
            }
            else if (!equal(set[i], da) && set[i].number[split] > da.number[split])
            {
                for (int l = 0; l < k; l++)
                {
                    set_right[sizeright].number[l] = set[i].number[l];
                }
                sizeright++;
            }
        }

        Tn.reset(new Tnode<T, T1>);
        for (int m = 0; m < k; m++)
        {
            Tn->da.number[m] = da.number[m];
        }
        Tn->split = split;
        Tn->left = build_kdtree(set_left, sizeleft, Tn->left);
        Tn->right = build_kdtree(set_right, sizeright, Tn->right);
        return Tn;
    }
}
//build KD tree
/////////////////////////////////////////////////////////////////////////////////////////////
//Search
template <class T, class T1>
bool arePointsSame(T point1[], T point2[])
{
    for (int i = 0; i < k; ++i)
        if (point1[i] != point2[i])
            return false;

    return true;
}
template <class T, class T1>
bool searchRec(shared_ptr<Tnode<T, T1>> root, T point[])
{
    if (root == NULL)
        return false;
    if (arePointsSame<T, T1>(root->da.number, point))
        return true;
    int cd = root->split;

    if (point[cd] < root->da.number[cd])
        return searchRec(root->left, point);

    return searchRec(root->right, point);
}
template <class T, class T1>
bool search(shared_ptr<Tnode<double, int>> root, T point[])
{
    return searchRec<T, T1>(root, point);
}
//Search
/////////////////////////////////////////////////////////////////////////////////////////
//insert
template <class T, class T1>
shared_ptr<Tnode<T, T1>> insertRec(shared_ptr<Tnode<T, T1>> root, T point[])
{
    if (root == NULL)
    {
        return newnode<T, T1>(point);
    }

    int cd = root->split;

    if (point[cd] < root->da.number[cd])
        root->left = insertRec(root->left, point);
    else
        root->right = insertRec(root->right, point);
    return root;
}
template <class T, class T1>
shared_ptr<Tnode<T, T1>> insert(shared_ptr<Tnode<T, T1>> root, T point[], vectordata<T, T1> set[], T1 id)
{
    for (int i = 0; i < k; i++)
    {
        set[id].number[i] = point[i];
    }
    return insertRec<T, T1>(root, point);
}
template <class T, class T1>
int insertnew(shared_ptr<Tnode<double, int>> root, T point[], vectordata<T, T1> set[], T1 id)
{
    insert<T, T1>(root, point, set, id);
    return id + 1;
}
//insert
//////////////////////////////////////////////////////////////////////////////////////
//delete
template <class T, class T1>
shared_ptr<Tnode<double, int>> minNode(shared_ptr<Tnode<double, int>> t1, shared_ptr<Tnode<double, int>> t2, shared_ptr<Tnode<double, int>> t3, T1 d)
{
    shared_ptr<Tnode<double, int>> tmp = t1;
    if (t2 != NULL && t2->da.number[d] < tmp->da.number[d])
        tmp = t2;
    if (t3 != NULL && t3->da.number[d] < tmp->da.number[d])
        tmp = t3;
    return tmp;
}
template <class T, class T1>
shared_ptr<Tnode<T, T1>> findMinRec(shared_ptr<Tnode<T, T1>> root, T1 d) //find minimun consider one dimension
{

    if (root == NULL)
        return NULL;

    int cd = root->split;

    if (cd == d)
    {
        if (root->left == NULL)
            return root;
        return findMinRec(root->left, d);
    }

    return minNode<T, T1>(root, findMinRec(root->left, d), findMinRec(root->right, d), d);
}
template <class T, class T1>
shared_ptr<Tnode<T, T1>> findMin(shared_ptr<Tnode<T, T1>> root, T1 d)
{
    return findMinRec(root, d);
} //find minimum in d th dimension
template <class T, class T1>
void copyPoint(T p1[], T p2[])
{
    for (int i = 0; i < k; i++)
        p1[i] = p2[i];
}
template <class T, class T1>
shared_ptr<Tnode<T, T1>> deleteNodeRec(shared_ptr<Tnode<T, T1>> root, T point[])
{
    // if point is not present
    if (root == NULL)
        return NULL;

    // Find dimension of current node
    int cd = root->split;

    // if the point  is present at root
    if (arePointsSame<T, T1>(root->da.number, point))
    {

        if (root->right != NULL)
        {
            // Find minimum of root's dimension in right subtree
            shared_ptr<Tnode<T, T1>> min = findMin(root->right, cd);

            // copy the minimum to root
            copyPoint<T, T1>(root->da.number, min->da.number);

            // recursively delete the minimum
            root->right = deleteNodeRec(root->right, min->da.number);
        }
        else if (root->left != NULL) // same as above
        {
            shared_ptr<Tnode<T, T1>> min = findMin(root->left, cd);
            copyPoint<T, T1>(root->da.number, min->da.number);
            root->right = deleteNodeRec(root->left, min->da.number);
        }
        else // if node to be deleted is leaf node
        {
            //delete root;
            return NULL;
        }
        return root;
    }
    if (point[cd] < root->da.number[cd])
        root->left = deleteNodeRec(root->left, point);
    else
        root->right = deleteNodeRec(root->right, point);
    return root;
}
template <class T, class T1>
shared_ptr<Tnode<double, int>> deleteNode(shared_ptr<Tnode<double, int>> root, T point[]) //delete node
{
    return deleteNodeRec<T, T1>(root, point);
}
template <class T, class T1>
int deletedata(vectordata<T, T1> set[], T point1[], T1 id)
{
    for (int i = 0; i < id; i++)
    {
        if (arePointsSame<T, T1>(set[i].number, point1)) //find the set and delete the set
        {
            for (int j = i; j < id - 1; j++)
            {
                set[i] = set[i + 1];
            }
            break;
        }
    }
    return id - 1; //update id
}
//delete
////////////////////////////////////////////////////////////////////////////////////
//update
//root = NULL;
//root=build_kdtree(set, id, root);
//update
#endif