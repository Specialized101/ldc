#include <stdlib.h>

#include "cell.h"
#include "client.h"

struct Cell* cell_new(struct Client* p_client) {

	/* Allouer un espace memoire pour une nouvelle cellule */

	struct Cell* p_new = (struct Cell*)malloc(sizeof(*p_new));

	/* Verifier si la call malloc a fonctionné */

	if (p_new != NULL) {

		/* Initialiser les données membres de nouvelle cellule avec le client donnée en parametre */

		p_new->client = p_client;
		p_new->p_next = NULL;
		p_new->p_prev = NULL;

	}

	return p_new;

}

void cell_pointing_each_other(struct Cell* p_head, struct Cell* p_tail) {

	p_head->p_next = p_tail;
	p_tail->p_prev = p_head;

}

struct Cell* cell_return_next(struct Cell* p_cell) {

	return p_cell->p_next;

}

struct Cell* cell_return_prev(struct Cell* p_cell) {

	return p_cell->p_prev;

}

void cell_chaining_update_after_insertion(struct Cell* p_current, struct Cell* p_new) {

	p_new->p_next = p_current;
	p_new->p_prev = p_current->p_prev;
	p_current->p_prev->p_next = p_new;
	p_current->p_prev = p_new;

}

void cell_chaining_update_before_deletion(struct Cell* p_cell) {

	/* Mettre à jour les chainages "comme si la cellule à supprimer n'existait plus"
					   1- La cellule qui suit la cellule courante (temp) doit pointer vers cell qui precede temp
					   2- La cellule qui precede temp doit pointer vers celle qui suit temp
	*/

	p_cell->p_next->p_prev = p_cell->p_prev;
	p_cell->p_prev->p_next = p_cell->p_next;

}

struct Client* cell_get_client(struct Cell* p_cell) {

	return p_cell->client;

}

void cell_display(struct Cell* p_cell) {

	client_display(p_cell->client);

}

struct Cell* cell_del(struct Cell* p_cell) {

	if (p_cell != NULL) {

		client_del(p_cell->client);

		free(p_cell);
		p_cell = NULL;

	}

	return p_cell;

}