#pragma once

#define MAX_LADDER_ENTRY 10
#define LADDER_ENTRY_SLOTS	 4

struct ladder_entry {
	unsigned char characters[4];
};

void clean_ladder();

bool is_in_my_ladder(int characterSlot, int id);

int get_ladder_addr(int slot);
int get_ladder_amount(int slot);

void generate_random_ladder(int slot);
void make_custom_tower();

int get_current_ladder_pos();