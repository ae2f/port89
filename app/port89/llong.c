#include "./llong.h"
#include "./cg.h"

#include <ctype.h>

enum PORT89_LLONG_ {
	PORT89_LLONG_DEFAULT,
	PORT89_LLONG_FLUSH,

	PORT89_LLONG_L,
	PORT89_LLONG_LO,
	PORT89_LLONG_LON,
	PORT89_LLONG_LONG,

	PORT89_LLONG_CMT_ENTRY,
	PORT89_LLONG_CMT_ONELINER,
	PORT89_LLONG_CMT_STAR,
	PORT89_LLONG_CMT_STAR2,

	PORT89_LLONG_STR,
	PORT89_LLONG_CH,

	PORT89_LLONG_END
};

typedef int port89_bool_t;

port89_t port89_llong(const char* rd_alter, FILE* h_ifp, FILE* h_ofp) {
	port89_t r = port89_val(PORT89_OK);
	port89_bool_t found = 0;
	int ch = fgetc(h_ifp);

	cgswtch(enum PORT89_LLONG_, PORT89_LLONG_DEFAULT, name) {
		cgcsdef(PORT89_LLONG_DEFAULT): switch((ch)) {
			case EOF:
				cgjmp(cgcase(PORT89_LLONG_END), name);
			case 'l':
				ch = getc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_L), name);

			case '/':
				fputc(ch, h_ofp);
				ch = getc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_CMT_ENTRY), name);

			case '"':
				fputc(ch, h_ofp);
				ch = getc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_STR), name);

			case '\'':
				fputc(ch, h_ofp);
				ch = getc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_CH), name);

			default:
				if(isspace(ch)) {
					fputc(ch, h_ofp);
					ch = fgetc(h_ifp);
					cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);
				} else {
					if(found)
						fputs("long ", h_ofp);

					fputc(ch, h_ofp);
					ch = fgetc(h_ifp);
					cgjmp(cgcase(PORT89_LLONG_FLUSH), name);
				}
		}

		cgcsdef(PORT89_LLONG_FLUSH):
		{
			found = 0;	/** resetting the shxt */

			if(isspace(ch)) {
				cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);
			} else if(ch == EOF) {
				cgjmp(cgcase(PORT89_LLONG_END), name);
			} else {
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_FLUSH), name);
			}
		}

		cgcsdef(PORT89_LLONG_L):
		{
			if(ch == 'o') {
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_LO), name);
			} else {
				if(found)
					fputs("long ", h_ofp);
				fputs("l", h_ofp);
				cgjmp(cgcase(PORT89_LLONG_FLUSH), name);
			}
		}

		cgcsdef(PORT89_LLONG_LO):
		{
			if(ch == 'n') {
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_LON), name);
			} else {
				if(found)
					fputs("long ", h_ofp);
				fputs("lo", h_ofp);
				cgjmp(cgcase(PORT89_LLONG_FLUSH), name);
			}
		}

		cgcsdef(PORT89_LLONG_LON):
		{
			if(ch == 'g') {
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_LONG), name);
			} else {
				if(found)
					fputs("long ", h_ofp);
				fputs("lon", h_ofp);
				cgjmp(cgcase(PORT89_LLONG_FLUSH), name);
			}
		}

		cgcsdef(PORT89_LLONG_LONG):
		{
			if(isspace(ch)) {
				if(found++) {
					/** emit new */
					found = 0;
					fputs(rd_alter, h_ofp);
				}

				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);
			} else {
				if(found)
					fputs("long ", h_ofp);
				fputs("long", h_ofp);
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_FLUSH), name);
			}
		}

		/*************************/

		cgcsdef(PORT89_LLONG_CMT_ENTRY):
		{
			fputc(ch, h_ofp);
			switch(ch) {
				case '*':
					ch = fgetc(h_ifp);
					cgjmp(cgcase(PORT89_LLONG_CMT_STAR), name);
				case '/':
					ch = fgetc(h_ifp);
					cgjmp(cgcase(PORT89_LLONG_CMT_ONELINER), name);
				default:
					ch = fgetc(h_ifp);
					cgjmp(cgcase(PORT89_LLONG_FLUSH), name);
			}
		}

		cgcsdef(PORT89_LLONG_CMT_ONELINER): switch(ch) {
			case '\n':
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);

			default:
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_CMT_ONELINER), name);
		}

		cgcsdef(PORT89_LLONG_CMT_STAR): switch(ch) {
			case '*':
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_CMT_STAR2), name);

			default:
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_CMT_STAR), name);
		}

		cgcsdef(PORT89_LLONG_CMT_STAR2): switch(ch) {
			case '/':
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);

			default:
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_CMT_STAR), name);
		} 

		/*************************/

		cgcsdef(PORT89_LLONG_STR): switch(ch) {
			case '"':
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);

			case '\\':
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				ae2f_fallthrough;

			default:
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_STR), name);
		} 

		/*************************/

		cgcsdef(PORT89_LLONG_CH): switch(ch) {
			case '\'':
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);

			case '\\':
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				ae2f_fallthrough;

			default:
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_CH), name);
		} 

		/*************************/

		cgdefault(PORT89_LLONG_END):
		{
			return r;
		}
	}

	ae2f_unreachable();
}
