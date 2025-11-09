#include <iostream>
#include <climits>
#include <vector>
using namespace std;

int arr[50][50];
int n, visited[50], path[50], final_res = INT_MAX;

struct node {
    int cost;
    int arr[50][50];
    int visited[50];
    int parent[50][50];
    int last;
    vector <int> path;
};

node stack[50];
int top=0;
node result;

int reduce(int arr[50][50]) {
    int row_reduction[50] = {0};
    int col_reduction[50] = {0};
    int cost = 0;
    // Row reduction
    for (int i = 0; i < n; i++) {
        int row_min = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (arr[i][j] < row_min) {
                row_min = arr[i][j];
            }
        }
        if (row_min != INT_MAX && row_min > 0) {
            row_reduction[i] = row_min;
            cost += row_min;
            for (int j = 0; j < n; j++) {
                if (arr[i][j] != INT_MAX) {
                    arr[i][j] -= row_min;
                }
            }
        }
    }

    // Column reduction
    for (int j = 0; j < n; j++) {
        int col_min = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (arr[i][j] < col_min) {
                col_min = arr[i][j];
            }
        }
        if (col_min != INT_MAX && col_min > 0) {
            col_reduction[j] = col_min;
            cost += col_min;
            for (int i = 0; i < n; i++) {
                if (arr[i][j] != INT_MAX) {
                    arr[i][j] -= col_min;
                }
            }
        }
    }

    // Print reduced matrix
    cout << "Reduced Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == INT_MAX) {
                cout << "INF\t";
            } else {
                cout << arr[i][j] << "\t";
            }
        }
        cout << endl;
    }
    return cost;
}

int main() {
    // n = 5;
    // arr[0][0] = INT_MAX; arr[0][1] = 20; arr[0][2] = 30; arr[0][3] = 10; arr[0][4] = 11;
    // arr[1][0] = 15; arr[1][1] = INT_MAX; arr[1][2] = 16; arr[1][3] = 4; arr[1][4] = 2;
    // arr[2][0] = 3; arr[2][1] = 5; arr[2][2] = INT_MAX; arr[2][3] = 2; arr[2][4] = 4;
    // arr[3][0] = 19; arr[3][1] = 6; arr[3][2] = 18; arr[3][3] = INT_MAX; arr[3][4] = 3;
    // arr[4][0] = 16; arr[4][1] = 4; arr[4][2] = 7; arr[4][3] = 16; arr[4][4] = INT_MAX;
    n = 4;
    arr[0][0] = INT_MAX; arr[0][1] = 10; arr[0][2] = 15; arr[0][3] = 20;
    arr[1][0] = 10; arr[1][1] = INT_MAX; arr[1][2] = 35; arr[1][3] = 25;
    arr[2][0] = 15; arr[2][1] = 35; arr[2][2] = INT_MAX; arr[2][3] = 30;
    arr[3][0] = 20; arr[3][1] = 25; arr[3][2] = 30; arr[3][3] = INT_MAX;
    int original[50][50];
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            original[i][j] = arr[i][j];
        }
    }
    int initial = reduce(arr);
    for (int i=0; i<n; i++) {
        visited[i] = 0;
    }
    visited[0] = 1;
    cout << "Initial reduction cost: " << initial << endl;
    node temp;
    temp.cost = initial;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            temp.arr[i][j] = arr[i][j];
            temp.parent[i][j] = arr[i][j];
        }
        temp.visited[i] = visited[i];
        //temp.arr[0][i] = INT_MAX;
    }
    temp.path.push_back(0);
    temp.last = 0;
    stack[top] = temp;
    top ++;
    while (top > 0) {
        int idx = 0;
        int min_cost = INT_MAX;
        for (int i=0; i<top; i++) {
            if (stack[i].cost < min_cost) {
                min_cost = stack[i].cost;
                idx = i;
            }
        }
        node curr = stack[idx];
        for (int i=idx; i<top-1; i++) {
            stack[i] = stack[i+1];
        }
        top--;
        if (curr.cost >= final_res) {
            continue;
        }
        for (int i=0; i<n; i++) {
            if (curr.visited[i]) {
                continue;
            }
            node child;
            for (int r=0; r<n; r++) {
                for (int c=0; c<n; c++) {
                    child.arr[r][c] = curr.arr[r][c];
                    child.parent[r][c] = curr.arr[r][c];
                }
                child.visited[r] = curr.visited[r];
            }
            child.visited[i] = 1;
            for (int k=0; k<n; k++) {
                child.arr[curr.last][k] = INT_MAX;
            }
            for (int k=0; k<n; k++) {
                child.arr[k][i] = INT_MAX;
            }
            child.arr[i][0] = INT_MAX;
            int cost_added = curr.cost + child.parent[curr.last][i];
            int reduction_cost = reduce(child.arr);
            printf("Cost added: %d, Reduction cost: %d, Curr Cost: %d\n", cost_added, reduction_cost, curr.cost);
            child.cost = cost_added + reduction_cost;
            child.last = i;
            child.path = curr.path;
            child.path.push_back(i);
            if (child.cost < final_res) {
                bool all_visited = true;
                for (int v=0; v<n; v++) {
                    if (!child.visited[v]) {
                        all_visited = false;
                        break;
                    }
                }
                if (all_visited) {
                    int total_cost = child.cost + child.parent[child.last][0];
                    if (total_cost < final_res) {
                        final_res = total_cost;
                        result = child;
                        result.cost = final_res;
                    }
                } else {
                    stack[top] = child;
                    top++;
                }
            }
        }
    }
    cout << "Optimal Path: ";
    for (int i=0; i<result.path.size(); i++) {
        cout << result.path[i] << " ";
    }
    cout << "Minimum cost of TSP: " << final_res << endl;
}
