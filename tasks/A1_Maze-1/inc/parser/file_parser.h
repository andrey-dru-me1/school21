#ifndef D74D692F_5AE9_4013_AFD6_7BEA3B662DB8
#define D74D692F_5AE9_4013_AFD6_7BEA3B662DB8

void file_parser_parse(char *fname, void (*func)(char *token, void *args[]),
                       void *args[]);

#endif /* D74D692F_5AE9_4013_AFD6_7BEA3B662DB8 */
