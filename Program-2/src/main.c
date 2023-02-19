/**
 * @file main.c
 * @author Emily Tso (tsoemily@ku.edu)
 * @brief EECS 348 Lab 3 Program 2: Prints out all the possible combinations of scoring plays.
 * @version 0.1
 * @date 2023-02-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define SIZE 5

typedef enum {
	TOUCHDOWN,
	TOUCHDOWN_ONE_POINT,
	TOUCHDOWN_TWO_POINT,
	FIELDGOAL,
	SAFETY,
} POINTS;

typedef struct {
	POINTS points;
	int max;
	int amount;
} Values;

static Values values[SIZE] = {
	{TOUCHDOWN_TWO_POINT, 0, 0},
	{TOUCHDOWN_ONE_POINT, 0, 0},
	{TOUCHDOWN, 0, 0},
	{FIELDGOAL, 0, 0},
	{SAFETY, 0,0},
};

int get_points(POINTS points) {
	switch (points) {
		case TOUCHDOWN_TWO_POINT: 
			return 8;
		case TOUCHDOWN_ONE_POINT:
			return 7;
		case TOUCHDOWN:
			return 6;
		case FIELDGOAL:
			return 3;
		case SAFETY:
			return 2;
		default:
			return 0;
	}
}

int allocate_max(int amount, POINTS points) {
	int value = get_points(points);
	int max = amount / value;
	return max;
}

int shift(int i) {
	static int done = 0;
	if (done) return 1;
	values[i].amount++;
	if (values[i].amount >= values[i].max) {
		values[i].amount = 0;
		switch (i) {
			case 0: done = 1;
				break;
			default: shift(i-1);
		}
	}
	return 0;
}

void print_values() {
	printf("possible combinations of scoring plays: \n");
	for (int i = 0; i < SIZE; i++) {
		printf("%i", values[i].amount);
		switch(values[i].points) {
			case SAFETY:
				printf(" Safety ");
				break;
			case FIELDGOAL:
				printf(" 3pt FG, ");
				break;
			case TOUCHDOWN_TWO_POINT:
				printf(" TD + 2pt, ");
				break;
			case TOUCHDOWN_ONE_POINT:
				printf(" TD + FG, ");
				break;
			case TOUCHDOWN:
				printf(" TD, ");
				break;
		}
	}
	printf("\n");
}


void func(const int pts) {
	int total = 0;
	for (int i = 0; i < SIZE; i++) {
		total += get_points(values[i].points) * values[i].amount;
	}
	if (total == pts)
		print_values();
}

void iterate(int nPoints) {
	do {
		func(nPoints);
	} while(shift(SIZE - 1) == 0);
}

void nfl_permutation(const int nPoints) {
	for (int i = 0; i < SIZE; i++) 
		values[i].max = allocate_max(nPoints, values[i].points);
	iterate(nPoints);
}

int main() {
	int choice;
	printf("Enter 1 or 0 to STOP: ");
	scanf("%i", &choice);
	fflush(stdin);

	switch (choice) {
		case 0:
		case 1:
			break;
		default:
			printf("Enter the NFL score: ");
			scanf("%i", &choice);
			fflush(stdin);
			nfl_permutation(choice);
	}
	return 0;
}