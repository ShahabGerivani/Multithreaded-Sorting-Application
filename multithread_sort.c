#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int initial_array[SIZE] = {234, 4, 54, 67, 87, 64, 22, 4, 78, 9};
int sorted_array[SIZE];

void *sort(void *start);
void *merge();

int main()
{
    pthread_t sort_thread1, sort_thread2, merge_thread;
    pthread_attr_t sort_thread1_attr, sort_thread2_attr, merge_thread_attr;

    pthread_attr_init(&sort_thread1_attr);
    pthread_create(&sort_thread1, &sort_thread1_attr, sort, initial_array);
    
    pthread_attr_init(&sort_thread2_attr);
    pthread_create(&sort_thread2, &sort_thread2_attr, sort, &initial_array[SIZE / 2]);

    pthread_join(sort_thread1, NULL);
    pthread_join(sort_thread2, NULL);

    pthread_attr_init(&merge_thread_attr);
    pthread_create(&merge_thread, &merge_thread_attr, merge, NULL);
    pthread_join(merge_thread, NULL);

    printf("Sorted array: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", sorted_array[i]);
}

// Source: https://www.geeksforgeeks.org/selection-sort-algorithm-2/
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
      
        // Assume the current position holds
        // the minimum element
        int min_idx = i;
        
        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
              
                // Update min_idx if a smaller element is found
                min_idx = j;
            }
        }
        
        // Move minimum element to its
        // correct position
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void *sort(void *start)
{
    selectionSort(start, SIZE / 2);
    pthread_exit(0);
}

void *merge()
{
    int i = 0, j = SIZE / 2;
    for (int k = 0; k < SIZE; k++)
    {
        if ((initial_array[i] < initial_array[j] && i < SIZE / 2) || j >= SIZE)
        {
            sorted_array[k] = initial_array[i];
            i++;
        }
        else
        {
            sorted_array[k] = initial_array[j];
            j++;
        }
    }
    
    pthread_exit(0);
}
