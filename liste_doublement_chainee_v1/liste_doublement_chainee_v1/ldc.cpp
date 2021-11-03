#include <iostream>
#include <stdlib.h>

#include "ldc.h"
#include "cell.h"
#include "client.h"


struct Ldc* ldc_new() {

	struct Ldc* p_new = (struct Ldc*)malloc(sizeof(*p_new));

	if (p_new != NULL) {

		p_new->p_head = NULL;
		p_new->p_tail = NULL;
		p_new->length = 0;

	}

	p_new->p_head = cell_new_empty_cells();
	p_new->p_tail = cell_new_empty_cells();

	if (p_new->p_head != NULL && p_new->p_tail != NULL) {

		p_new->p_head->p_prev = NULL;
		p_new->p_head->p_next = p_new->p_tail;

		p_new->length++;

		p_new->p_tail->p_next = NULL;
		p_new->p_tail->p_prev = p_new->p_head;

		p_new->length++;

	}

	return p_new;

}

struct Ldc* ldc_insert_client(struct Ldc* p_list, struct Client* p_client, int key) {

	if (p_list != NULL) {

		struct Cell* p_temp = p_list->p_head->p_next; // -1 200 300 400 500 -1

		while (p_temp->p_next != NULL && p_temp->key <= key) { 
			
			p_temp = p_temp->p_next;

		}

		struct Cell* p_new = cell_new(p_client, key);

		if (p_new != NULL) {

			p_new->p_next = p_temp;
			p_new->p_prev = p_temp->p_prev;
			p_temp->p_prev->p_next = p_new;
			p_temp->p_prev = p_new;

			p_list->length++;

		}

	}

	return p_list;

}

struct Ldc* ldc_remove_client(struct Ldc* p_list, struct Client* p_client) {

	if (p_list != NULL) {

		struct Cell* p_temp = p_list->p_head->p_next;
		int found = 0;

		while (p_temp != NULL && found == 0) {

			if (p_temp->client->num_client == p_client->num_client) { // -1 10 20 30 -1

				p_temp->p_next->p_prev = p_temp->p_prev;
				p_temp->p_prev->p_next = p_temp->p_next;

				client_del(p_temp->client);

				cell_del(p_temp);
				p_list->length--;
				found = 1;

			}
			else {

				p_temp = p_temp->p_next;

			}

		}

	}

	return p_list;

}

void ldc_display_asc(struct Ldc* p_list) {

	if (p_list != NULL && p_list->length > 2) {

		struct Cell* p_temp = p_list->p_head->p_next;

		printf("\n**********AFFICHAGE ORDRE CROISSANT**********\n");

		for (int i = 0; i < p_list->length - 2; i++) {

			printf("\nNom: %s\n", p_temp->client->nom);
			printf("Prenom: %s\n", p_temp->client->prenom);
			printf("Numero_client: %d\n", p_temp->client->num_client);

			printf("Cell_Key: %d\n", p_temp->key);
			p_temp = p_temp->p_next;

		}

	}
	else {

		printf("La liste est vide.\n");

	}

}

void ldc_display_desc(struct Ldc* p_list) {

	if (p_list != NULL && p_list->length > 2) {

		struct Cell* p_temp = p_list->p_tail->p_prev;

		printf("\n**********AFFICHAGE ORDRE DECROISSANT**********\n");

		for (int i = 0; i < p_list->length - 2; i++) {

			printf("\nNom: %s\n", p_temp->client->nom);
			printf("Prenom: %s\n", p_temp->client->prenom);
			printf("Numero_client: %d\n", p_temp->client->num_client);

			printf("Cell_Key: %d\n", p_temp->key);
			p_temp = p_temp->p_prev;

		}

	}
	else {

		printf("La liste est vide.\n");

	}

}

struct Ldc* ldc_del(struct Ldc* p_list) {

	if (p_list != NULL) {

		struct Cell* p_temp = p_list->p_head->p_next;

		for (int i = 0; i < p_list->length - 2; i++) { // -1 100 200 250 300 -1

			struct Cell* p_del = p_temp;

			p_temp = p_temp->p_next;

			client_del(p_del->client);
			cell_del(p_del);

		}

		cell_del(p_list->p_head);
		cell_del(p_list->p_tail);

		free(p_list);
		p_list = NULL;

	}

	return p_list;

}