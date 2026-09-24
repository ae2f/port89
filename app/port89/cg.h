#ifndef	port89_cg_H
#define port89_cg_H

#include <ae2f/cgoto.h>

#if	ae2f_cgoto_available
#	define	cgswtch(ty, a, name)	goto LBL_##a;
#	define	cgcsdef(a)		LBL_##a
#	define	cgdefault		cgcsdef
#	define	cgcase(a)		(&&LBL_##a)
#	define	cgjmp(a, name)		ae2f_cgoto_beg(); goto *(a); ae2f_cgoto_end()
#else
#	define	cgswtch(ty, a, name)	ty name##V = a; name##L: switch(name##V)
#	define	cgcsdef(a)		case a
#	define	cgdefault(a)		case a: default
#	define	cgcase(a)		a
#	define	cgjmp(a, name)		name##V = (a); goto name##L
#endif

#endif
