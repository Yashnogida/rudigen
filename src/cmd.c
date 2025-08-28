#include <stdio.h>
#include "cmd.h"

command_block terminal_commands[] =
{
    "echo", cmd_echo,
    "test", cmd_test,
};

int cmd_test(char *str);

int cmd_echo(char *str)
{
    
}


int cmd_test(char *str)
{
    printf("TEST 0");
}
