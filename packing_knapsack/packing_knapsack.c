/*
 * Packing knapsack question
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
<<<<<<< HEAD
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 16

struct knapsack {
	unsigned int maxprice;
} *knapsack_list;

struct jewelry {
	unsigned int wgt;
	unsigned int price;
};

unsigned int limited_wgt;

unsigned int get_cond_maxprice(int wgt, struct jewelry *jewelry)
{
	/* Get maximum price based on a specific weight
	 * following a specific jewelry.
	 */
	int i;
	int rest_wgt = wgt - jewelry->wgt;
	int price = jewelry->price + knapsack_list[rest_wgt].maxprice;

	return knapsack_list[wgt].maxprice < price ?
		price : knapsack_list[wgt].maxprice;
}

void pack_knapsack(struct jewelry *jewelry)
{
	/* Case by case pack knapsack following maximum
	 * price per limited weight.
	 */
	int wgt;

	if (limited_wgt < jewelry->wgt)
		return;

	for (wgt = 0; wgt <= limited_wgt; wgt++) {
		if (jewelry->wgt <= wgt) {
			unsigned int maxprice = get_cond_maxprice(wgt, jewelry);

			if (knapsack_list[wgt].maxprice < maxprice)
				knapsack_list[wgt].maxprice = maxprice;
		}
	}
}

bool get_values_from(char *input, unsigned int *val1, unsigned int *val2)
{
	char *arg;
	char *ptr = strdup(input);

	if (!ptr) {
		printf("%s: strdup failed\n", __func__);
		exit(1);
	}

	arg = strsep(&ptr, " ");
	*val1 = atoi(arg);
	if (ptr == NULL) {
		printf("Error: Need a whitespace\n");
		return false;
	}

	*val2 = atoi(ptr);

	return true;
=======

void grade_price_per_wgt(int price_per_wgt_list[])
{
	/* Arrange each value in order of price per 1 weight */
}

int get_nr_of_try(int kinds)
{
	/* Get the number of try that check whether
	 * some result value is most close to theoretical maximum
	 */
}

int get_theor_maximum(int price_per_wgt_list[])
{
	/* Get a theoretical maximum following the highest
	 * price per 1 weight.
	 */
}

int get_cond_maximum(int price_per_wgt_list[], int exclu_index,
		     int vital_index)
{
	/* Get a maximum with condition that some values
	 * should be included or excluded.
	 */
>>>>>>> f9b87bb... packing knapsack: Basic code solving this question
}

int main(int argc, const char **argv)
{
<<<<<<< HEAD
	int i;
	struct jewelry *jewels;
	char input[MAX_INPUT];
	unsigned int nr_jewels;

	fgets(input, sizeof(input), stdin);
	if (get_values_from(input, &nr_jewels, &limited_wgt) == false)
		return -1;

	jewels = malloc(sizeof(struct jewelry) * nr_jewels);
	for (i = 0; i < nr_jewels; i++) {
		bool ret;

		fgets(input, sizeof(input), stdin);
		ret = get_values_from(input, &jewels[i].wgt,
				      &jewels[i].price);
		if (ret == false)
			return -1;
	}

	/* from 0 to last limited weight */
	knapsack_list = malloc(sizeof(struct knapsack) * (limited_wgt + 1));

	for (i = 0; i <= limited_wgt; i++)
		knapsack_list[i].maxprice = 0;

	for (i = 0; i < nr_jewels; i++)
		pack_knapsack(&jewels[i]);

	printf("%d\n", knapsack_list[limited_wgt].maxprice);
	free(jewels);
	free(knapsack_list);
	return 0;
=======
>>>>>>> f9b87bb... packing knapsack: Basic code solving this question
}
