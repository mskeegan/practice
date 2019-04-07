#include <cstdlib>
#include <iostream> 

using namespace std;

template <typename T> class Heap{
public: 
    Heap();
    Heap(size_t l);
    ~Heap();

    void insert(T e);
    T get_top();
    bool is_empty();
    void print();

private:
    T* heap;
    size_t nElements;
    size_t maxElements;
    const size_t DEFAULT_SIZE = 1000;

    void percolate_up(size_t n);
    void percolate_down(size_t n);
};

// include Heap<> implementation
#include "heap.tpp"