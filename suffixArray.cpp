#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

class SuffixArray {
private:
    const char* inputString;
    int length;
    int* suffixIndices;       // (indices of suffixes)
    int* currentRankArray;         // Current rank array
    int* tempRankArray;             // Temporary rank array

public:
    // Constructor
    SuffixArray(const char* input) {
        // Add the '$' character to the input string
        string modifiedInput = input;
        modifiedInput += '$';
        inputString = modifiedInput.c_str();
        length = modifiedInput.length();

        // Allocate memory for arrays
        suffixIndices = new int[length];
        currentRankArray = new int[length];
        tempRankArray = new int[length];
    }

    // Destructor
    ~SuffixArray() {

        delete[] suffixIndices;
        delete[] currentRankArray;
        delete[] tempRankArray;
    }

    // Function to Build SuffixArray
    void BuildSuffixArray() {
        // Initialize the suffix array and rank array
        for (int i = 0; i < length; ++i) {
            suffixIndices[i] = i;
            currentRankArray[i] = (inputString[i] == '$') ? -1 : inputString[i];
        }

        // Perform sorting based on the first 2^k characters
        for (int k = 1; k < length; k *= 2) {
            // Comparator function for sorting suffixes
            auto comparator = [this, k](int i, int j) {
                if (currentRankArray[i] != currentRankArray[j]) {
                    return currentRankArray[i] < currentRankArray[j];
                }
                // Compare suffixes based on the second half of the 2^k prefix
                int rank_i = (i + k < length) ? currentRankArray[i + k] : -1;
                int rank_j = (j + k < length) ? currentRankArray[j + k] : -1;
                return rank_i < rank_j;
            };

            // Sort the suffix indices using the comparator
            sort(suffixIndices, suffixIndices + length, comparator);

            // Step 3: Update the ranks after sorting
            tempRankArray[suffixIndices[0]] = 0;  // The smallest suffix gets rank 0
            for (int i = 1; i < length; ++i) {
                tempRankArray[suffixIndices[i]] = tempRankArray[suffixIndices[i - 1]] + (comparator(suffixIndices[i - 1], suffixIndices[i]) ? 1 : 0);
            }

            // Copy the new ranks to the current rank array
            copy(tempRankArray, tempRankArray + length, currentRankArray);
        }
    }

    // Function to print the suffix array
    void Print() const {
        for (int i = 0; i < length; ++i) {
            cout << suffixIndices[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // Input string
    const char* input = "ACGACTACGATAAC";


    SuffixArray suffixArray(input);
    suffixArray.BuildSuffixArray();
    suffixArray.Print();

    return 0;
}
