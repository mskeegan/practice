#include <chrono>
#include <memory>
#include <iostream>

#include "algo.h"
#include "data_structs.h"

using namespace std;

template <typename T>
inline void swap_vals(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}


template <typename T>
void heap_sort(T* list,size_t n) {
    Heap<T>* h_p = new Heap<T>(n);
    for (size_t i = 0; i < n; i ++) {
        h_p->insert(list[i]);
    }

    int c = 0;
    while(!h_p->is_empty()){
        list[c++] = h_p->get_top();
    }
    delete h_p;
}

template <typename T>
void bubble_sort(T* list, size_t n) {
    
    bool bubbled;
    do {
        bubbled = false;
        for (size_t i = 1; i < n; i++) {
            if (list[i-1] > list[i]){
                swap_vals(list[i-1],list[i]);
                bubbled = true;
            }
        }   
    } while(bubbled);
}

template <typename T> 
void insertion_sort(T* list, size_t n) {
    for (size_t i = 1; i < n; i++) {
        size_t j = i;
        while (j > 0 && list[j] < list[j-1]) {
            swap_vals(list[j-1],list[j]);
            j--;
        } 
    }
}

template <typename T>
void selection_sort(T* list, size_t n) {

    for (size_t i = 0; i < n; i++) {
        T next_smallest = list[i];
        size_t smallest_index = i;
        for (size_t j = i+1; j < n; j++) {
            if (list[j] < next_smallest){
                smallest_index = j;
                next_smallest = list[j];
            }
        }
        if (smallest_index != i) {
            list[smallest_index] = list[i];
            list[i] = next_smallest;
        }
    }
}

template<typename T>
void merge_sorted_arrays(const T* list1, size_t n, const T* list2, size_t m, T* sorted){

    if (!list1 || !list2 || !sorted) return; // Error case
    size_t i = 0, j = 0, k = 0;
    while (i < n && j < m){
        sorted[k] = list1[i] <= list2[j] ? list1[i++] : list2[j++];
        k++;
    }
    for (; i < n;)
        sorted[k++] = list1[i++];
    for (; j < m;)
        sorted[k++] = list2[j++];
}

template<typename T>
void copy_array(const T* src, T* target, size_t n) {
    for (size_t i = 0; i < n; i++){
        target[i] = src[i];
    }
}

template<typename T>
void merge_sort_inner(T* list, size_t x, size_t y) {
    if ( y <= x) return; // Deal with error case x>y 
    size_t array_length = y-x+1;
    size_t mid = x + array_length/2;
    merge_sort_inner(list,x,mid-1);
    merge_sort_inner(list,mid,y);
    T* sorted = new T[array_length];
    merge_sorted_arrays(list+x,mid-x,list+mid,y-mid+1,sorted);
    copy_array(sorted,list+x,array_length);
    delete [] sorted;
}

template <typename T>
void merge_sort(T* list, size_t n) {
    merge_sort_inner(list,0,n-1);
}

template <typename T>
void quick_sort_inner(T* list, size_t x, size_t y) {
    if (x >= y) return;
    size_t p = y;
    size_t firsthigh = x;
    for (size_t i = x; i < y; i++) {
        if (list[i] <= list[p]) {
            if (i != firsthigh){
                swap_vals(list[firsthigh],list[i]);
            }
            firsthigh++;
        }
    }
    if (p != firsthigh){
        swap_vals(list[firsthigh],list[p]);
    }

    quick_sort_inner(list,x,firsthigh-1);
    quick_sort_inner(list,firsthigh+1,y);
}

template <typename T>
void quick_sort(T* list, size_t n) {
    quick_sort_inner(list,0,n-1);
}

template <typename T>
void time_sort(T* list, int n, void (*sort)(T* list, size_t n)) {
    auto start = chrono::high_resolution_clock::now();
    sort(list,n);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
    cout << "sort time(ms): " << duration.count() << endl;
}

template <typename T>
void print_sort(T* list, int n) {
    if (n < 100) {
        for (int i = 0; i < n; i++) {
            cout << list[i];
            if ( (i+1) % 15 == 0)
                cout << endl;
            else
                cout << ' ';
        }
    }
    cout << endl;
}

template <typename T>
void run_sort(const T* list, int n, void (*sort)(T* list, size_t n)) {
    int* tlist = new int[n];
    for (int i = 0; i < n; i++)
        tlist[i] = list[i];
    time_sort(tlist,n,sort);
    print_sort(tlist,n);
    delete [] tlist;
}

void test_sorts(){
    // randomly generate array to sort
    constexpr int N = 20;
    int* list = new int[N];
    srand(time(0));
    for (int i = 0; i < N; i++)
        list[i] = rand()%1024;

    /*cout << "Heap Sort" << endl;
    run_sort(list,N,&heap_sort);
    cout << "Insertion Sort" << endl;
    run_sort(list,N,&insertion_sort);
    cout << "Selection Sort" << endl;
    run_sort(list,N,&selction_sort);
    cout << "Merge Sort" << endl;
    run_sort(list,N,&merge_sort);*/
    cout << "Quick Sort" << endl;
    run_sort(list,N,&quick_sort);

    delete [] list;
}