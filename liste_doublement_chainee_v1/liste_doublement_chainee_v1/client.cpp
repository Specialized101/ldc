
#include <stdlib.h> 
#include <iostream>

#include "client.h"

struct Client* client_new(const char* nom, const char* prenom, int num_client) {

	struct Client* p_new = (struct Client*)malloc(sizeof(*p_new));

	if (p_new != NULL) {

		strcpy(p_new->nom, nom);
		strcpy(p_new->prenom, prenom);
		p_new->num_client = num_client;

	}

	return p_new;

}

struct Client* client_del(struct Client* p_client) {

	if (p_client != NULL) {

		free(p_client);
		p_client = NULL;

	}

	return p_client;

}