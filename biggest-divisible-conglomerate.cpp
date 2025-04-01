// Programmer: Walter Cordero
// This is my 8th c++ program
// DYNAMMIC PROGRAMMING

#include "bdc.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// coverts vectors of ints into a string representaton of such
string vec_to_string(vector<int> v) {
    if (v.empty()) return "{}";
    string result = "{";
    for (size_t i = 0; i < v.size(); i++) {
        result += to_string(v[i]) + (i != v.size() - 1 ? ", " : "");
    }
    return result + "}";
}

// funct to find the biggest divisble subset implementing dp

vector<int> biggest_divisible_conglomerate(vector<int>& input) {
    if (input.empty()) return {};
    
    // sorts the input for smoothness like before 
    
    sort(input.begin(), input.end());
    int n = input.size(); // int n 

    // helps reconstruct subset

    vector<int> dp(n, 1);  // dp[i] stores the size of the largest subset ending at index i
    vector<int> parent(n, -1);  
    
    int max_size = 1, max_index = 0;
    

    // builds the dp table
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (input[i] % input[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > max_size) {
            max_size = dp[i];
            max_index = i;
        }
    }
    // Reconstruct the largest subset
    vector<int> result;
    for (int i = max_index; i >= 0; i = parent[i]) {
        result.push_back(input[i]);
        if (parent[i] == -1) break;
    }
    
    reverse(result.begin(), result.end());
    return result;
}

/*
Time Complexity Comparison 

Previous recursive approach was O(2^n) -> Exponential complexity due to subset exploration.

DP approach: O(n^2) -> Quadratic complexity using table-based DP.
  Sorting takes O(n log n)
  DP table construction takes O(n^2)
  Reconstruction takes O(n)
  Overall complexity -> O(n^2)

we can clearly see DP is the best option for massive input to programs like this

however recursion is good for like part 1 where the inputs weren't massive

We use this DP approach because when we have inputs like the 28000 recursion is just not feasible 
*/
