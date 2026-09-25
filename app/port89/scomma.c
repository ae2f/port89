#include "./cg.h"
#include "./scomma.h"
#include "./strcmt.h"

#include <ctype.h>
#include <ae2f/cc/switchctl.h>

enum PORT89_SCOMMA_ {
	PORT89_SCOMMA_DEFAULT,
	PORT89_SCOMMA_COMMA,
	PORT89_SCOMMA_END
};

port89_t port89_scomma(FILE* h_ifp, FILE* h_ofp) {
	int ch = fgetc(h_ifp);
	port89_t r = port89_val(PORT89_OK);

	cgswtch(enum PORT89_SCOMMA_, PORT89_SCOMMA_DEFAULT, name) {
		cgcsdef(PORT89_SCOMMA_DEFAULT): switch(ch) {
			case EOF:
				cgjmp(cgcase(PORT89_SCOMMA_END), name);
			case '/':
				fputc(ch, h_ofp);
				ch = port89_cmt(fgetc(h_ifp), h_ifp, h_ofp);
				cgjmp(cgcase(PORT89_SCOMMA_DEFAULT), name);

			case '"':
				fputc(ch, h_ofp);
				ch = port89_str(fgetc(h_ifp), h_ifp, h_ofp);
				cgjmp(cgcase(PORT89_SCOMMA_DEFAULT), name);

			case '\'':
				fputc(ch, h_ofp);
				ch = port89_ch(fgetc(h_ifp), h_ifp, h_ofp);
				cgjmp(cgcase(PORT89_SCOMMA_DEFAULT), name);

			case ',':
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_SCOMMA_COMMA), name);

			default:
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_SCOMMA_DEFAULT), name);
		}

		cgdefault(PORT89_SCOMMA_END): {
			return r;
		}

		cgcsdef(PORT89_SCOMMA_COMMA): switch(ch) {
			case ',':
				/** self */
				fputs(",", h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_SCOMMA_COMMA), name);

			case '/':
				fputc(ch, h_ofp);
				ch = port89_cmt(fgetc(h_ifp), h_ifp, h_ofp);
				cgjmp(cgcase(PORT89_SCOMMA_COMMA), name);

			case '"':
				fputc(ch, h_ofp);
				ch = port89_str(fgetc(h_ifp), h_ifp, h_ofp);
				cgjmp(cgcase(PORT89_SCOMMA_DEFAULT), name);

			case '\'':
				fputc(ch, h_ofp);
				ch = port89_ch(fgetc(h_ifp), h_ifp, h_ofp);
				cgjmp(cgcase(PORT89_SCOMMA_COMMA), name);

			case EOF:
				cgjmp(cgcase(PORT89_SCOMMA_END), name);

			case ';':
			case '>':
			case '}':
				/** not permitted */
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_SCOMMA_DEFAULT), name);

			default:
				if(isspace(ch)) {
					fputc(ch, h_ofp);
					ch = fgetc(h_ifp);
					cgjmp(cgcase(PORT89_SCOMMA_COMMA), name);
				} else {
					fputs(" , ", h_ofp);
					fputc(ch, h_ofp);
					ch = fgetc(h_ifp);
					cgjmp(cgcase(PORT89_SCOMMA_DEFAULT), name);
				}

				ae2f_unreachable();
		}
	}

	ae2f_unreachable();
}
