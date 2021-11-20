#pragma once

#include "client.h"

struct Cell* cell_new_empty_cells();
struct Cell* cell_new(struct Client* p_client);
void cell_pointing_each_other(struct Cell* p_head, struct Cell* p_tail);
struct Cell* cell_return_next(struct Cell* p_cell);
struct Cell* cell_del(struct Cell* p_cell);

struct Cell {

	struct Cell* p_prev;	// pointe vers la cellule qui la précède
	struct Cell* p_next;	// pointe vers la cellule qui la succède
	struct Client* client;	// pointe vers le client contenue dans la cellule

};