#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define Create_String_Item(str) string_item_new(str)
#define Append_Node(linked_List, New_String) Double_Append((struct list_node **)&linked_List, &(Create_String_Item(New_String))->node);

struct list_node
{
    struct list_node *prev;
    struct list_node *next;
};

struct list_node *list_get_tail(struct list_node **head)
{
    struct list_node *curr_node = *head;
    struct list_node *last_node = NULL;
    while (curr_node)
    {
        last_node = curr_node;
        curr_node = curr_node->next;
    }
    return last_node;
}
struct list_node *Double_Append(struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}

struct String_Item
{
    struct list_node node;
    const char *string;
};
struct String_Item *string_item_new(const char *string)
{
    struct String_Item *item = malloc(sizeof(struct String_Item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}
struct list_node *remove_node(struct list_node **head, struct list_node *item_to_replace)
{

    struct list_node *curr_node = *head;
    struct list_node *next_node = curr_node->next;
    while (curr_node->next)
    {

        if (next_node == item_to_replace)
        {
            struct list_node *node_after = next_node->next;
            next_node->next = NULL;
            curr_node->next = node_after;
            return curr_node;
        }
        curr_node = next_node;
        next_node = curr_node->next;
    }
    return curr_node;
}

void Insert_After_An_Item(struct list_node **head, struct list_node* item,struct list_node* after_node)
{
    struct list_node* curr_node = *head; 
    while (curr_node)
    {
        if(curr_node == after_node)
        {
            struct list_node* curr_next_node;
            curr_next_node = curr_node->next;
            curr_node->next = item;
            item->prev = curr_node;
            item->next = curr_next_node;
            if(curr_next_node)
            {
                curr_next_node->prev = item;
            }
            return;
        }
       
        curr_node = curr_node->next;
    }
    
}
void Insert_Before_An_Item(struct list_node **head, struct list_node * item,struct list_node* before_node)
{
    struct list_node* curr_node = *head; 
    while (curr_node)
    {
        if(curr_node == before_node)
        {
            struct list_node* curr_prev_node;
            curr_prev_node = curr_node->prev;
            curr_node->prev = item;
            item->next = curr_node;
            item->prev = curr_prev_node;
            if(curr_prev_node)
            {
                curr_prev_node->next = item;
            }
            return;
        }
       
        curr_node = curr_node->next;
    }
    
}


int main(int argc, char **args)
{
    struct String_Item *Double_ll = NULL;

    Append_Node(Double_ll, "Hello World");
    
    struct list_node* to_Remove = Append_Node(Double_ll, "Ciao Mondo");

    Append_Node(Double_ll, "Addio Mondo\n");

    struct String_Item *newString = string_item_new("Saro' Franco");
    Double_Append((struct list_node **)&Double_ll, &newString->node);


    printf("\ntarget BEFORE: %p \n\n",&newString->node);
    struct String_Item* add_after_node = string_item_new("Saro' Franco AFTER");
    Insert_After_An_Item((struct list_node**) &Double_ll, &add_after_node->node, &newString->node);


    struct String_Item* add_before_node = string_item_new("Saro' Franco BEFORE");
    Insert_Before_An_Item((struct list_node**) &Double_ll, &add_before_node->node, &newString->node);

    struct String_Item *string_item = Double_ll;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct String_Item *)string_item->node.next;
    }

    printf("\nDELETE Ciao Mondo\n");
    struct String_Item *string_item2 = Double_ll;
    remove_node((struct list_node **)&Double_ll, to_Remove);
    while (string_item2)
    {
        printf("%s\n", string_item2->string);
        string_item2 = (struct String_Item *)string_item2->node.next;
    }
    return 0;
}
