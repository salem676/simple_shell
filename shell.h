#define UNUSED(x) (void)x


char *_strcat(char *dest, char *src);
char *_strdup(char *original);
int _strlen(char *s);
char **find_path(char **env);
char **split_line(char *line, char *delim);
char **concat_command(char **dirs_path, char *cmd);
char *read_line(void);
char *remove_char(char *line, char c);
void execute_path(char **_path);
char **make_env(char **env);
