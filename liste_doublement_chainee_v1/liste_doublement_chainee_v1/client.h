#pragma once

#define MAX_LENGTH_NOM 40
#define MAX_LENGTH_PRENOM 30


struct Client* client_new(const char* nom, const char* prenom, int num_client);
int* client_get_id(struct Client* p_client);
char* client_get_firstname(struct Client* p_client);
char* client_get_lastname(struct Client* p_client);
/* p_client1 < p_client2 -> -1
   p_client1 = p_client2 -> 0
   p_client1 > p_client2 -> 1
*/
int client_compare(struct Client* p_client1, struct Client* p_client2);
void client_display(struct Client* p_client);
struct Client* client_del(struct Client* p_client);

struct Client {

	int num_client;
	char nom[MAX_LENGTH_NOM];
	char prenom[MAX_LENGTH_PRENOM];

};