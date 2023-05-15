#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Node {
    int data;
    char* dna;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

struct BST {
    Node* root;
};

typedef struct BST BST;

// This function creates a new node with the given data and initializes its fields
Node* createNode(int data) {
    // Allocate memory for the new node using malloc() and cast the return value to Node*
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    // Set the data field of the new node to the given data
    newNode->data = data;
    
    // Set the dna field of the new node to NULL
    newNode->dna = NULL;
    
    // Set the left and right child pointers of the new node to NULL
    newNode->left = NULL;
    newNode->right = NULL;
    
    // Return a pointer to the new node
    return newNode;
}


// This function inserts a new node with the given value into the binary search tree
void insert(BST* bst, int num) {
    // If the tree is empty, create a new root node with the given value
    if (bst->root == NULL) {
        bst->root = createNode(num);
    } else {
        // Otherwise, traverse the tree to find the appropriate place to insert the new node
        Node* current = bst->root;
        while (current != NULL) {
            // If the value is less than the current node's value, go left
            if (num < current->data) {
                if (current->left == NULL) {
                    // If the left child is NULL, create a new node and set it as the left child
                    current->left = createNode(num);
                    break;
                } else {
                    // Otherwise, continue traversing left
                    current = current->left;
                }
            } else {
                // If the value is greater than or equal to the current node's value, go right
                if (current->right == NULL) {
                    // If the right child is NULL, create a new node and set it as the right child
                    current->right = createNode(num);
                    break;
                } else {
                    // Otherwise, continue traversing right
                    current = current->right;
                }
            }
        }
    }
}

// This function generates a binary search tree (BST) with N nodes
BST generateBST(int N, double x0) {
    int i;
    BST bst;
    bst.root = NULL; // Initialize the BST with a null root
    double R = 3.99; // Set the value of the R constant for the logistic map equation
    double x = x0; // Set the initial value of x
    for ( i = 1; i <= N; i++) {
        x = R * x * (1 - x); // Update the value of x using the logistic map equation
        int num = round(x * 255); // Multiply x by 255 and round to the nearest integer to get the value to be inserted into the BST
        insert(&bst, num); // Insert the generated value into the BST
    }
    return bst; // Return the generated BST
}

char* intToBinary(int num) {
    int i;
    // Allocate memory for a char array to hold the binary string
    char* binary = (char*)malloc(9 * sizeof(char));
    binary[8] = '\0'; // Set the last character of the binary string to null terminator
    for ( i = 7; i >= 0; i--) { // Iterate over the 8 bits of the binary string in reverse order
        binary[i] = (num % 2) + '0'; // Compute the binary digit by taking the remainder when num is divided by 2, and add '0' to convert the digit to a character
        num /= 2; // Divide num by 2 to shift to the next binary digit
    }
    return binary; // Return the binary string
}
char* binaryToDNA(char* binary, int rule) {
    int i,length = strlen(binary); // Get the length of the binary string
    char* result = malloc((length / 2) + 1); // Allocate memory for the resulting DNA sequence
    for ( i = 0; i < length; i += 2) { // Iterate over the binary string two characters at a time
        char a = binary[i]; // Get the first character of the current pair
        char b = binary[i + 1]; // Get the second character of the current pair
        switch (rule) { // Select the appropriate binary coding rule based on the value of the rule argument
            case 1:
                if (a == '0' && b == '0') result[i / 2] = 'A';
                else if (a == '1' && b == '1') result[i / 2] = 'T';
                else if (a == '1' && b == '0') result[i / 2] = 'C';
                else if (a == '0' && b == '1') result[i / 2] = 'G';
                break;
            case 2:
                if (a == '0' && b == '0') result[i / 2] = 'A';
                else if (a == '1' && b == '1') result[i / 2] = 'T';
                else if (a == '0' && b == '1') result[i / 2] = 'C';
                else if (a == '1' && b == '0') result[i / 2] = 'G';
                break;
            case 3:
                if (a == '1' && b == '1') result[i / 2] = 'A';
                else if (a == '0' && b == '0') result[i / 2] = 'T';
                else if (a == '1' && b == '0') result[i / 2] = 'C';
                else if (a == '0' && b == '1') result[i / 2] = 'G';
                break;
            case 4:
                if (a == '1' && b == '1') result[i / 2] = 'A';
                else if (a == '0' && b == '0') result[i / 2] = 'T';
                else if (a == '0' && b == '1') result[i / 2] = 'C';
                else if (a == '1' && b == '0') result[i / 2] = 'G';
                break;
            case 5:
                if (a == '1' && b == '0') result[i / 2] = 'A';
                else if (a == '0' && b == '1') result[i / 2] = 'T';
                else if (a == '0' && b == '0') result[i / 2] = 'C';
                else if (a == '1' && b == '1') result[i / 2] = 'G';
                break;
            case 6:
                if (a == '0' && b == '1') result[i / 2] = 'A';
                else if (a == '1' && b == '0') result[i / 2] = 'T';
                else if (a == '0' && b == '0') result[i / 2] = 'C';
                else if (a == '1' && b == '1') result[i / 2] = 'G';
                break;
            case 7:
                if (a == '1' && b == '0') result[i / 2] = 'A';
                else if (a == '0' && b == '1') result[i / 2] = 'T';
                else if (a == '1' && b == '1') result[i / 2] = 'C';
                else if (a == '0' && b == '0') result[i / 2] = 'G';
                break;
            case 8:
                if (a == '0' && b == '1') result[i / 2] = 'A';
                else if (a == '1' && b == '0') result[i / 2] = 'T';
                else if (a == '1' && b == '1') result[i / 2] = 'C';
                else if (a == '0' && b == '0') result[i / 2] = 'G';
                break;
            default:
                free(result); // Free the allocated memory
                return NULL;  // Invalid rule number
        }
    }
    result[length / 2] = '\0'; // Add null character at the end of the resulting DNA sequence
    return result;
}


void traversal(Node* node, double R, double* x, int N) {
    if (node == NULL)
        return;

    traversal(node->left, R, x, N); // Traverse the left subtree

    // Generate DNA sequence for the current node
    char* binary = intToBinary(node->data); // Convert node data to binary
    *x = R * (*x) * (1 - (*x)); // Update the value of x using the logistic map equation
    int ruleNum = round((*x) * 7) + 1; // Determine the rule number based on the updated value of x
    node->dna = binaryToDNA(binary, ruleNum); // Generate the DNA sequence for the node

    traversal(node->right, R, x, N); // Traverse the right subtree
}

BST convertBSTtoDNA(BST bst, int N) {
    double R = 3.99;
    double x0 = 0.1;
    traversal(bst.root, R, &x0, N);
    return bst;
}

void printDNAStrands(Node* node) {
    if (node == NULL) return;

    printDNAStrands(node->left);
    printf("Node %d: %s\n", node->data, node->dna);
    printDNAStrands(node->right);
}
void freeBST(Node* node) {
    if (node == NULL) return;

    freeBST(node->left);
    freeBST(node->right);
    free(node->dna);
    free(node);
}

int main() {
    int N = 100;
    double x0 = 0.3;
    BST bst = generateBST(N, x0);
    bst = convertBSTtoDNA(bst, N);

    // Print the DNA sequence for each node
    printDNAStrands(bst.root);

    // Free memory used by the BST
    freeBST(bst.root);

    return 0;
}


