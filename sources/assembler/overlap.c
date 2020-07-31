#include "asm.h"

/*
** A simple function to check if the given types overlap.
** Returns the sum of values that overlap.
**
** Examples of usage:
** Can be used to check if currently checked argument type is valid:
** overlap(T_REG, token->type);
** overlap(T_REG | T_IND, token->type);
**
** overlap(T_REG | T_IND | T_DIR, T_IND | T_DIR); // returns (T_IND | T_DIR)
*/

int		overlap(int type1, int type2)
{
	return (type1 & type2);
}
