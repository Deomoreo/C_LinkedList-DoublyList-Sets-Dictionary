#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct set_node
{
    const void* key;        
    size_t key_len;         
    struct set_node* next;  
    char valueType; 
    void* value;  
}set_node;

typedef struct set_table
{
    struct set_node** nodes;
    size_t hashmap_size;
    
} set_table;

void NumberToString(int number,char* buffer)
{
    sprintf(buffer, "%i", number);
}
size_t djb33x_hash( void *key)
{
    size_t hash = 5381;
    char* key_as_string = (char* )key;
    int length = strlen(key_as_string);
    for (size_t i = 0; i < length; i++)
    {
        hash = ((hash << 5) + hash) ^ key_as_string[i];
    }
    return hash;
}
size_t calculate_index_hash(set_table* table, void* key)
{
    size_t hash = djb33x_hash(key);
    size_t index = hash % table->hashmap_size;
    return index;
}
int duplicate_search(set_table* table, void* key)
{
    size_t index = calculate_index_hash(table,key);
    if(!strcmp(table->nodes[index]->key,key))
    {
         return !0;
    } 
    return 0;
}

set_table *set_table_new(const size_t hashmap_size)
{
    set_table *table = malloc(sizeof(set_table)); 
    if (!table)
    {
        return NULL; 
    }

    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(set_node *));

    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

set_node *set_insert(set_table *table,  void *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key);
    size_t index = hash % table->hashmap_size;
   
    set_node *head = table->nodes[index];
    if (!head)
    {
        table->nodes[index] = malloc(sizeof(set_node));
        if (!table->nodes[index])
        {
            return NULL;
        }
        table->nodes[index]->key = key;
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->next = NULL;
        return table->nodes[index];
    }

    if(duplicate_search(table,key)>0)
    {
        printf("\nDuplicate key detected! = %s \n" , (char*)key);
        return NULL;
    }
    set_node *new_item = malloc(sizeof(set_node));
    if (!new_item)
    {
        return NULL;
    }
    new_item->key = key;
    new_item->key_len = key_len;
    new_item->next = NULL;
    set_node *tail = head;
    while (head)
    {
        tail = head;
        head = head->next;
    }
    tail->next = new_item;
       
    return tail;
}

void Display_Keys(set_table* to_print)
{
    for (int i=0;i<(int)to_print->hashmap_size;i++)
    {
        set_node* current_set_node = to_print->nodes[i];
        if(current_set_node)
        {
            printf("Key at Index %i : %s \n",i,(char*)current_set_node->key); 
            if(current_set_node->next)
            {
                printf(" Next node : %p  \n",(char*)current_set_node->next); 
            }
            else
            {
                 printf(" Next node is NULL \n"); 
            }
        }
    }
}

set_node* key_find(set_table* to_examine,char* key_to_find)
{
    size_t index = calculate_index_hash(to_examine,key_to_find);
    if(to_examine->nodes[index])
    {
        return to_examine->nodes[index] ;
    }
    return NULL;
}

void Key_delete(set_table* table,void* key_del)
{
    size_t index = calculate_index_hash(table,key_del);
    if(table->nodes[index])
    {
        free(table->nodes[index]);
        table->nodes[index] = NULL;
        printf("\nRemove the node with key: %s\n\n",(char*)key_del);
    }
}

