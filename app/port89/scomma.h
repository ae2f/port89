#ifndef	port89_scomma_h
#define port89_scomma_h

#include <stdio.h>
#include "./stat.h"

/** erase ',' when faced { , } | <, > pattern */
port89_t port89_scomma(FILE* h_ifp, FILE* h_ofp);

#endif
