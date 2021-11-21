#pragma once

#define MAX_LENGTH_NOM 40
#define MAX_LENGTH_PRENOM 30


struct Client* client_new(const char* nom, const char* prenom, int num_client);
int* client_get_id(struct Client* p_client);
char* client_get_firstname(struct Client* p_client);
char* client_get_lastname(struct Client* p_client);
struct Client* client_del(struct Client* p_client);

struct Client {

	int num_client;
	char nom[MAX_LENGTH_NOM];
	char prenom[MAX_LENGTH_PRENOM];

};