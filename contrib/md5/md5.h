/* rl_md5.h
 * Copyright (c) 2010, RoYi Infotech co.,ltd. 
 * Author: Varphone Wong (), varphone@qq.com
 * Date: 2010-08-14 12:22:04
 *
 * [Description go here]
 */

#ifndef _RL_MD5_H_
#define _RL_MD5_H_

#include <stdlib.h>

#define MD5_DIGEST_LENGTH		16

#ifdef __cplusplus
extern "C" {
#endif /* _cplusplus */

/**
 * 获取指定缓冲区数据的HASH值;
 */
unsigned char * md5Hash(const char *buffer, size_t len, unsigned char *md);

/**
 * 将字符串格式的MD5值转为二进制形式;
 */
void md5FromString(const char *str, unsigned char *md);

/**
 * 将二进制形式的MD5值转为字符串格式;
 */
void md5ToString(const unsigned char *md, char *str);

#ifdef __cplusplus
}
#endif /* _cplusplus */

#endif /* _RL_MD5_H_ */

