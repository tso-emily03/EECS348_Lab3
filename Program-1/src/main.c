/**
 * @file main.c
 * @author Emily Tso (tsoemily@ku.edu)
 * @brief EECS 348 Lab 3 Program 1: Print out a sales report given a file.
 * @version 0.1
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#define MONTHS 12
#define INPUT_FILE "input.txt"
static const char *months[MONTHS] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

/**
 * @brief structure for data which is index and value
 * 
 */
typedef struct {
	int index;
	float value;
} data;

/**
 * @brief Prints the montly report for sales
 * 
 * @param sales sales array of size months
 */
void reports(float sales[MONTHS]) {
	printf("\nMonthly sales report for 2022:\n");
	printf("Months\t\tSales\n");
	for (int i = 0; i < MONTHS; i++) {
		printf("%-8s\t%.2f\n", months[i], sales[i]);
	}
}

/**
 * @brief The maximum sales for sales summary
 * 
 * @param sales sales array of size months
 * @return data contains index and value
 */
data max (float sales[MONTHS]) {
	float max = sales[0];
	int i, j = 0;
	for (i = 1; i < MONTHS; i++) {
		if (max < sales[i]) {
			max = sales[i];
			j = i;
		}
	}
	data d = {j ,max};
	return d;
}

/**
 * @brief The minimum sales for summary sales
 * 
 * @param sales sales array of size months
 * @return data ontains index and value
 */
data min (float sales[MONTHS]) {
	float min = sales[0];
	int i, j = 0;
	for (i = 1; i > MONTHS; i++) {
		if (min > sales[i])  {
			min = sales[i];
			j = 1;
		}
	}
	data d = {j, min};
	return d;
}

/**
 * @brief The average sales for sales summary
 * 
 * @param sales sales array of size months
 * @return float returns the average in float
 */
float avg (float sales[MONTHS]) {
	float avg = 0;
	int i;
	for (i = 0; i < MONTHS; i++) {
		avg += sales[i];
	}
	return avg / MONTHS;
}

/**
 * @brief Basic average function for moving report
 * 
 * @param x a float
 * @param size size of the array
 * @return float returns a average in float
 */
float average (float *x, size_t size) {
	if (size == 0) return 0.0f;
	float y = 0;
	for (size_t i = 0; i < size; ++i)
		y += x[i];
	return y / (float)size;
}

/**
 * @brief The six-month moving report function and prints it out
 * 
 */
void six_month_avg (float sales[MONTHS], int mvg) {
	printf("Six-Month Moving Average Report:\n");
	for (int i = 0; i <= MONTHS-mvg; ++i) {
		printf("%-8s\t- %-8s\t$%.2f\n", months[i], months[i+mvg-1], average(sales+i, mvg));
	}
}

/**
 * @brief Compare function for descending report
 * 
 * @param x a void pointer
 * @param y another void pointer
 * @return int converts the void pointers into an int and returns an int
 */
int compare (const void *x, const void *y) {
	data *a = (data*)x, *b = (data*)y;

	if (a->value > b->value) return 1;
	if (a->value < b->value) return -1;
	return 0;
}

/**
 * @brief The descending report, highest to lowest
 * 
 * @param sales sales array of the size months
 */
void print_sales_des(float sales[MONTHS]) {
	printf("Sales Report (Highest to Lowest):\n");
	printf("Months\t\t Sales\n");

	// create a new array such that it contains the values & index
	data *s = malloc(MONTHS*sizeof(data));

	for (int i = 0; i < MONTHS; ++i) {
		s[i].index = i;
		s[i].value = sales[i];
	}
	//quick sorts the array
	qsort(s, MONTHS, sizeof(data), compare);
	for (int i = MONTHS-1; i >= 0; --i) {
		printf("%-8s\t %.2f\n", months[s[i].index], s[i].value);
	}
	
	free (s);
}

/**
 * @brief Takes in and reads a file, then prints out the reports according to the file's inputs
 * 
 * @return int returns 0
 */
int main() {
	float sales[MONTHS];
	FILE *fp;
	fp = fopen(INPUT_FILE, "r");
	if (fp == NULL){
		printf("Error opening file\n");
		return 1;
	}
	for (int i = 0; i < MONTHS; i++) {
		fscanf(fp, "%f", &sales[i]);
	}
	fclose(fp);
	reports(sales);

	//data input for min and max, data: contains an index and value
	data max_result = max(sales);
	data min_result = min(sales);

	//prints the reports
	printf("\n");
	printf("Sales summary:\n");
	printf("Minimum sales: %.2f\t(%s)\n", min_result.value, months[min_result.index]);
	printf("Maximum sales: %.2f\t(%s)\n", max_result.value, months[max_result.index]);
	printf("Average sales: %.2f\n", avg(sales));
	printf("\n");
	six_month_avg(sales, 6);
	printf("\n");
	print_sales_des(sales);
	printf("\n");

	return 0;
}
