#pragma once

#include <vector>
#include <iostream>

using std::vector;
using std::cout;

void bubbleSort(int* array, int len);

void insertSort(int* array, int len);

void merge_sort(vector<int>& array, int left, int rigth);

void merger_sortV2(int* array, int left, int right);

void quickSort(vector<int>& array, int left, int right);

void f(const char* s);