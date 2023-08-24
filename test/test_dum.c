#include "unity.h"
#include "dum.h"

void setUp( void )
{
}

void tearDown( void )
{
}

void test__sum__two_integers( void )
{
    uint32_t res = sum( 2, 3 );
    TEST_ASSERT_EQUAL_MESSAGE( 5, res, "2 + 3 = 5" );
}
