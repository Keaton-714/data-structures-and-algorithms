/*
How to run this program (macOS/Linux):
1) Compile:
   g++ main.cpp sorting.cpp -o sorting_demo
2) Run:
   ./sorting_demo
3) Input:
   - Enter 9 digits (** With spaces between each number **)
   - Choose a sorting algorithm from the menu
   The program prints the sorted array and execution time in microseconds.
*/
#include <iostream>
#include <chrono>
#include "sorting.h"
using namespace std;
using namespace chrono;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    const int n = 9;
    int arr[n];

    cout << "Enter 9 digits (x x x x x x x x x): ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "\nChoose sorting algorithm:\n";
    cout << "1. Insertion Sort\n2. Selection Sort\n3. Heap Sort\n4. Merge Sort\n5. Quick Sort\n";
    int choice;
    cin >> choice;

    // Copy array for sorting
    int sorted[n];
    for (int i = 0; i < n; i++) sorted[i] = arr[i];

    cout << "\nOriginal array: ";
    printArray(arr, n);

    // Start timer
    auto start = high_resolution_clock::now();

    // Run chosen algorithm
    switch (choice) 
    {
        case 1: insertionSort(sorted, n); break;
        case 2: selectionSort(sorted, n); break;
        case 3: heapSort(sorted, n); break;
        case 4: mergeSort(sorted, 0, n - 1); break;
        case 5: quickSort(sorted, 0, n - 1); break;
        default: cout << "Invalid choice!\n"; return 0;
    }

    // End timer
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Sorted array: ";
    printArray(sorted, n);

    cout << "Execution time: " << duration.count() << " microseconds\n";
    return 0;
}
