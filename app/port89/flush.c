#include "./flush.h"

#include <ctype.h>
#include <ae2f/cc/switchctl.h>

int port89_flush(int c_ch, FILE* h_ifp, FILE* h_ofp) {
START:
	if(isspace(c_ch) || c_ch == EOF) {
		return c_ch;
	} else {
		fputc(c_ch, h_ofp);
		c_ch = fgetc(h_ifp);
		goto START;
	}

	ae2f_unreachable();
}
