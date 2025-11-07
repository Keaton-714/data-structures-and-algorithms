#include "sorting.h"
#include <iostream>
using namespace std;

/* =========================
   INSERTION SORT
   -------------------------
   Build sorted sublist one by one by inserting elements
   ========================= */
void insertionSort(int arr[], int n) 
{

    for (int i = 1; i < n; ++i)
    {
        int j = i;
        while (j > 0 && arr[j] < arr[j-1])
        {
            swap(arr[j], arr[j - 1]);
            --j;
        }
    }
}

/* =========================
   SELECTION SORT
   -------------------------
   Repeatedly find the smallest element and swap to front
   ========================= */
void selectionSort(int arr[], int n) // 9 10 7 8 11
{
    for (int i = 0; i < n - 1; i++) 
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}

/* =========================
   HEAP SORT
   -------------------------
   Use max-heap structure to extract the largest element
   ========================= */
void heapify(int arr[], int n, int i) 
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) 
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) 
{
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) 
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

/* =========================
   MERGE SORT
   -------------------------
   Divide array, sort halves, merge them
   ========================= */
void merge(int arr[], int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) 
{
    if (left < right) 
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/* =========================
   QUICK SORT
   -------------------------
   Pick a pivot, partition array, and recurse
   ========================= */
int partition(int arr[], int low, int high) 
{
    int pivot = arr[high]; // pivot element
    int i = (low - 1);

    for (int j = low; j < high; j++) 
    {
        if (arr[j] <= pivot) 
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) 
{
    if (low < high) 
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
