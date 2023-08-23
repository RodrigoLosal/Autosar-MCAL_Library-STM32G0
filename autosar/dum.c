/*This is a workaround file so cppcheck does not complain about autosar directory
not having nothing to lint
MUST be renmove once a source .c file is added to any of the subdirectories*/
#include <stdint.h>
#include "dum.h"

uint32_t sum( uint32_t a, uint32_t b )
{
    return a + b;
}
