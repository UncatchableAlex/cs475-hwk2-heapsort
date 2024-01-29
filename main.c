#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"
#include "heap.h"
#define MAX_EMPLOYEES 7
int main(int argc, char *argv[])
{
	// allocate memory on the heap to store all the employees:
	Employee *A = (Employee*) malloc(sizeof(Employee) * MAX_EMPLOYEES);
	for (int i = 0; i < MAX_EMPLOYEES; i++) {
		// get the ith employee's name:
		printf("Name: ");
		fgets((char*) &A[i].name, MAX_NAME_LEN, stdin);
		// remove the last letter that the user entered (because it was a newline)
		A[i].name[strlen(A[i].name) - 1] = '\0';
		// get the ith employee's salary:
		printf("Salary:  ");
		// allocate enough characters in the stack to store INT_MIN (a negative sign + 10 digits + \0 terminator = 12 chars).
		char decimalInput[12];
		char *endPtr;
		// keep scanning for the ith employee's salary until the user gives it:
		do {
			fgets((char*) &decimalInput, sizeof(decimalInput), stdin);
			// fitting a long into an int may result in overflow, but the provided solution allows int overflows, so it's probably okay:
			A[i].salary = strtol(decimalInput, &endPtr, 10);
			// If the last character registered wasn't a newline, then there still is stuff remaining in the
			// input buffer that will mess with us if we don't clear it. https://stackoverflow.com/a/7898516:
			int c;
			if (decimalInput[strlen(decimalInput) - 1] != '\n') {
				while ((c = getc(stdin)) != '\n' && c != EOF) {}
			}
		} while (endPtr == decimalInput); // while we didn't read any numbers

		printf("\n");
	}
	heapSort(A, MAX_EMPLOYEES);
	printList(A, MAX_EMPLOYEES);
	free(A);
	A = NULL;
	return 0;
}
