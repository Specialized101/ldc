#include <iostream>
#include <stdlib.h>

#include "ldc.h"
#include "cell.h"
#include "client.h"


struct Ldc* ldc_new() {

	/* Allouer un espace memoire d'un pointeur d'objet de type Ldc */

	struct Ldc* p_new = (struct Ldc*)malloc(sizeof(*p_new));

	/* Verifier si la call à la fonction malloc a renvoyé une adresse */

	if (p_new != NULL) {

		/* Initialiser les données membres de la nouvelle liste */

		p_new->p_head = NULL;
		p_new->p_tail = NULL;
		p_new->length = 0;

	}

	/* Creer les cellules fictives de debut et fin de liste
	   Et recupérer les adresses retrournées dans les données membres correspondantes de la nouvelle liste */

	p_new->p_head = cell_new(NULL);
	p_new->p_tail = cell_new(NULL);

	if (p_new->p_head != NULL && p_new->p_tail != NULL) {

		/* Initialiser les données membres des 2 cellules fictives:
			      NULL <-- head <--> tail --> NULL 
		   Incrementer la longueur de la liste apres chaque ajout de cellule */

		cell_pointing_each_other(p_new->p_head, p_new->p_tail);
		p_new->length = 2;

	}

	return p_new;

}

struct Ldc* ldc_insert_client(struct Ldc* p_list, struct Client* p_client) {

	/* FONCTION d'INSERTION D'UN CLIENT DANS UNE LISTE EN FONCTION D'UNE CLE */

	if (p_list != NULL) {

		/* Verifier si le client que l'on souhaite inserer n'est pas deja present dans la liste */

		if (ldc_is_client_in_list(p_list, p_client) == 0) {

			/* Rechercher la cellule courante = dont la clé est strictement supérieur à celle donnée en parametre
		   Debuter la recherche à la cellule qui suit celle de tete de liste (head) */

			struct Cell* p_temp = cell_return_next(p_list->p_head);

			/* Si le pointeur droit de la cellule en cours (temp) est NULL -> temp = tail, fin de boucle
			OU
			   Si le num_client dans la cellule courante est strictement superieur au num_client à inserer, fin de boucle */

			int found = 0;

			for (int i = 0; i < p_list->length - 2 || found == 1; i++) {

				if (client_compare(cell_get_client(p_temp), p_client) == 1) { 

					found = 1;

				}

				/* Passer à la cellule suivante */

				p_temp = cell_return_next(p_temp);

			}

			/* Creer une nouvelle cellule qui va contenir la client à inserer */

			struct Cell* p_new = cell_new(p_client);

			if (p_new != NULL) {

				/* Mettre à jour les chainages */

				cell_chaining_update_after_insertion(p_temp, p_new);

				/* Incrementer la longueur de la liste */

				p_list->length++;

			}

		}
		else {

			printf("\nLe client n'a pas pu etre ajoute, il est deja dans la liste.\n");

		}

	}

	return p_list;

}

struct Ldc* ldc_remove_client(struct Ldc* p_list, struct Client* p_client) {

	/* FONCTION DE SUPPRESSION D'UN CLIENT ET DE LA CELLULE QUI LE CONTIENT */

	if (p_list != NULL) {

		/* Verifier si le client à supprimer est bien present dans la liste */

		if (ldc_is_client_in_list(p_list, p_client) == 1) {

			/* Rechercher la cellule contenant le client à supprimer:
		   Debuter la recherche à la cellule suivant la tete de liste */

			struct Cell* p_temp = cell_return_next(p_list->p_head);
			int found = 0;

			/* Fin de boucle quand la cellule recherchée est trouvée ou que la cellule est cours n'existe pas */

			while (p_temp != NULL && found == 0) {

				/* Verifier si le numero client du client donnée en parametre correspond à celui de la
				   cellule en cours */

				if (client_compare(p_client, cell_get_client(p_temp)) == 0) {

					/* Mettre à jour les chainages */

					cell_chaining_update_before_deletion(p_temp);

					/* Supprimer la cellule courante */

					cell_del(p_temp);

					/* Decrementer la longueur de la liste */

					p_list->length--;

					/* Sortir de la boucle */

					found = 1;

				}
				else {

					/* Si les numeros client ne correspondent pas, passer à la cellule suivante */

					p_temp = cell_return_next(p_temp);

				}

			}

		}
		else {

			printf("\nLe client n'a pas pu etre supprime, il n'est pas dans la liste.\n");

		}

	}

	return p_list;

}

int ldc_is_client_in_list(struct Ldc* p_list, struct Client* p_client) {

	/* Demarrer la recherche de correspondance à la cellule suivante la cellule vide de tete de liste */

	struct Cell* p_temp = cell_return_next(p_list->p_head);

	int found = 0;

	/* Boucler autant de fois qu'il y a de clients de la liste (-2 cellules vides) */

	for (int i = 0; i < p_list->length - 2; i++) {

		if (client_compare(p_client, cell_get_client(p_temp)) == 0) {
			
			/* Si les numeros clients correspondent, le client est present dans la liste, sortie de boucle */

			found = 1;

		}

		/* Passer à la cellule suivante */

		p_temp = cell_return_next(p_temp);

	}

	/* return 0: Le client n'est pas present dans la liste
	   return 1: le client est present dans la liste
	*/

	return found;

}

void ldc_display_asc(struct Ldc* p_list) {

	/* Verifier si la liste existe et qu'elle contient au moins 1 client */

	if (p_list != NULL && p_list->length > 2) {

		/* Debuter l'affichage à la cellule suivant la tete de liste: la cellule contenant le premier client */

		struct Cell* p_temp = cell_return_next(p_list->p_head);

		printf("\n**********AFFICHAGE ORDRE CROISSANT**********\n");

		/* Boucler autant de fois qu'il y a de client: longueur de liste moins 2 cellules fictives vides */

		for (int i = 0; i < p_list->length - 2; i++) {

			cell_display(p_temp);

			p_temp = cell_return_next(p_temp);

		}

	}
	else {

		printf("\nLa liste est vide.\n");

	}

}

void ldc_display_desc(struct Ldc* p_list) {

	if (p_list != NULL && p_list->length > 2) {

		/* Debuter l'affichage à la cellule precendant la fin de liste: la cellule contenant le dernier client */

		struct Cell* p_temp = cell_return_prev(p_list->p_tail);

		printf("\n**********AFFICHAGE ORDRE DECROISSANT**********\n");

		for (int i = 0; i < p_list->length - 2; i++) {

			cell_display(p_temp);

			p_temp = cell_return_prev(p_temp);

		}

	}
	else {

		printf("\nLa liste est vide.\n");

	}

}

struct Ldc* ldc_del(struct Ldc* p_list) {

	if (p_list != NULL) {

		/* Debuter la suppression à la cellule suivant la tete de liste (premier client) */

		struct Cell* p_temp = cell_return_next(p_list->p_head);

		/* Boucler autant de fois qu'il y a de clients, 0 si la liste est vide */

		for (int i = 0; i < p_list->length - 2; i++) { 

			/* L'ordre des 3 operations suivantes est important: 
			   Si on commencait par l'operation 3, lors de l'operation 2, le pointeur p_temp pointerait 
			   vers une cellule ayant été supprimée (via cell_del(p_del))

			   1- Stocker le pointeur de la cellule en cours dans une variable intermediaire (del) */

			struct Cell* p_del = p_temp;

			/* 2- Passer à la cellule suivante */

			p_temp = cell_return_next(p_temp);

			/* 3- Supprimer le client puis la cellule courante */

			cell_del(p_del);

		}

		/* Supprimer les cellules fictives de tete et de fin de liste */

		cell_del(p_list->p_head);
		cell_del(p_list->p_tail);

		/* Liberer l'espace memoire de la liste */

		free(p_list);
		p_list = NULL;

	}

	return p_list;

}