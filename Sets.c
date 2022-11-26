#include "SetsHeader.h"

int main (int argc,char** args)
{
    struct set_table* new_set = set_table_new(100);
    
    char* key_to_insert = "Hello Word"; 
    set_insert(new_set,key_to_insert,strlen(key_to_insert));
    int IntToString = 17;
    char buffer[20];
    NumberToString(IntToString,buffer);
    set_insert(new_set,&IntToString,strlen(buffer));
    key_to_insert = "Ciao Mondo"; 
    set_insert(new_set,key_to_insert,strlen(key_to_insert));
    
    Display_Keys(new_set);
    printf("\n");
    
    char* key_to_search = "Ciao Mondo"; 
    struct set_node* search = key_find(new_set,key_to_search);
    printf("Key found : %s \n",(char*)search->key);
    printf("\n");
    
    Key_delete(new_set,"Hello Word");
    printf("\n");

    printf("INSERTING DUPLICATE KEY");
    char* key_duplicate = "Ciao Mondo"; 
    struct set_node* check_if_null = set_insert(new_set,key_duplicate,strlen(key_duplicate));

    if(!check_if_null)
    {
        printf("DUPLICATE KEY NOT INSERTED\n\n");
    }
    Display_Keys(new_set);
}