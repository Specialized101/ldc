#pragma once

#define MAX_LENGTH_NOM 40
#define MAX_LENGTH_PRENOM 30


struct Client* client_new(const char* nom, const char* prenom, int num_client);
struct Client* client_del(struct Client* p_client);

struct Client {

	int num_client;
	char nom[MAX_LENGTH_NOM];
	char prenom[MAX_LENGTH_PRENOM];

};