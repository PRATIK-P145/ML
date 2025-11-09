#include <iostream>
#include <vector>
//#include <cmath>
using namespace std;

vector<int> selected;

struct items{
    int profit;
    int weight;
};

int knapsack(struct items item[], int n, int capacity){
    vector<vector<int>> dp (n+1, vector<int>(capacity+1));

    int i,w;
    for( i=0; i<n+1; i++){
        for( w=0; w<capacity+1; w++){

            if(i==0 || w==0)
                dp[i][w] = 0;

            else if(item[i-1].weight <= w){
                dp[i][w] = max(dp[i-1][w], item[i-1].profit+dp[i-1][w-item[i-1].weight] );
            }
            else{
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    i--; w--;
    while(dp[i][w]!=0){
        if( dp[i-1][w] != dp[i][w] ){
            //cout<<"\nAdded-"<<i;
            selected.push_back(i);
            w = w - item[i-1].weight;
            i--; 
           // cout<<"\ni- "<<i<<"\nw- "<<w;
        }
        else{
            i--;
        }
    }

    return dp[n][capacity];
 
}

int main(){
   
    struct items item[5] = { {6,1}, {10,2}, {12,3}, {7,2}, {18,5} };
    int cap = 10;
    int result = knapsack(item, 5, 10);

    cout<<"\nFinal Result : "<<result;
    cout<<"\nSELECTED ITEMS : "<<endl;
    cout<<"Indx\tWeight\tProfit"<<endl;
    
    for(int j=0; j<selected.size(); j++){
        int i = selected[j];
        cout<<i<<"\t"<<item[i-1].weight<<"\t"<<item[i-1].profit<<endl;
    }

    return 0;
}
