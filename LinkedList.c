#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define Create_String_Item(str) string_item_new(str)
#define Append_Node(linked_List, New_String) list_append((struct list_node **)&linked_List, &(Create_String_Item(New_String))->node);

struct list_node
{
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
struct list_node *list_append(struct list_node **head, struct list_node *item)
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
    item->next = NULL;
    return item;
}

struct list_node *list_pop(struct list_node **head)
{
    struct list_node *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}
struct string_item
{
    struct list_node node;
    const char *string;
};
struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}

struct list_node *reverse(struct list_node *curr, struct list_node *prev, struct list_node **head)
{
    if (!curr->next)
    {
        *head = curr;
        curr->next = prev;
        return NULL;
    }

    struct list_node *next = curr->next;
    curr->next = prev;
    reverse(next, curr, head);
    return NULL;
}

struct list_node *list_reverse(struct list_node **head)
{
    if (!head)
        return NULL;
    reverse(*head, NULL, head);
    return NULL;
}

struct list_node *remove_node(struct list_node **head, struct list_node *node_to_remove)
{
    struct list_node *curr_node = *head;
    struct list_node *next_node = curr_node->next;
    while (curr_node->next)
    {
        if (next_node == node_to_remove)
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

int main(int argc, char **args)
{
    struct string_item *Linked_List_test = NULL;

    Append_Node(Linked_List_test, "Hello World");
    Append_Node(Linked_List_test, "Ciao Mondo");
    Append_Node(Linked_List_test, "Addio Mondo");

    struct string_item *newString = string_item_new("Sarò Franco");
    list_append((struct list_node **)&Linked_List_test, &newString->node);
    remove_node((struct list_node **)&Linked_List_test, &newString->node);

    struct string_item *string_item = Linked_List_test;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item *)string_item->node.next;
    }

    printf("\nINVERT LIST :\n");
    list_reverse((struct list_node **)&Linked_List_test);
    struct string_item *string_item1 = Linked_List_test;
    while (string_item1)
    {
        printf("%s\n", string_item1->string);
        string_item1 = (struct string_item *)string_item1->node.next;
    }
    return 0;
}
