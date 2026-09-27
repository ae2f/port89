#include "./port89/llong.h"
#include "./port89/scomma.h"

#include <ae2f/cc/branches/naive.h>

#define	RET(x)	{ ret = (int)(x); goto OUT; }

int main(int c_argc, const char* rd_argv[]);
int main(int c_argc, const char* rd_argv[]) {
	port89_t ret = port89_val(PORT89_OK);
	FILE
		*h = 0,
		*h_r0 = 0,
		*h_r1 = 0;	/**/;

	if(c_argc < 5)		RET(PORT89_ARGS);
	if((~c_argc & 1))	RET(PORT89_ARGS);

	while((c_argc -= 2) > 2) {
		h		= fopen(rd_argv[c_argc], "r");
		h_r0		= tmpfile();
		h_r1		= fopen(rd_argv[c_argc + 1], "w+");

		if(!h)		RET(PORT89_FILE);
		if(!h_r0)	RET(PORT89_FILE);
		if(!h_r1)	RET(PORT89_FILE);

#define	h_ret	h_r1

		ae2f_ifnezerr(ret = port89_llong(
					rd_argv[1]
					, rd_argv[2]
					, h
					, h_r0))
			goto OUT;


		fseek(h_r0, 0, SEEK_SET);

		ae2f_ifnezerr(ret = port89_scomma(
					h_r0
					, h_ret))
			goto OUT;

#undef	h_ret

		fclose(h);
		fclose(h_r0);
		fclose(h_r1);

		h	= 0;
		h_r0	= 0;
		h_r1	= 0;
	}

OUT:
	if(h)		fclose(h);
	if(h_r0)	fclose(h_r0);
	if(h_r1)	fclose(h_r1);
	return (int)ret;
}
