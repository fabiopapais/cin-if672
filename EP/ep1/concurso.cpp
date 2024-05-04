#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

struct applicant {
    string name;
    int score;
    int age;
};


void merge(applicant* array, int l, int r) {
    applicant unsorted_applicants[r + 1]; // ATTENTION 
    for (int x = l; x <= r; x++) unsorted_applicants[x] = array[x];
    int m = (l + r) / 2;
    int i1 = l; int i2 = m + 1;

    for (int curr = l; curr <= r; curr++) {
        if (i1 == m + 1) {
            array[curr] = unsorted_applicants[i2++];
        } else if (i2 > r) {
            array[curr] = unsorted_applicants[i1++];
        } else { // bloco das comparações score -> age -> index
            if (unsorted_applicants[i1].score < unsorted_applicants[i2].score) {
                array[curr] = unsorted_applicants[i1++];
            } else if (unsorted_applicants[i1].score > unsorted_applicants[i2].score) {
                array[curr] = unsorted_applicants[i2++];
            } else {
                if (unsorted_applicants[i1].age < unsorted_applicants[i2].age) {
                    array[curr] = unsorted_applicants[i1++];
                } else if (unsorted_applicants[i1].age > unsorted_applicants[i2].age) {
                    array[curr] = unsorted_applicants[i2++];
                } else {
                    if (i1 < i2) {
                        array[curr] = unsorted_applicants[i2++];
                    } else if (i1 > i2) {
                        array[curr] = unsorted_applicants[i1++];
                    }
                }
            }
        }
    }
}

void mergesort(applicant* array, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergesort(array, l, m);
        mergesort(array, m + 1, r);
        merge(array, l, r);
    }
}

int main() {
    int positions; scanf("%d", &positions);
    for (int i = 0; i < positions; i++) {
        int applicants_qty = 0; scanf("%d", &applicants_qty);
        int jobs_qty = 0; scanf("%d", &jobs_qty);

        applicant* applicants = new applicant[applicants_qty];

        for (int j = 0; j < applicants_qty; j++) {
            char name_buffer[30]; int score; int age;
            scanf("%s", name_buffer); scanf("%d", &score); scanf("%d", &age);
            string name = name_buffer;
            applicant new_applicant = {.name = name, .score = score, .age = age};
        
            applicants[j] = new_applicant;
        }

        mergesort(applicants, 0, applicants_qty - 1);
        
        cout << "cargo " << i + 1 << ":" << endl;
        for (int j = applicants_qty - 1; j >= applicants_qty - jobs_qty; j--) {
            if (j < 0) {
                cout << "x" << endl;
            } else {
                cout << applicants[j].name << endl;
            }
        }

        delete[] applicants;
    }
}