#include "./strcmt.h"
#include "./cg.h"

enum PORT89_CMT_ {
	PORT89_CMT_ENTRY,
	PORT89_CMT_ONELINER,
	PORT89_CMT_STAR,
	PORT89_CMT_STAR2
};

int port89_cmt(int ch, FILE* h_ifp, FILE* h_ofp) {
	cgswtch(enum PORT89_CMT_, PORT89_CMT_ENTRY, name) {
		cgdefault(PORT89_CMT_ENTRY):
		{
			switch(ch) {
				case '*':
					fputc('*', h_ofp);
					ch = fgetc(h_ifp);
					cgjmp(cgcase(PORT89_CMT_STAR), name);
				case '/':
					fputc('*', h_ofp);
					ch = fgetc(h_ifp);
					cgjmp(cgcase(PORT89_CMT_ONELINER), name);
				default:
					fputc(ch, h_ofp);
					return fgetc(h_ifp);
			}
		}

		cgcsdef(PORT89_CMT_ONELINER): switch(ch) {
			case '\n':
				fputs(" */\n", h_ofp);
				return fgetc(h_ifp);

			case EOF:
				return EOF;

			case '/':
				fputs("\\/", h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_CMT_ONELINER), name);

			case '\\':
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				ae2f_fallthrough;

			default:
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_CMT_ONELINER), name);
		}

		cgcsdef(PORT89_CMT_STAR): switch(ch) {
			case '*':
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_CMT_STAR2), name);

			case EOF:
				return EOF;

			default:
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_CMT_STAR), name);
		}

		cgcsdef(PORT89_CMT_STAR2): switch(ch) {
			case '/':
				fputc(ch, h_ofp);
				return fgetc(h_ifp);

			case EOF:
				return EOF;

			default:
				fputc(ch, h_ofp);
				ch = fgetc(h_ifp);
				cgjmp(cgcase(PORT89_CMT_STAR), name);
		}
	}

	ae2f_unreachable();
}
