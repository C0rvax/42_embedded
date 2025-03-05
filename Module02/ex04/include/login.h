#ifndef LOGIN_H
# define LOGIN_H

# include <avr/io.h>
# include <util/delay.h>
#include "prog.h"
# include <string.h>

# define MAX_LEN 16
# define PASS "nope"
# define USER "c0rvax"
# define WELCOME "\r\nHello c0rvax!\r\nShall we play a game? tintintin!!!\r\n"

void	acceptUser(void);
void	drama(void);
void	login(void);

#endif /* __LOGIN_H */
