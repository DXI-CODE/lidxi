#pragma once
#include "class_knn.h"
#include <stdio.h>
#include <stdlib.h>

void merge(JEF *arr, short left, short mid, short right) {
    short i, j, k;
    short n1 = mid - left + 1;
    short n2 = right - mid;

    JEF *L = (JEF *) malloc(n1 * sizeof(JEF));
    JEF *R = (JEF *) malloc(n2 * sizeof(JEF));

    if (L == NULL || R == NULL) return;

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;

    // Orden descendente: mayor a menor
    while (i < n1 && j < n2) {
        if (L[i].cont >= R[j].cont) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(JEF *arr, short left, short right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
