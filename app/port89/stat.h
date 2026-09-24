#ifndef	zeit89_stat_h
#define zeit89_stat_h

#include <ae2f/c90/stdint.h>

enum PORT89_ {
	PORT89_OK,
	PORT89_ARGS,
	PORT89_FILE,
	PORT89_MAX
};

/** see ZEIT89_ */
typedef uint16_t port89_t;
typedef int port89_t_max[((enum PORT89_)(port89_t)PORT89_MAX) == PORT89_MAX ? 1 : -1];

#define port89_val(c)	((port89_t)(c))

#endif
