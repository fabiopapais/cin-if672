#include <stdio.h>
#include <stdlib.h>

int main() {
    int n_test_cases = 1; scanf("%d", &n_test_cases);
    for (int i = 0; i < n_test_cases; i++) {
        int n_students = 0; scanf("%d", &n_students);
        
        int current_second = 0;
        int seconds[n_students];
        
        for (int j = 0; j < n_students; j++) {
            int enter_second = 0, leave_second = 0; scanf("%d %d", &enter_second, &leave_second);
            
            if (leave_second >= current_second) {
                if (enter_second >= current_second) {
                    seconds[j] = enter_second;
                } else {
                    seconds[j] = current_second;
                }
                current_second = seconds[j] + 1;
            } else seconds[j] = 0;
            printf("%d ", seconds[j]);
        }
        printf("\n");
    } 
    return 0;
}