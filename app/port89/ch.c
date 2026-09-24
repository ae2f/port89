#include "./strcmt.h"
#include <ae2f/cc/switchctl.h>

int port89_ch(int c_ch, FILE* h_ifp, FILE* h_ofp) {
START:
	switch(c_ch) {
		case '\'':
			fputc(c_ch, h_ofp);
			return c_ch = fgetc(h_ifp);

		case '\\':
			fputc(c_ch, h_ofp);
			c_ch = fgetc(h_ifp);
			ae2f_fallthrough;

		case EOF:
			return EOF;

		default:
			fputc(c_ch, h_ofp);
			c_ch = fgetc(h_ifp);
			goto START;
	}

	ae2f_unreachable();
}
