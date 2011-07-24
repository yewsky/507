#ifndef _MESSAGE_H_
#define _MESSAGE_H_

/**
 * 函数执行结果;
 */
enum _ERROR_R {
	  NE_ERROR = -2 /**< 发生致命错误 */
	, NE_FAIL /**< 执行失败 */
	, NE_OK /**< 执行成功 */
	, NE_AGAIN /**< 设备忙资源处于锁定状态(短暂), 需要再次尝试 */
	, NE_BUSY /**< 设备忙资源处于锁定状态(时间较长), 根据需要自行重试 */
};

struct Message {
    int 	 flag; /**< 执行结果标志 */
    uint32_t size;
    char 	 content[]; /**< 接收到的数据 */
};

#endif
