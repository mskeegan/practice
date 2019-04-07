#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "algo.h"

int* longest_subsequence_slow(int* seq, int n, int& longest_count) {

    longest_count = 0;
    int longest_start_index;
    for (int i = 0; i < n; i++) {
        int count = 0;
        int previous = seq[i];
        for (int j = i+1; j < n; j++) {
            if (seq[j] > previous){
                count++;
                previous=seq[j];
            }
        }
        if (count > longest_count) {
            longest_count = count;
            longest_start_index = i;
        }
    }
    
    // Reconstruct longest subsequence
    int* longest_subseq_index = new int[longest_count];
    int previous = seq[longest_start_index];
    int i = 0;
    longest_subseq_index[i++] = previous;
    for (int j = longest_start_index+1; j < n; j++){
        if (seq[j] > previous ){
            previous = seq[j];
            longest_subseq_index[i++] = previous;
        }
    }
    return longest_subseq_index;
}

int* longest_subsequence_slow_but_optimized(int* seq, int n, int& longest_count) {

    int bytecount = n/8+1;
    std::cout << bytecount << std::endl;
    unsigned char* hits = new unsigned char[bytecount];
    for (int i = 0; i < bytecount; i++) hits[i] = '\0';

    longest_count = 0;
    int longest_start_index;
    for (int i = 0; i < n; i++) {
        if (hits[i/8] & 1<<i%8) continue;
        int count = 0;
        int previous = seq[i];
        for (int j = i+1; j < n; j++) {
            if (seq[j] > previous){
                count++;
                previous=seq[j];
                hits[j/8] |= 1 << (j%8);
            }
        }
        if (count > longest_count) {
            longest_count = count;
            longest_start_index = i;
        }
    }
    delete [] hits;

    // Reconstruct longest subsequence
    int* longest_subseq_index = new int[longest_count];
    int previous = seq[longest_start_index];
    int i = 0;
    longest_subseq_index[i++] = previous;
    for (int j = longest_start_index+1; j < n; j++){
        if (seq[j] > previous ){
            previous = seq[j];
            longest_subseq_index[i++] = previous;
        }
    }
    return longest_subseq_index;
}

//int* previous;
//int* lengths;
int longest_subseq_inner(int* seq, int j, int* lengths, int* previous) {

    if (lengths[j] != -1) return lengths[j];

    lengths[j] = 0;
    if (j == 0) {
        lengths[0] = 1;
        return lengths[0];
    }
    for (int i = 0; i < j; i++) {
        if (seq[j] > seq[i]) {
            int i_length = longest_subseq_inner(seq,i,lengths,previous);
            if (lengths[j] < i_length+1 ) {
                lengths[j] = i_length+1;
                previous[j] = i;
            }
        }
    }
    return lengths[j];
}

int* longest_subsequence_correct(int* seq, int n, int& l) {
    int* lengths = new int[n];
    int* previous = new int[n];
    for (int i = 0; i < n; i++) {
        lengths[i] = -1;
        previous[i] = -1;
    }
    longest_subseq_inner(seq,n-1,lengths,previous);

    l = 0;
    int last_idx = -1;
    for (int i = n-1; i >= 0; i--) {
        if (lengths[i] > l) {
            l = lengths[i];
            last_idx = i;
        }
    }

    int* subseq = new int[l];
    int j = l;
    while (j > 0) {
        subseq[j-1] = seq[previous[last_idx]];
        last_idx = previous[last_idx];
        j--;
        // sanity check last_idx value
    }

    delete [] lengths;
    delete [] previous;
    return subseq;
}

int longest_subseq_inner_slow(int* seq, int j) {

    int length = 0;
    if (j == 0) {
        length = 1;
        return length;
    }
    for (int i = 0; i < j; i++) {
        if (seq[j] > seq[i]) {
            int i_length = longest_subseq_inner_slow(seq,i);
            if (length < i_length+1 ) {
                length = i_length+1;
            }
        }
    }
    return length;
}

void longest_subsequence_correct_slow(int* seq, int n, int& l) {
    l = longest_subseq_inner_slow(seq,n-1);
}

void lsubseq_test() {
    constexpr int n = 100;
    int sequence[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        sequence[i] = rand();
    }
    auto start = std::chrono::high_resolution_clock::now();
    int l = 0;
    int* subseq = longest_subsequence_slow(sequence,n,l);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << "Longest Subesquence Length: " << l << std::endl;
    std::cout << "Subsequence:" << std::endl;
    for (int i = 0; i < l; i++) {
        std::cout << subseq[i] << " ";
        if ((i+1) % 12 == 0 )
            std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Duration " << duration.count() << " microseconds" << std::endl;
    delete [] subseq;

    start = std::chrono::high_resolution_clock::now();
    l = 0;
    subseq = longest_subsequence_slow_but_optimized(sequence,n,l);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << "Longest Subesquence Length: " << l << std::endl;
    std::cout << "Subsequence:" << std::endl;
    for (int i = 0; i < l; i++) {
        std::cout << subseq[i] << " ";
        if ((i+1) % 12 == 0 )
            std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Duration " << duration.count() << " microseconds" << std::endl;
    delete [] subseq;

    start = std::chrono::high_resolution_clock::now(); 
    l = 0;
    subseq = longest_subsequence_correct(sequence,n,l);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << "Longest Subesquence Length: " << l << std::endl;
    std::cout << "Subsequence:" << std::endl;
    for (int i = 0; i < l; i++) {
        std::cout << subseq[i] << " ";
        if ((i+1) % 12 == 0 )
            std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Duration " << duration.count() << " microseconds" << std::endl;
    delete [] subseq;



    start = std::chrono::high_resolution_clock::now();  
    l = 0;
    longest_subsequence_correct_slow(sequence,n,l);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    std::cout << "Longest Subesquence Length: " << l << std::endl;
    std::cout << "Duration " << duration.count() << " microseconds" << std::endl;

}