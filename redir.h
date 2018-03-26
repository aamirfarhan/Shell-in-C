#ifndef _REDIR_H
#define _REDIR_H

int redir_check(char **tokens);
int redir_input(char **tokens);
int redir_output(char **tokens);
int redir_output_append(char **tokens);

#endif