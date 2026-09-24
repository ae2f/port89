
#include "./cenum.h"
#include "./cg.h"

enum PORT89_CENUM_ {
	PORT89_CENUM_DEFAULT,

	PORT89_CENUM_E,
	PORT89_CENUM_EN,
	PORT89_CENUM_ENU,
	PORT89_CENUM_ENUM,


	PORT89_CENUM_DEF,
	/** (), [], <> */
	PORT89_CENUM_CAGE,
	PORT89_CENUM_COMMA,

	PORT89_CENUM_STR,
	PORT89_CENUM_CH,

	PORT89_CENUM_END
};

#if	0
port89_t port89_cenum(FILE* h_ifp, FILE* h_ofp) {
	port89_t r = port89_val(PORT89_OK);
	int ch = fgetc(h_ifp);



	ae2f_unreachable();
}
#endif
