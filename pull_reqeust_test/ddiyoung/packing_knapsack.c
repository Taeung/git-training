/*
 * Packing knapsack question
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 16

struct knapsack {
	unsigned int limited_wgt;
	unsigned int max_price;
};

struct jewelry {
	unsigned int wgt;
	unsigned int price;
};

void pack_knapsack(struct knapsack *knapsack_list,
		      struct jewelry **usable_jewels)
{
	/* Case by case pack knapsack following maximum
	 * price per limited weight.
	 */
}

int get_maxprice(struct knapsack *knapsack_list, struct jewelry *jewelry)
{
	/* Get maximum price based on limited weight */
}

bool get_values_from(char *input, int *val1, int *val2)
{
	char *ptr = input;

	*val1 = atoi(strsep(&ptr, " "));
	if (ptr == NULL) {
		printf("Error: Need a whitespace\n");
		return false;
	}

	*val2 = atoi(ptr);

	if (*val1 == 0 || *val2 == 0) {
		printf("Error: Input have to contain only numbers\n");
		return false;
	}

	return true;
}

int main(int argc, const char **argv)
{
	char input[MAX_INPUT];
	char *ptr = input;
	int nr_jewels, limited_wgt;
	struct jewelry *jewels;
	struct knapsack *knapsack_list;

	fgets(input, sizeof(input), stdin);
	if (get_values_from(input, &nr_jewels, &limited_wgt) == false)
		return -1;

	jewels = malloc(sizeof(struct jewelry) * nr_jewels);
	for (int i = 0; i < nr_jewels; i++) {
		bool ret;

		fgets(input, sizeof(input), stdin);
		ret = get_values_from(input, &jewels[i].wgt,
				      &jewels[i].price);
		if (ret == false)
			return -1;
	}

	knapsack_list = malloc(sizeof(struct knapsack) * limited_wgt);

	for (int i = 0; i < nr_jewels; i++) {
		struct jewelry **usable_jewels = malloc(sizeof(struct jewelry *)
							* (i + 1));

		for (int j = 0; j <= i; j++)
			usable_jewels[i] = &jewels[j];
		pack_knapsack(knapsack_list, usable_jewels);
		free(usable_jewels);
	}

	printf("%d\n", knapsack_list[limited_wgt-1].max_price);
	free(jewels);
	free(knapsack_list);
	return 0;
}
