#include <stdlib.h>
#include <cmath>
#include <iostream>
using namespace std;
#ifndef HASH_FUNCTIONS
#define HASH_FUNCTIONS

int mod_h(int key, int m) {
    return abs(key)%m;
}

int mid_square_h(int key, int m) {
    long long K = (long long int) key*key;
    cout << "K: " << K << " key: " << key << endl; 
    // calculate r, such that 10^r − 1 < m
    int r = 0; while (pow(10, r) - 1 < m) r++; 
    r--;
    cout << "r: " << r << endl; 
    // calculate number of digits
    int num_digits = 0;
    long long temp = K;
    while (temp != 0) {
        temp /= 10;
        num_digits++;
    }
    cout << "ndigits: " << num_digits << endl; 
    temp = K;
    // iterate through K to find r middle digits 
    // the iteration starts from the less important decimal number to the most important
    // because of that you need to multiply by 10, 100, 1000, ...
    long long result = 0;
    int left_side = (int) (num_digits / 2) - (r / 2), right_side = left_side + r;
    cout << "leftside: " << left_side << " right_side: " << right_side << endl; 
    long decimal_counter = 1;
    for (int i = 0; i < num_digits; i++) {
        int current_digit = temp % 10;
        if (i >= left_side && i < right_side) {
            result += current_digit * decimal_counter; // inserts every number with decimal importance
            decimal_counter *= 10;
        }
        temp /= 10;
    }

    return abs(result) % m; // ensuring it stays in correct range
}

int fold_h(string key, int m) {
    long sum = 0;
    for (int i = 0; i < key.size(); i++) {
        sum += key[i];
    }
    return abs(sum) % m;
}


int sfold_h(string key, int m) {
    int substrings_lenght = key.size() / 4;
    int sum = 0;
    string sub;
    int mult;
    // Folds substrings with lenght 4
    for (int i = 0; i < substrings_lenght; i++) {
        sub = key.substr(i*4, 4);
        mult = 1;
        for (int j = 0; j < 4; j++) {
            sum += sub[j] * mult;
            mult *= 256;
        }
    }
    sub = key.substr(substrings_lenght * 4);
    mult = 1;
    // Folds remaining substring
    for (int i = 0; i < sub.size(); i++) {
        sum += sub[i] * mult;
        mult *= 256;
    }  
    
    return abs(sum) % m;
}

#endif