#include "pch.h"
#include "ladder.h"
#include "characters.h"
#include "misc.h"
#include <iostream>

ladder_entry my_ladder[MAX_LADDER_ENTRY] = {};

short sub_bosses[] = {
	GORO
};

short characters[] = {
	SCORPION,
	RAIDEN,
	SONYA,
	LIU_KANG,
	SUBZERO,
	FUJIN,
	REIKO,
	QUANCHI,
	TANYA,
	REPTILE,
	KAI,
	JAREK,
	JAX,
	CAGE
};



void clean_ladder()
{
	for (int i = 0; i < MAX_LADDER_ENTRY; i++)
		my_ladder[i] = { 0xFF,0xFF,0xFF,0xFF };
}

bool is_in_my_ladder(int characterSlot, int id)
{
	for (int i = 0; i < MAX_LADDER_ENTRY; i++)
	{
		if (my_ladder[i].characters[characterSlot] == id)
			return true;
	}

	return false;
}

int get_ladder_addr(int slot)
{
	switch (slot)
	{
	case 0:
		return 0x4E55C8;
	case 1:
		return 0x4E55E8;
	case 2:
		return 0x4E5610;
	case 3:
		return 0x4E5638;
	case 4:
		return 0x4E5660;
	default:
		break;
	}
	return 0x4E55C8;
}

int get_ladder_amount(int slot)
{
	switch (slot)
	{
	case 0:
		return 7;
	case 1:
		return 8;
	case 2:
		return 9;
	case 3:
		return 9;
	case 4:
		return 9;
	default:
		break;
	}
	return 7;
}

void generate_random_ladder(int slot)
{
	int ladder_max = get_ladder_amount(slot);
	for (int i = 0; i < ladder_max; i++)
	{
		for (int a = 0; a < LADDER_ENTRY_SLOTS; a++)
		{
			int fighter_id = -1;
			int table_size = 0;
			// boss
			if (i == ladder_max - 1)
			{
				fighter_id = SHINNOK;
			}
			else if (i == ladder_max - 2) // sub boss
			{
				table_size = sizeof(sub_bosses) / sizeof(sub_bosses[0]);
				fighter_id = sub_bosses[randu(table_size)];
			}
			else
			{
				table_size = sizeof(characters) / sizeof(characters[0]);
				fighter_id = characters[randu(table_size)];

				while (is_in_my_ladder(a, fighter_id))
					fighter_id = characters[randu(table_size)];
			}

			my_ladder[i].characters[a] = fighter_id;
		}
	}
	my_ladder[ladder_max] = {0,0,0,0};

	ladder_entry* ladder = (ladder_entry*)get_ladder_addr(slot);

	for (int i = 0; i < ladder_max; i++)
		ladder[i] = my_ladder[i];

}

void make_custom_tower()
{
	for (int i = 0; i < 5; i++)
	{
		clean_ladder();
		generate_random_ladder(i);
	}
}

int get_current_ladder_pos()
{
	return *(int*)0x534780;
}
