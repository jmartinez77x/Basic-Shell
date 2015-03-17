//Programmer's name: Joe Martinez
//hash_table.h holds the functions of hash_table.c

extern struct Table *t;

struct Node;
struct Table;
struct Table *Table_create(void);
unsigned int hash(const char *x);
void  Table_add(char *key, char *value);
char* Table_search(const char *key);
void  Table_free(struct Table *t);
void  Table_print();