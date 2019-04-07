#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

bool is_palindrome(char* seq, int s, int l) {
    int i = l/2;
    for (int j = 0; j < i; j++) {
        if (seq[s+j] != seq[s+l-1-j])
            return false;
    }
    return true;
}

int longest_palindrome_slow(char* seq, int n, char** pal){

    int max_length = 0;
    int start = -1;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j <n; j++) {
            int length = j-i;
            if (is_palindrome(seq,i,length)) {
                if (length > max_length){
                    max_length = length;
                    start = i;
                }
            }
        }
    }

    (*pal) = new char[max_length];
    for (int i = 0; i < max_length; i++){
        (*pal)[i] = seq[start+i];
    }
    return max_length;
}

int longest_palindrome_fast(char* seq, int n, char** pal) {

    int max_length = 0;
    int middle = -1;
    for (int i = 0; i < n; i++) {
        int max_possible = i < n-i-1 ? i : n-i-1;
        for (int c = 0; c <= max_possible; c++) {
            if (seq[i-c] != seq[i+c] ) {
                break;
            }
            int length = 1+2*c;
            if (length > max_length) {
                max_length = length;
                middle = i;
            }
        }
        if (i == n-1) break;
        for (int c = 0; c <= max_possible; c++) {
            if (seq[i-c] != seq[i+c+1] ) {
                break;
            }
            int length = 2*(c+1);
            if (length > max_length) {
                max_length = length; 
                middle = i;
            }
        }
    }

    (*pal) = new char[max_length];
    int s = middle - max_length/2;
    if (max_length%2 == 0) s = middle-max_length/2+1;
    for (int i = 0; i < max_length; i++)
        (*pal)[i] = seq[s+i];
    return max_length;
}


void palindrome_test() {
    constexpr int n = 100000;
    char* seq = new char[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        seq[i] = (char)((int)'a' + (rand()%10));
    }
    char* palindrome;
    auto start = std::chrono::high_resolution_clock::now();
    int l = longest_palindrome_slow(seq,n,&palindrome);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);

    std::cout << "Longest Palindrome Length: " << l << std::endl;
    std::cout << "Palindrome: " << std::endl;
    for (int i = 0; i < l; i++) {
        std::cout << palindrome[i] << " ";
        if ((i+1) % 12 == 0 )
            std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Duration " << duration.count() << " microseconds" << std::endl;
    delete [] palindrome;   

    start = std::chrono::high_resolution_clock::now();
    l = longest_palindrome_fast(seq,n,&palindrome);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);

    std::cout << "Longest Palindrome Length: " << l << std::endl;
    std::cout << "Palindrome: " << std::endl;
    for (int i = 0; i < l; i++) {
        std::cout << palindrome[i] << " ";
        if ((i+1) % 12 == 0 )
            std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Duration " << duration.count() << " microseconds" << std::endl;
    delete [] palindrome;

/*    std::cout << std::endl << "Full String: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << seq[i] << " ";
        if ((i+1) % 25 == 0 )
            std::cout << std::endl;
    }
*/
    delete [] seq;
}