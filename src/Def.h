#ifndef _DEF_H_
#define _DEF_H_

#pragma pack(1)
struct RequestHeader {
    uint32_t		proto;							/* 协议版本 */
    uint32_t		extra;							/* 内容长度 */
    uint32_t		cmd;							/* 指令编号 */
    uint32_t		cmd_sn;							/* 指令序号 */
    uuid_t			uu_src;							/* 源　唯一编号 */
    uuid_t			uu_dst;							/* 目标唯一编号 */
};
#pragma pack()


#pragma pack(1)
struct ResponseHeader {
    uint32_t		proto;							/* 协议版本 */
    uint32_t		extra;							/* 内容长度 */
    uint32_t		cmd;							/* 指令编号 */
    uint32_t		cmd_sn;							/* 指令序号 */
    int32_t			flags;							/* 执行标志 */
};
#pragma pack()

/**
 * Session 回应接收结构体
 */
struct Response {
    ResponseHeader 	hdr;
    char 			content[MAX_CONTENT_LEN];
};

/**
 * Session 发送结构体
 */
struct Request {
    RequestHeader 	hdr;
    char 			content[MAX_CONTENT_LEN];
};


/**
 * transmit frame header
 */
struct TransmitFrameHeader {
	uint8_t type;				/**< frame type, 0=NULL 1=Audio 2=Video */
	uint8_t sync;				/**< synchronization flags */
	uint16_t flags;				/**< frame content flags */
	uint32_t size;				/**< frame size */
	uint32_t pts_low;			/**< frame pts (low) */
	uint32_t pts_high;			/**< frame pts (high) */
	uint32_t counter;			/**< frame counter */
};

/**
 * transmit frame
 */
struct TransmitFrame {
	TransmitFrameHeader	hdr;		/* transmit header */
	char				data[0];	/* transmit data */
};


#endif /* _DEF_H_ */
