#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

#define MAX_CITIES 20

struct Node {
    int reducedMatrix[MAX_CITIES][MAX_CITIES];
    int cost;
    int vertex;
    int level;
    int path[MAX_CITIES];
    int pathLength;
};

struct Compare {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->cost > rhs->cost;
    }
};

void copyMatrix(int dest[MAX_CITIES][MAX_CITIES], int src[MAX_CITIES][MAX_CITIES], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

void copyPath(int dest[MAX_CITIES], int& destLength, int src[MAX_CITIES], int srcLength) {
    destLength = srcLength;
    for (int i = 0; i < srcLength; i++) {
        dest[i] = src[i];
    }
}

int reduceMatrix(int matrix[MAX_CITIES][MAX_CITIES], int n) {
    int cost = 0;
    
    // Reduce rows
    for (int i = 0; i < n; i++) {
        int minVal = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }
        if (minVal != INT_MAX && minVal != 0) {
            cost += minVal;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= minVal;
                }
            }
        }
    }
    
    // Reduce columns
    for (int j = 0; j < n; j++) {
        int minVal = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }
        if (minVal != INT_MAX && minVal != 0) {
            cost += minVal;
            for (int i = 0; i < n; i++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= minVal;
                }
            }
        }
    }
    
    return cost;
}

void solveTSP(int originalMatrix[MAX_CITIES][MAX_CITIES], int n) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    // Create root node
    Node* root = new Node();
    copyMatrix(root->reducedMatrix, originalMatrix, n);
    root->path[0] = 0;
    root->pathLength = 1;
    root->level = 0;
    root->vertex = 0;
    
    int tempMatrix[MAX_CITIES][MAX_CITIES];
    copyMatrix(tempMatrix, root->reducedMatrix, n);
    root->cost = reduceMatrix(tempMatrix, n);
    copyMatrix(root->reducedMatrix, tempMatrix, n);
    
    pq.push(root);
    
    int minCost = INT_MAX;
    int finalPath[MAX_CITIES];
    int finalPathLength = 0;
    
    while (!pq.empty()) {
        Node* minNode = pq.top();
        pq.pop();
        
        int i = minNode->vertex;
        
        if (minNode->level == n - 1) {
            int returnCost = originalMatrix[i][0];
            if (returnCost != INT_MAX) {
                int totalCost = minNode->cost + returnCost;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    copyPath(finalPath, finalPathLength, minNode->path, minNode->pathLength);
                    finalPath[finalPathLength++] = 0;
                }
            }
            delete minNode;
            continue;
        }
        
        for (int j = 0; j < n; j++) {
            if (minNode->reducedMatrix[i][j] != INT_MAX && minNode->reducedMatrix[i][j] != 0) {
                Node* child = new Node();
                copyMatrix(child->reducedMatrix, minNode->reducedMatrix, n);
                
                for (int k = 0; k < n; k++) {
                    child->reducedMatrix[i][k] = INT_MAX;
                    child->reducedMatrix[k][j] = INT_MAX;
                }
                child->reducedMatrix[j][0] = INT_MAX;
                
                copyPath(child->path, child->pathLength, minNode->path, minNode->pathLength);
                child->path[child->pathLength++] = j;
                
                child->level = minNode->level + 1;
                child->vertex = j;
                
                int tempChildMatrix[MAX_CITIES][MAX_CITIES];
                copyMatrix(tempChildMatrix, child->reducedMatrix, n);
                int reductionCost = reduceMatrix(tempChildMatrix, n);
                child->cost = minNode->cost + minNode->reducedMatrix[i][j] + reductionCost;
                copyMatrix(child->reducedMatrix, tempChildMatrix, n);
                
                if (child->cost < minCost) {
                    pq.push(child);
                } else {
                    delete child;
                }
            }
        }
        
        delete minNode;
    }
    
    if (minCost != INT_MAX) {
        cout << "\nMinimum Cost: " << minCost << endl;
        cout << "Optimal Path: ";
        for (int i = 0; i < finalPathLength; i++) {
            cout << finalPath[i];
            if (i < finalPathLength - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "\nNo feasible solution found!" << endl;
    }
    
    while (!pq.empty()) {
        Node* node = pq.top();
        pq.pop();
        delete node;
    }
}

void printMatrix(int matrix[MAX_CITIES][MAX_CITIES], int n) {
    cout << "\nCost Matrix:" << endl;
    cout << "    ";
    for (int j = 0; j < n; j++) {
        cout << "C" << j << "  ";
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "C" << i << "  ";
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                printf("%3d ", matrix[i][j]);
            }
        }
        cout << endl;
    }
}

int main() {
    cout << "=== Traveling Salesman Problem using LC Branch and Bound ===" << endl;
    
    // New 5x5 cost matrix example
    int n = 5;
    int costMatrix[MAX_CITIES][MAX_CITIES];
    
    // Initialize with INF
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            costMatrix[i][j] = INT_MAX;
        }
    }
    
    // New symmetric cost matrix (distances between 5 cities)
    costMatrix[0][1] = 12; costMatrix[0][2] = 29; costMatrix[0][3] = 22; costMatrix[0][4] = 13;
    costMatrix[1][0] = 12; costMatrix[1][2] = 19; costMatrix[1][3] = 25; costMatrix[1][4] = 18;
    costMatrix[2][0] = 29; costMatrix[2][1] = 19; costMatrix[2][3] = 17; costMatrix[2][4] = 28;
    costMatrix[3][0] = 22; costMatrix[3][1] = 25; costMatrix[3][2] = 17; costMatrix[3][4] = 16;
    costMatrix[4][0] = 13; costMatrix[4][1] = 18; costMatrix[4][2] = 28; costMatrix[4][3] = 16;
    
    // Set diagonal to INF
    for (int i = 0; i < n; i++) {
        costMatrix[i][i] = INT_MAX;
    }
    
    cout << "5x5 Cost Matrix Example:" << endl;
    cout << "Cities: 0, 1, 2, 3, 4" << endl;
    
    printMatrix(costMatrix, n);
    solveTSP(costMatrix, n);
    
    // Verification of the result
    cout << "\n--- Verification ---" << endl;
    cout << "Possible tours and their costs:" << endl;
    
    // List some possible tours to verify optimality
    int possibleTours[5][6] = {
        {0, 1, 2, 3, 4, 0},  // 12 + 19 + 17 + 16 + 13 = 77
        {0, 1, 2, 4, 3, 0},  // 12 + 19 + 28 + 16 + 22 = 97
        {0, 1, 3, 2, 4, 0},  // 12 + 25 + 17 + 28 + 13 = 95
        {0, 1, 4, 3, 2, 0},  // 12 + 18 + 16 + 17 + 29 = 92
        {0, 4, 3, 2, 1, 0}   // 13 + 16 + 17 + 19 + 12 = 77
    };
    
    const char* tourNames[] = {
        "0->1->2->3->4->0",
        "0->1->2->4->3->0", 
        "0->1->3->2->4->0",
        "0->1->4->3->2->0",
        "0->4->3->2->1->0"
    };
    
    for (int i = 0; i < 5; i++) {
        int tourCost = 0;
        for (int j = 0; j < 5; j++) {
            int from = possibleTours[i][j];
            int to = possibleTours[i][j + 1];
            tourCost += costMatrix[from][to];
        }
        cout << tourNames[i] << " = " << tourCost << endl;
    }
    
    return 0;
}
