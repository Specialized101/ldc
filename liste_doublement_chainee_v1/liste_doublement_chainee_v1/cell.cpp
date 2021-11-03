#include <stdlib.h>
#include <iostream>

#include "ldc.h"
#include "cell.h"
#include "client.h"

struct Cell* cell_new_empty_cells() {

	struct Cell* p_new = (struct Cell*)malloc(sizeof(*p_new));

	return p_new;
}

struct Cell* cell_new(struct Client* p_client, int key) {

	struct Cell* p_new = (struct Cell*)malloc(sizeof(*p_new));

	if (p_new != NULL) {

		p_new->client = p_client;
		p_new->key = key;
		p_new->p_next = NULL;
		p_new->p_prev = NULL;

	}

	return p_new;

}

struct Cell* cell_del(struct Cell* p_cell) {

	if (p_cell != NULL) {

		free(p_cell);
		p_cell = NULL;

	}

	return p_cell;

}