/*
 * Author: Spencer Peters
 * Date: 10/16/18
 * Class: CSC-2710
 * File Location: ~/CSC2710/Proj4
 *
 * This program uses the optimal binary search tree and puts the phrase or sentence in pre, in, and post
 * order
 *
 * To compile g++ main.cpp and then use IO redirection to run, a.out < (filename)
 */
#include <iostream>
#include <string>
#include "btnode.h"
#include "bst.h"
#include "binary.h"

using namespace std;
void optsearchtree(int n, const float p[], float& minavg, int R[][100]);
BinaryTree<string> tree(int i, int j, string keys[], int R[][100]);
void print(BinaryTree<string> tree);

/*Main Function:
 *      Is used to call all the other function in order to build the optimal binary
 *      search tree and to print out the final pre, in, and post order
 */
int main()
{
    int amtofKeys;
    cin >> amtofKeys;
    string keys[amtofKeys];
    float prob[amtofKeys];
    float minavg = 0;
    int R[100][100];
    BinaryTree<string> searchTree;
    for (int i = 1; i <= amtofKeys; i++)
    {
        cin >> keys[i];
    }
    for (int j = 1; j <= amtofKeys; j++)
    {
        cin >> prob[j];
    }
    optsearchtree(amtofKeys,prob,minavg,R);
    cout << "Average Seek Time: " << minavg << endl;
    cout << endl;

    searchTree = tree(1, amtofKeys, keys, R);
    print(searchTree);
}

/*optsearchtree Function:
 *      Files the array R in order to prepare it to be used to build the tree
 *
 *precondition:
 *      Takes the amount of words, the probability, and the unused R 2D array
 *      which will be filled by the end of the function run. It also calculates the
 *      minimum and sum within the function without having to call other functions.
 *
 *post conditon:
 *      Once the function has completed the variable minavg will be assigned
 *      the minimum seek time. R[][] is indexed with the keys to build the optimal search
 *      tree
 */
void optsearchtree(int n, const float p[], float& minavg, int R[][100])
{
    int i, j, k, diagonal;
    float A[n+2][n+1];

    for(i = 1; i <= n; i++)
    {
        A[i][i-1] = 0;
        A[i][i] = p[i];
        R[i][i] = i;
        R[i][i-1] = 0;

    }
    A[n+1][n] = 0;
    R[n+1][n] = 0;

    for(diagonal = 1; diagonal <= n-1; diagonal++)
    {
        for(i = 1; i <= (n - diagonal); i++)
        {
            j = i + diagonal;
            float temp = 10000000;
            float sum = 0;
            int temp2;
            for(k = i ;k <= j ;k++)
            {
                if((A[i][k-1] + A[k+1][j]) < temp)
                {
                    temp = A[i][k-1] + A[k+1][j];
                    temp2 = k;
                }
            }
            for(int z = i; z <= j; z++)
            {
                sum += p[z];
            }
            A[i][j] = temp + sum;
            R[i][j] = temp2;
        }
    }
    minavg = A[1][n];
}

/*tree Function:
 *      Uses the R[][] array from the optsearchtree function to build a tree
 *
 *precondition:
 *      This function takes in j the amount of keys, keys being the words provided from the file
 *      and R which was just created in optsearchtree
 *
 *post conditon:
 *      Once the function has completed a pointer to an optimal binary search tree will be returned
 *      holding the amount of keys
 */
BinaryTree<string> tree(int i, int j, string keys[], int R[][100])
{
    int k;
    BinaryTree<string> leftChild;
    BinaryTree<string> rightChild;
    BinaryTree<string> pointer;
    k = R[i][j];
    if(k == 0)
    {
        return pointer;
    }
    else
    {
        leftChild = tree(i, k-1, keys, R);
        rightChild = tree(k+1, j, keys, R);
        pointer.MakeTree(keys[k], leftChild, rightChild);
        return pointer;
    }
}

/*print Function:
 *      Function calls the functions in binary.h to output the tree in the proper orders
 *
 *precondition:
 *      The function is given the tree
 *
 *post conditon:
 *      Once the function has completed the pre, in, and post order will be printed by
 *      sending the tree to each one of the functions to be treversed in the proper order
 */
void print(BinaryTree<string> tree)
{
    cout << "Pre-Order: ";
    tree.PreOutput();
    cout << endl;
    cout << "In-Order: ";
    tree.InOutput();
    cout << endl;
    cout << "Post-Order: ";
    tree.PostOutput();
    cout << endl;
}


