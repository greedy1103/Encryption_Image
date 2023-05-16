#include <iostream>
#include <cmath>
#include <cstring>

// Define a Node structure to hold data, dna, and pointers to left and right child nodes
struct Node
{
    int data;
    char *dna;
    Node *left;
    Node *right;
};

// Define a BST structure to hold the root node of the binary search tree
struct BST
{
    Node *root;
};

// Function to create a new node with given data and initialize its members
Node *createNode(int data)
{
    Node *newNode = new Node;
    newNode->data = data;
    newNode->dna = nullptr;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to insert a new node with given data into the binary search tree
void insert(BST *bst, int num)
{
    if (bst->root == nullptr)
    {
        bst->root = createNode(num);
    }
    else
    {
        Node *current = bst->root;
        while (current != nullptr)
        {
            if (num < current->data)
            {
                if (current->left == nullptr)
                {
                    current->left = createNode(num);
                    break;
                }
                else
                {
                    current = current->left;
                }
            }
            else
            {
                if (current->right == nullptr)
                {
                    current->right = createNode(num);
                    break;
                }
                else
                {
                    current = current->right;
                }
            }
        }
    }
}

// Function to generate a binary search tree with N nodes using logistic map equation
BST generateBST(int N, double x0)
{
    BST bst;
    bst.root = nullptr;
    double R = 3.99; // R value for logistic map equation
    double x = x0;   // initial value for logistic map equation
    for (int i = 1; i <= N; i++)
    {
        x = R * x * (1 - x);           // calculate next value using logistic map equation
        int num = std::round(x * 255); // scale value to range [0, 255]
        insert(&bst, num);             // insert value into binary search tree
    }
    return bst;
}

// Function to convert an integer to its binary representation as a string
char *intToBinary(int num)
{
    char *binary = new char[9];
    binary[8] = '\0';
    for (int i = 7; i >= 0; i--)
    {
        binary[i] = (num % 2) + '0';
        num /= 2;
    }
    return binary;
}
// Function to convert a binary string to a DNA string using a given rule
char *binaryToDNA(char *binary, int rule)
{
    int length = std::strlen(binary);
    char *result = new char[length / 2 + 1];
    for (int i = 0; i < length; i += 2)
    {
        char a = binary[i];
        char b = binary[i + 1];
        switch (rule)
        {
        case 1:
            if (a == '0' && b == '0')
                result[i / 2] = 'A';
            else if (a == '1' && b == '1')
                result[i / 2] = 'T';
            else if (a == '1' && b == '0')
                result[i / 2] = 'C';
            else if (a == '0' && b == '1')
                result[i / 2] = 'G';
            break;
        case 2:
            if (a == '0' && b == '0')
                result[i / 2] = 'A';
            else if (a == '1' && b == '1')
                result[i / 2] = 'T';
            else if (a == '0' && b == '1')
                result[i / 2] = 'C';
            else if (a == '1' && b == '0')
                result[i / 2] = 'G';
            break;
        case 3:
            if (a == '1' && b == '1')
                result[i / 2] = 'A';
            else if (a == '0' && b == '0')
                result[i / 2] = 'T';
            else if (a == '1' && b == '0')
                result[i / 2] = 'C';
            else if (a == '0' && b == '1')
                result[i / 2] = 'G';
            break;
        case 4:
            if (a == '1' && b == '1')
                result[i / 2] = 'A';
            else if (a == '0' && b == '0')
                result[i / 2] = 'T';
            else if (a == '0' && b == '1')
                result[i / 2] = 'C';
            else if (a == '1' && b == '0')
                result[i / 2] = 'G';
            break;
        case 5:
            if (a == '1' && b == '0')
                result[i / 2] = 'A';
            else if (a == '0' && b == '1')
                result[i / 2] = 'T';
            else if (a == '0' && b == '0')
                result[i / 2] = 'C';
            else if (a == '1' && b == '1')
                result[i / 2] = 'G';
            break;
        case 6:
            if (a == '0' && b == '1')
                result[i / 2] = 'A';
            else if (a == '1' && b == '0')
                result[i / 2] = 'T';
            else if (a == '0' && b == '0')
                result[i / 2] = 'C';
            else if (a == '1' && b == '1')
                result[i / 2] = 'G';
            break;
        case 7:
            if (a == '1' && b == '0')
                result[i / 2] = 'A';
            else if (a == '0' && b == '1')
                result[i / 2] = 'T';
            else if (a == '1' && b == '1')
                result[i / 2] = 'C';
            else if (a == '0' && b == '0')
                result[i / 2] = 'G';
            break;
        case 8:
            if (a == '0' && b == '1')
                result[i / 2] = 'A';
            else if (a == '1' && b == '0')
                result[i / 2] = 'T';
            else if (a == '1' && b == '1')
                result[i / 2] = 'C';
            else if (a == '0' && b == '0')
                result[i / 2] = 'G';
            break;
        }
    }
    result[length / 2] = '\0'; // add null terminator to end of string
    return result;
}

// Function to perform an in-order traversal of the binary search tree and convert each node's data to a DNA string
void traversal(Node *node, double R, double *x, int N)
{
    if (node == nullptr)
        return;

    traversal(node->left, R, x, N); // traverse left subtree

    char *binary = intToBinary(node->data);   // convert node data to binary string
    *x = R * (*x) * (1 - (*x));               // calculate next value using logistic map equation
    int ruleNum = std::round((*x) * 7) + 1;   // scale value to range [1, 8]
    node->dna = binaryToDNA(binary, ruleNum); // convert binary string to DNA string using calculated rule

    traversal(node->right, R, x, N); // traverse right subtree
}

// Function to convert all nodes in the binary search tree to DNA strings
BST convertBSTtoDNA(BST bst, int N)
{
    double R = 3.99;                // R value for logistic map equation
    double x0 = 0.1;                // initial value for logistic map equation
    traversal(bst.root, R, &x0, N); // perform in-order traversal and convert each node's data to a DNA string
    return bst;
}

// Function to perform an in-order traversal of the binary search tree and print each node's DNA string
void printDNAStrands(Node *node)
{
    if (node == nullptr)
        return;

    printDNAStrands(node->left);                                          // traverse left subtree
    std::cout << "Node " << node->data << ": " << node->dna << std::endl; // print node's DNA string
    printDNAStrands(node->right);                                         // traverse right subtree
}

// Function to free all memory allocated for the binary search tree
void freeBST(Node *node)
{
    if (node == nullptr)
        return;

    freeBST(node->left);  // free left subtree
    freeBST(node->right); // free right subtree
    delete[] node->dna;   // free memory allocated for dna string
    delete node;          // free memory allocated for node
}

int main()
{
    int N = 100;                   // number of nodes in binary search tree
    double x0 = 0.3;               // initial value for logistic map equation
    BST bst = generateBST(N, x0);  // generate binary search tree with N nodes using logistic map equation
    bst = convertBSTtoDNA(bst, N); // convert all nodes in binary search tree to DNA strings

    printDNAStrands(bst.root); //// print all DNA strings in binary search tree

    freeBST(bst.root); // free all memory allocated for binary search tree

    return 0;
}
