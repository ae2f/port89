
#include <ae2f/cc/qualifier.h>

#include "./llong.h"
#include "./cg.h"
#include "./strcmt.h"
#include "./flush.h"
#include "./tok.h"

#include <ctype.h>
#include <string.h>


enum PORT89_LLONG_ {
	PORT89_LLONG_DEFAULT,
	PORT89_LLONG_FLUSH,

	PORT89_LLONG_LONG,
	PORT89_LLONG_UNSIGNED,

	PORT89_LLONG_END
};

typedef int port89_bool_t;

port89_t port89_llong(const char* rd_ll, const char* rd_ull, FILE* h_ifp, FILE* h_ofp) {
	port89_t r = port89_val(PORT89_OK);
	port89_bool_t found = 0;
	port89_bool_t found_unsigned = 0;
	int ch = fgetc(h_ifp);

	cgswtch(enum PORT89_LLONG_, PORT89_LLONG_DEFAULT, name) {
		cgcsdef(PORT89_LLONG_DEFAULT): switch((ch)) {
			case EOF:
				cgjmp(cgcase(PORT89_LLONG_END), name);

			case 'u':
				if(!found_unsigned) {
					char tok[] = "unsigned";
					ch = port89_tok_match(tok, sizeof(tok) - 1, ch, h_ifp);

					if(strlen(tok) < 8) {
						if(found_unsigned)
							fputs("unsigned ", h_ofp);
						if(found)
							fputs("long ", h_ofp);
						fputs(tok, h_ofp);
						cgjmp(cgcase(PORT89_LLONG_FLUSH), name);
					} else {
						cgjmp(cgcase(PORT89_LLONG_UNSIGNED), name);
					}
				} else {
					found_unsigned = 0;
					fputs("unsigned ", h_ofp);
					if(found) {
						fputs("long ", h_ofp);
					}
					cgjmp(cgcase(PORT89_LLONG_FLUSH), name);

				}

			case 'l':
				{
					char tok[] = "long";
					ch = port89_tok_match(tok, sizeof(tok) - 1, ch, h_ifp);

					if(strlen(tok) < 4) {
						if(found_unsigned)
							fputs("unsigned ", h_ofp);
						if(found)
							fputs("long ", h_ofp);
						fputs(tok, h_ofp);
						cgjmp(cgcase(PORT89_LLONG_FLUSH), name);
					} else {
						cgjmp(cgcase(PORT89_LLONG_LONG), name);
					}
				}

			case '/':
				fputc(ch, h_ofp);
				ch = port89_cmt(fgetc(h_ifp), h_ifp, h_ofp);
				cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);

			case '"':
				fputc(ch, h_ofp);
				ch = port89_str(fgetc(h_ifp), h_ifp, h_ofp);
				cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);

			case '\'':
				fputc(ch, h_ofp);
				ch = port89_ch(fgetc(h_ifp), h_ifp, h_ofp);
				cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);

			default:
				if(isspace(ch)) {
					fputc(ch, h_ofp);
					ch = fgetc(h_ifp);
					cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);
				} else {
					if(found_unsigned)
						fputs("unsigned ", h_ofp);

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
			found_unsigned = 0;
			ch = port89_flush(ch, h_ifp, h_ofp);
			cgjmp(ch == EOF ? cgcase(PORT89_LLONG_END) : cgcase(PORT89_LLONG_DEFAULT), name);
		}

		cgcsdef(PORT89_LLONG_UNSIGNED):
		{
			if(isspace(ch)) {
				found_unsigned = 1;
				fputs("/** unsigned */", h_ofp);
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);
			} else {
				if(found_unsigned)
					fputs("unsigned ", h_ofp);

				if(found)
					fputs("long ", h_ofp);
				fputs("long", h_ofp);
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_FLUSH), name);
			}
		}

		cgcsdef(PORT89_LLONG_LONG):
		{
			if(isspace(ch)) {
				if(found++) {
					/** emit new */
					found = 0;
					fputs(found_unsigned ? rd_ull : rd_ll, h_ofp);
					found_unsigned = 0;
				}

				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_DEFAULT), name);
			} else {
				if(found_unsigned)
					fputs("unsigned ", h_ofp);

				if(found)
					fputs("long ", h_ofp);
				fputs("long", h_ofp);
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_LLONG_FLUSH), name);
			}
		}

		/*************************/

		cgdefault(PORT89_LLONG_END):
		{
			return r;
		}
	}

	ae2f_unreachable();
}
