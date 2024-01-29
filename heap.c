/*
 * heapsort.c
 *
 *  Created on: Jul 1, 2013
 *      Author: Alex
 */
#include <stdio.h>
#include <stdlib.h>
#include "employee.h"
#include "heap.h"

/**
 * Sorts a list of n employees in descending order
 *
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the heap
 */
void heapSort(Employee *A, int n)
{
	// BuildHeap on the heap
	buildHeap(A, n);

	// while n > 0:
	while (n > 0) {
		// swap A[n-1] with A[0], since A[0] is the smallest number.
		swap(A + n - 1, A);
		// A[n-1] now sorted in place, so decrement n
		n--;
		//Heapify the elements from A[0] up to A[n-1] (which leaves the newly sorted element alone)
		heapify(A, 0, n);
	}
}

/**
 * Given an array A[], we want to get A[] into min-heap property
 * We only need to run heapify() on internal nodes (there are floor(n/2) of them)
 * and we need to run it bottom up (top-down cannot build a heap)
 *
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the heap
 */
void buildHeap(Employee *A, int n)
{
	// heapify() every element from A[n/2] down-to A[0]
	for (int i = n/2; i >= 0; i--) {
		heapify(A, i, n);
	}
}

/**
 * We want to start with A[i] and percolate it downward
 * if it is greater than either left or right child.
 *
 * @param	*A	Pointer to the list of employees
 * @param	i	Index of current element to heapify
 * @param	n	Size of the heap
 */
void heapify(Employee *A, int i, int n)
{
	// if the node on which we are trying to heapify has no children, then there is nothing left to do. Base case.
	if (2*i + 1 >= n) {
		return;
	}
	// if the node on which we are trying to heapify has one child which is smaller, then swap
	if (2*i + 2 >= n && A[2*i + 1].salary < A[i].salary) {
		swap(A + 2*i + 1, A + i);
	}
	// if the node on which that we are trying to heapify has one child, return. base case.
	if (2*i + 2 >= n) {
		return;
	}

	// get index of left child of element i
	Employee *leftChild = A + (i * 2) + 1;
	
	// get index of right child of element i
	Employee *rightChild = A + (i * 2) + 2;
	// determine which child has a smaller salary. We'll call the index of this element: "smaller"
	Employee *smaller = leftChild->salary < rightChild->salary ? leftChild : rightChild;

	// recursively check if the salary at A[i] > the salary at A[smaller]. If it is, swap the two.
	if (smaller->salary < A[i].salary) {
		swap(smaller, A + i);
	}
	// Continue recursion as long as i is within range AND either right_child and left_child are still within range.
	heapify(A, smaller - A, n);
}

/**
 * Swaps the locations of two Employees
 * @param *e1 An Employee
 * @param *e2 Another Employee to swap with
 */
void swap(Employee *e1, Employee *e2)
{
	Employee temp = *e1;
	*e1 = *e2;
	*e2 = temp;
}

/**
 * Outputs an array of Employees
 * @param	*A	Pointer to the list of employees
 * @param	n	Size of the list
 */
void printList(Employee *A, int n)
{
	for (int i = 0; i < n - 1; i++) {
		printf("[id=%s sal=%d], ", A[i].name, A[i].salary);
	}
	printf("[id=%s sal=%d]\n", A[n-1].name, A[n-1].salary);
}
