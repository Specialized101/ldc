#pragma once

#include "client.h"

struct Cell* cell_new(struct Client* p_client);
void cell_pointing_each_other(struct Cell* p_head, struct Cell* p_tail);
void cell_chaining_update_after_insertion(struct Cell* p_current, struct Cell* p_new);
void cell_chaining_update_before_deletion(struct Cell* p_cell);
struct Client* cell_get_client(struct Cell* p_cell);
struct Cell* cell_return_next(struct Cell* p_cell);
struct Cell* cell_return_prev(struct Cell* p_cell);
void cell_display(struct Cell* p_cell);
struct Cell* cell_del(struct Cell* p_cell);

struct Cell {

	struct Cell* p_prev;	// pointe vers la cellule qui la précède
	struct Cell* p_next;	// pointe vers la cellule qui la succède
	struct Client* client;	// pointe vers le client contenue dans la cellule

};