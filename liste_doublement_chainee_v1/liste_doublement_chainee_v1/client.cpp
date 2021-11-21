
#include <stdlib.h> 
#include <iostream>

#include "client.h"

struct Client* client_new(const char* nom, const char* prenom, int num_client) {

	/* Allouer un espace memoire pour un nouveau client */

	struct Client* p_new = (struct Client*)malloc(sizeof(*p_new));

	/* Verifier si la call malloc a fonctionné */

	if (p_new != NULL) {

		/* Initialiser les données membres du nouveau client avec les parametres */

		strcpy(p_new->nom, nom);
		strcpy(p_new->prenom, prenom);
		p_new->num_client = num_client;

	}

	/* Retourner l'adresse du nouveau client */

	return p_new;

}

int* client_get_id(struct Client* p_client) {

	return &p_client->num_client;

}

char* client_get_firstname(struct Client* p_client) {

	return p_client->prenom;

}
char* client_get_lastname(struct Client* p_client) {

	return p_client->nom;

}

struct Client* client_del(struct Client* p_client) {

	if (p_client != NULL) {

		free(p_client);
		p_client = NULL;

	}

	return p_client;

}