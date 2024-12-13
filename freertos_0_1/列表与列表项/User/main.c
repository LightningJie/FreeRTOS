#include "list.h"

List_t List_Test;
ListItem_t List_Item1;
ListItem_t List_Item2;
ListItem_t List_Item3;

int main(void)
{
	vListInitialise(&List_Test);
	vListInitialiseItem(&List_Item1);
	vListInitialiseItem(&List_Item2);
	vListInitialiseItem(&List_Item3);
	
	vListInsert(&List_Test,&List_Item1);
	vListInsert(&List_Test,&List_Item2);
	vListInsert(&List_Test,&List_Item3);
	
	
	for(;;)
	{
	
	}

}
