#include <bits/stdc++.h>
using namespace std;

class SuffixArray {
private:
    const char* input_string; // Input string
    int string_length; // Length of the input string
    int* suffix_array; // Suffix array
    int* current_rank; // Current rank array
    int* new_rank; // Temporary rank array used during updates

public:
    // Constructor
    SuffixArray(const char* input) {
        input_string = input;
        string_length = std::strlen(input);
        suffix_array = new int[string_length];
        current_rank = new int[string_length];
        new_rank = new int[string_length];
    }

    // Destructor
    ~SuffixArray() {
        delete[] suffix_array;
        delete[] current_rank;
        delete[] new_rank;
    }

    // Function to construct the suffix array using the prefix doubling method
    void ConstructUsingPrefixDoubling() {
        // Step 1: Initialize the suffix array and rank array
        for (int i = 0; i < string_length; ++i) {
            suffix_array[i] = i; // Start with indices of the string
            current_rank[i] = input_string[i]; // Initial rank based on ASCII value of characters
        }

        // Step 2: Perform sorting based on the first 2^k characters, doubling k each time
        for (int k = 1; k < string_length; k *= 2) {
            // Comparator function for sorting suffixes
            auto comparator = [this, k](int i, int j) {
                if (current_rank[i] != current_rank[j]) {
                    return current_rank[i] < current_rank[j];
                }
                int rank_i = (i + k < string_length) ? current_rank[i + k] : -1; // Rank of suffix starting from i + k
                int rank_j = (j + k < string_length) ? current_rank[j + k] : -1; // Rank of suffix starting from j + k
                return rank_i < rank_j;
            };

            // Sort the suffix indices using the comparator
            sort(suffix_array, suffix_array + string_length, comparator);

            // Step 3: Update the ranks after sorting
            new_rank[suffix_array[0]] = 0; // The smallest suffix gets rank 0
            for (int i = 1; i < string_length; ++i) {
                // Assign new rank based on whether the comparator considers the suffixes different
                new_rank[suffix_array[i]] = new_rank[suffix_array[i - 1]] + (comparator(suffix_array[i - 1], suffix_array[i]) ? 1 : 0);
            }

            // Copy the new ranks to the current rank array
            copy(new_rank, new_rank + string_length, current_rank);
        }
    }

    // Function to print the suffix array
    void Print() const {
        for (int i = 0; i < string_length; ++i) {
            cout << suffix_array[i] << (i == string_length - 1 ? "\n" : " ");
        }
    }
};

int main() {
    SuffixArray suffix_array("ACGACTACGATAAC$");
    suffix_array.ConstructUsingPrefixDoubling();
    suffix_array.Print(); // Prints: 14 11 12 0 6 3 9 13 1 7 4 2 8 10 5
    return 0;
}
