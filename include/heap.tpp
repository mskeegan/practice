// heap.tpp
// contains the Heap<> template implementation

template <typename T>
Heap<T>::Heap() : nElements(0), maxElements(DEFAULT_SIZE) {
    heap = new T[DEFAULT_SIZE];
}

template <typename T>
Heap<T>::Heap(size_t length) : nElements(0), maxElements(length){
    heap = new T[length];
}

template <typename T>
Heap<T>::~Heap() {
    delete [] heap;
}

template <typename T>
void Heap<T>::insert(T e) {
    if (nElements >= maxElements){
        // deal with error case
        exit(1);
    }
    heap[nElements] = e;
    percolate_up(nElements);
    nElements++;
}

template <typename T>
void Heap<T>::percolate_up(size_t n) {

    if (n == 0) return;

    size_t parent = (n-1)/2;
    if (heap[parent] > heap[n]) {
        T tmp = heap[parent];
        heap[parent] = heap[n];
        heap[n] = tmp;
        percolate_up(parent);
    }
}

template <typename T>
bool Heap<T>::is_empty() {
    return nElements == 0;
}

template <typename T>
T Heap<T>::get_top() {
    T top = heap[0];
    nElements--;
    if (!is_empty()) {
        heap[0] = heap[nElements];
        percolate_down(0);
    }
    return top;
}

template <typename T>
void Heap<T>::percolate_down(size_t n) {
    if (nElements <= 1) return;
    size_t child_left = n*2+1;
    size_t end_of_array = nElements-1;
    if (child_left > end_of_array) return; 
    size_t child_right = n*2+2;
    bool has_right_child = child_right <= end_of_array;
    if (!has_right_child || heap[child_left] < heap[child_right]){
        if (heap[child_left] < heap[n]){
            T tmp = heap[child_left];
            heap[child_left] = heap[n];
            heap[n] = tmp;
            percolate_down(child_left);
        }
    }else if (heap[child_right] < heap[n]) {
        T tmp = heap[child_right];
        heap[child_right] = heap[n];
        heap[n] = tmp;
        percolate_down(child_right);
    }
}

template <typename T>
void Heap<T>::print(){
    int l = 0;
    int p = 1;
    for (int i = 0; i < static_cast<int>(nElements); i++){
        cout << heap[i];
        if (l == 0 || i % l == 0){
            cout << endl;
            p *= 2;
            l += p;
            
        }
        else
            cout << ' ';
    }
}