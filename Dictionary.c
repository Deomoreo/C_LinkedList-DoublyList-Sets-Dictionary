#include "SetsHeader.h"

set_node* InsertKeyValue(set_table* table, void* key,void* element,char TypeOfValue)
{
    int num = strlen((char*)key);
    set_node* dictionary_node = set_insert(table,key,num);
    dictionary_node->value = element;
    dictionary_node->valueType = TypeOfValue;
    return dictionary_node;
}
void* ExtractFromKey(set_table* table,void* key)
{
    set_node* found = key_find(table,key);
    if(found)
    {
        char type = found->valueType;
        switch(type )
        {
            case 'i':
                return (int*) found-> value;
                break;
            case 's':
                return (char*)found->value;
                break;
            case 'f':
                return (float*)found->value;
                break;
            case 'd':
                return (double*) found->value;
                break;
            case 'l':
                return (long long*) found-> value;
                break;
            case 'u':
                return (unsigned int*) found-> value;
                break;
        }
    }
    return NULL; 
}
int main (int argc,char** args)
{
    set_table* new_set = set_table_new(100);
    int anyVariable = 10;
    int intToExtract = 17;
    char* key_to_insert = "test1234"; 
    InsertKeyValue(new_set,key_to_insert,&anyVariable, 'i');

    char * key_to_insert_1 = "Saro' Franco"; 
    InsertKeyValue(new_set,key_to_insert_1,&intToExtract, 'i');
    int* extracted = ExtractFromKey(new_set,"Saro' Franco");
    printf("\nExtracted value int: %i\n\n", *extracted);
    
    InsertKeyValue(new_set,"Ciao","Saro' Franco", 'i');
    char* extracted_string = ExtractFromKey(new_set,"Ciao");
    printf("Extracted string: %s \n\n",extracted_string);

    long long  large_number = 1717171717;
    long long* large_number_ptr = &large_number;
    printf("SUPER LONG : %lld\n\n",*large_number_ptr);
    InsertKeyValue(new_set,large_number_ptr,large_number_ptr,'l');

    long long* extracted_longlong_ptr = ExtractFromKey(new_set,large_number_ptr);
    long long extracted_longlong_val = *extracted_longlong_ptr;
    printf("Extracted SUPER LONG : %lld\n\n",extracted_longlong_val);
    
    Display_Keys(new_set);

    Key_delete(new_set,"test1234");

    Display_Keys(new_set);
}