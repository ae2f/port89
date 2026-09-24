#ifndef	port89_llong_h
#define port89_llong_h

#include "./stat.h"

#include <stdio.h>

/** 
 * capture long long, convert to `rd_alter`
 * */
port89_t port89_llong(const char* rd_alter, FILE* h_ifp, FILE* h_ofp);

#endif
