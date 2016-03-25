/*
 * Packing knapsack question
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>

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

int main(int argc, const char **argv)
{
}
