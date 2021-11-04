#include <stdlib.h>

#include "cell.h"
#include "client.h"

struct Cell* cell_new_empty_cells() {

	/* Allouer un espace memoire pour une nouvelle cellule */

	struct Cell* p_new = (struct Cell*)malloc(sizeof(*p_new));

	return p_new;
}

struct Cell* cell_new(struct Client* p_client, int key) {

	/* Allouer un espace memoire pour une nouvelle cellule */

	struct Cell* p_new = (struct Cell*)malloc(sizeof(*p_new));

	/* Verifier si la call malloc a fonctionné */

	if (p_new != NULL) {

		/* Initialiser les données membres de nouvelle cellule avec le client et la clé donnés en parametre */

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