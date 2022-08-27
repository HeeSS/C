#include "header.h"

int Table_Init(Table *table) {
	table->howmany = 0;
	table->size = 10;
	table->list = (State_A **)calloc(table->size, sizeof(State_A *));
	return TRUE;
}
int Table_Add(Table *table, State_A *admin) {
	State_A **list;
	int i;

	if (table->size - table->howmany <= 5) {
		table->size += 5;
		list = (State_A **)calloc(table->size, sizeof(State_A *));
		memcpy(list, table->list, sizeof(State_A)*(table->size - 5));
		free(table->list);
		table->list = list;
	}

	for (i = 0; i < table->howmany; i++) {
		if (table->list[i]->Socket == admin->Socket) {
			return TRUE;
		}
	}

	table->list[table->howmany++] = admin;
	return TRUE;
	      
}
int Table_Delete(Table *table, State_A *admin) {
	int i,j=0;
	if (table->howmany <= 0) {
		return FALSE;
	}

	for (i = 0; i < table->howmany; i++) {
		if (table->list[i]->Socket == admin->Socket) {
			table->list[i] = NULL;
			//memcpy(table->list[i], table->list[i + 1], 4*(table->howmany-i));
			j = i;
			while (TRUE) {
				if (table->list[j+1] == NULL) {
					break;
				}
				else {
					table->list[j] = table->list[j + 1];
					j++;
				}
			}
			table->howmany--;
			return TRUE;
		}
	}
	return FALSE;
}