#include <iostream>
#include <stdlib.h>

#include "ldc.h"
#include "cell.h"
#include "client.h"


struct Ldc* ldc_new() {

	/* Allouer un espace memoire d'un pointeur d'objet de type Ldc */

	struct Ldc* p_new = (struct Ldc*)malloc(sizeof(*p_new));

	/* Verifier si la call � la fonction malloc a renvoy� une adresse */

	if (p_new != NULL) {

		/* Initialiser les donn�es membres de la nouvelle liste */

		p_new->p_head = NULL;
		p_new->p_tail = NULL;
		p_new->length = 0;

	}

	/* Creer les cellules fictives de debut et fin de liste
	   Et recup�rer les adresses retrourn�es dans les donn�es membres correspondantes de la nouvelle liste */

	p_new->p_head = cell_new_empty_cells();
	p_new->p_tail = cell_new_empty_cells();

	if (p_new->p_head != NULL && p_new->p_tail != NULL) {

		/* Initialiser les donn�es membres des 2 cellules fictives:
			      NULL <-- head <--> tail --> NULL 
		   Incrementer la longueur de la liste apres chaque ajout de cellule */

		p_new->p_head->p_prev = NULL;
		p_new->p_head->p_next = p_new->p_tail;
		p_new->length++;

		p_new->p_tail->p_next = NULL;
		p_new->p_tail->p_prev = p_new->p_head;
		p_new->length++;

	}

	return p_new;

}

struct Ldc* ldc_insert_client(struct Ldc* p_list, struct Client* p_client) {

	/* FONCTION d'INSERTION D'UN CLIENT DANS UNE LISTE EN FONCTION D'UNE CLE */

	if (p_list != NULL) {

		/* Rechercher la cellule courante = dont la cl� est strictement sup�rieur � celle donn�e en parametre
		   Debuter la recherche � la cellule qui suit la cellule de tete de liste (head) */

		struct Cell* p_temp = p_list->p_head->p_next; 

		/* Si le pointeur droit de la cellule en cours (temp) est NULL -> temp = tail, fin de boucle 
		OU
		   Si la cl� de temp est strictement superieur � la cl� donn�e en parametre, fin de boucle */

		while (p_temp->p_next != NULL && p_temp->client->num_client <= p_client->num_client) { 
			
			/* Passer de cellule en cellule */

			p_temp = p_temp->p_next;

		}

		/* Creer une nouvelle cellule qui va contenir la client � inserer */

		struct Cell* p_new = cell_new(p_client);

		if (p_new != NULL) {

			/* Mettre � jour les chainages */

			p_new->p_next = p_temp; 
			p_new->p_prev = p_temp->p_prev;
			p_temp->p_prev->p_next = p_new;
			p_temp->p_prev = p_new;

			/* Incrementer la longueur de la liste */

			p_list->length++;

		}

	}

	return p_list;

}

struct Ldc* ldc_remove_client(struct Ldc* p_list, struct Client* p_client) {

	/* FONCTION DE SUPPRESSION D'UN CLIENT ET DE LA CELLULE QUI LE CONTIENT */

	if (p_list != NULL) {

		/* Rechercher la cellule contenant le client � supprimer:
		   Debuter la recherche � la cellule suivant la tete de liste */

		struct Cell* p_temp = p_list->p_head->p_next;
		int found = 0;

		/* Fin de boucle quand la cellule recherch�e est trouv�e ou que la cellule est cours n'existe pas */

		while (p_temp != NULL && found == 0) {

			/* Verifier si le numero client du client donn�e en parametre correspond � celui de la
			   cellule en cours */

			if (p_temp->client->num_client == p_client->num_client) { 

				/* Mettre � jour les chainages "comme si la cellule � supprimer n'existait plus" 
				   1- La cellule qui suit la cellule courante (temp) doit pointer vers cell qui precede temp
				   2- La cellule qui precede temp doit pointer vers celle qui suit temp 
				*/

				p_temp->p_next->p_prev = p_temp->p_prev;
				p_temp->p_prev->p_next = p_temp->p_next;

				/* Supprimer le client contenu dans la cellule courante */

				client_del(p_temp->client);

				/* Supprimer la cellule courante, qui contenait le client */

				cell_del(p_temp);

				/* Decrementer la longueur de la liste */

				p_list->length--;

				/* Sortir de la boucle */

				found = 1;

			}
			else {

				/* Si les numeros client ne correspondent pas, passer � la cellule suivante */

				p_temp = p_temp->p_next;

			}

		}

	}

	return p_list;

}

void ldc_display_asc(struct Ldc* p_list) {

	/* Verifier si la liste existe et qu'elle contient au moins 1 client */

	if (p_list != NULL && p_list->length > 2) {

		/* Debuter l'affichage � la cellule suivant la tete de liste: la cellule contenant le premier client */

		struct Cell* p_temp = p_list->p_head->p_next;

		printf("\n**********AFFICHAGE ORDRE CROISSANT**********\n");

		/* Boucler autant de fois qu'il y a de client: longueur de liste moins 2 cellules fictives vides */

		for (int i = 0; i < p_list->length - 2; i++) {

			printf("\nNom: %s\n", p_temp->client->nom);
			printf("Prenom: %s\n", p_temp->client->prenom);
			printf("Numero_client: %d\n", p_temp->client->num_client);

			p_temp = p_temp->p_next;

		}

	}
	else {

		printf("La liste est vide.\n");

	}

}

void ldc_display_desc(struct Ldc* p_list) {

	if (p_list != NULL && p_list->length > 2) {

		/* Debuter l'affichage � la cellule precendant la fin de liste: la cellule contenant le dernier client */

		struct Cell* p_temp = p_list->p_tail->p_prev;

		printf("\n**********AFFICHAGE ORDRE DECROISSANT**********\n");

		for (int i = 0; i < p_list->length - 2; i++) {

			printf("\nNom: %s\n", p_temp->client->nom);
			printf("Prenom: %s\n", p_temp->client->prenom);
			printf("Numero_client: %d\n", p_temp->client->num_client);

			p_temp = p_temp->p_prev;

		}

	}
	else {

		printf("La liste est vide.\n");

	}

}

struct Ldc* ldc_del(struct Ldc* p_list) {

	if (p_list != NULL) {

		/* Debuter la suppression � la cellule suivant la tete de liste (premier client) */

		struct Cell* p_temp = p_list->p_head->p_next;

		/* Boucler autant de fois qu'il y a de clients, 0 si la liste est vide */

		for (int i = 0; i < p_list->length - 2; i++) { 

			/* L'ordre des 3 operations suivantes est important: 
			   Si on commencait par l'operation 3, lors de l'operation 2, le pointeur p_temp pointerait 
			   vers une cellule ayant �t� supprim�e (via cell_del(p_del))

			   1- Stocker le pointeur de la cellule en cours dans une variable intermediaire (del) */

			struct Cell* p_del = p_temp;

			/* 2- Passer � la cellule suivante */

			p_temp = p_temp->p_next;

			/* 3- Supprimer le client et la cellule courante */

			client_del(p_del->client);
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