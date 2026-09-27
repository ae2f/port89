#include "./tok.h"

int port89_tok_match(char* rdwr_tok, size_t c_tok_len, int c_ch, FILE* h_ifs) {
	size_t idx;

	for(idx = 0; idx < c_tok_len && (((int)rdwr_tok[idx]) == c_ch); ++idx)
		c_ch = fgetc(h_ifs);

	if(idx < c_tok_len) {
		rdwr_tok[idx] = ((char)0);
	}

	return c_ch;
}
