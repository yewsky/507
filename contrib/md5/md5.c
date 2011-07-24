/* rl_md5.c
 * Copyright (c) 2010, RoYi Infotech co.,ltd. 
 * Author: Varphone Wong (), varphone@qq.com
 * Date: 2010-08-30 19:43:37
 *
 * [Description go here]
 */

#include <stdio.h>
#include <stdlib.h>

#include "md5-private.h"

#define MD5_DIGEST_LENGTH		16

unsigned char * md5Hash(const char *buffer, size_t len, unsigned char *md)
{
	return ((unsigned char *)md5_buffer(buffer, len, md));
}



void md5FromString(const char *str, unsigned char *md)
{
	if (str != NULL && md != NULL) {
		sscanf(str,
			   	"%2hhx%2hhx%2hhx%2hhx"
				"%2hhx%2hhx%2hhx%2hhx"
				"%2hhx%2hhx%2hhx%2hhx"
				"%2hhx%2hhx%2hhx%2hhx",
				&md[0], &md[1], &md[2], &md[3],
				&md[4], &md[5], &md[6], &md[7],
				&md[8], &md[9], &md[10], &md[11],
				&md[12], &md[13], &md[14], &md[15]);
	}
}


void md5ToString(const unsigned char *md, char *str)
{
	int		i = 0;
	if (md != NULL && str != NULL) {
		for (i=0; i<16; i++) {
			sprintf(&str[i*2], "%02x", md[i]);
		}
		str[16*2] = '\0';
	}
}

