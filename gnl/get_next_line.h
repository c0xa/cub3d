
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
int		writefile(int fd, char **line, char **bufs);
char	*stream(char **line, char *buf);
char	*ft_strjoin(char *s1, char *s2, int len2);
int		freestr(char **dest, char *src);
int		ft_strchr_strlen(char *str, int flag);

#endif
