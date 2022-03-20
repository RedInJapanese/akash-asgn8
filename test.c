#include "bv.h" 
#include <stdio.h>

int main(void) {
	BitVector *bv = bv_create(128);
	printf("CURRENT LENGTH: %u\n", bv_length(bv));
	bv_print(bv);

	bv_set_bit(bv, 0); 
	bv_set_bit(bv, 7); 
	bv_set_bit(bv, 4);
	bv_print(bv);

	bv_clr_bit(bv, 7); 
	bv_print(bv);

	bool bit = false;
	printf("FIRST BIT IS: %d\n", bv_get_bit(bv, 0, &bit));

	bv_set_64(bv, 120);
	bv_print(bv);

	bv_clr_64(bv,120);
	bv_print(bv);

	bv_set_64(bv, 0);
	bv_print(bv); 

	bv_clr_64(bv, 0);
	bv_print(bv);

	printf("NUMBER OF WRITES: %u\n", bv_writes(bv));
	bv_delete(&bv);
	return 0; 
}

