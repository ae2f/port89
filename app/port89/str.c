#include "./strcmt.h"
#include <ae2f/cc/switchctl.h>

int port89_str(int c_ch, FILE* h_ifp, FILE* h_ofp) {
START:
	switch(c_ch) {
		case '"':
			fputc(c_ch, h_ofp);
			return c_ch = fgetc(h_ifp);

		case EOF:
			return EOF;

		case '\\':
			fputc(c_ch, h_ofp);
			c_ch = fgetc(h_ifp);
			ae2f_fallthrough;

		default:
			fputc(c_ch, h_ofp);
			c_ch = fgetc(h_ifp);
			goto START;
	}

	ae2f_unreachable();
}
