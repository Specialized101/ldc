#pragma once

#include "cell.h"
#include "client.h"

struct Ldc* ldc_new(void);
struct Ldc* ldc_insert_client(struct Ldc* p_list, struct Client* p_client);
struct Ldc* ldc_remove_client(struct Ldc* p_list,struct Client* p_client);
void ldc_display_asc(struct Ldc* p_list);
void ldc_display_desc(struct Ldc* p_list);
struct Ldc* ldc_del(struct Ldc* p_list);

struct Ldc {

	struct Cell* p_head;	// pointe vers la premiere cellule de la liste (cell fictive dont cell_prev est NULL)
	struct Cell* p_tail;  // pointe vers la derniere cellule de la liste (cell fictive dont cell_next est NULL)
	int length;			// indique le nombre de cellule dans la liste (y compris les 2 cellules fictives vides)

};