
typedef struct command_block
{ 
    const char cmd_name[80]; 
    int (*cmd_func)(char *); 
} command_block;

int cmd_test(char *str);
int cmd_echo(char *str);
