#ifndef _NDVR_CMD_H_
#define _NDVR_CMD_H_

enum ndvr_command_e {
    CMD_REQ_SECODE = 10,					/* 安全码请求 */
    CMD_REP_SECODE,

    CMD_REQ_LOGIN,							/* 登录请求 */
    CMD_REP_LOGIN,

    CMD_REQ_LOGOUT,							/* 登出请求 */
    CMD_REP_LOGOUT,

    CMD_REQ_ALIVE,							/* 检测是否存活 */
    CMD_REP_ALIVE,

    CMD_REQ_DISCOVERY = 20,					/* 设备发现请求 */
    CMD_REP_DISCOVERY,

    CMD_REQ_DISCOVERY_SET,					/* 设备发现配置修改请求 */
    CMD_REP_DISCOVERY_SET,

    CMD_REQ_SHUTDOWN = 30,					/* 关机请求 */
    CMD_REP_SHUTDOWN,

    CMD_REQ_REBOOT,							/* 重启请求 */
    CMD_REP_REBOOT,

    CMD_REQ_RESET,							/* 重置请求 */
    CMD_REP_RESET,

    CMD_REQ_UPGRADE,						/* 升级请求 */
    CMD_REP_UPGRADE,

    CMD_REQ_SYNC_TIME,						/* 同步时间请求 */
    CMD_REP_SYNC_TIME,

    CMD_REQ_CONTROL,						/* 设备控制指令 */
    CMD_REP_CONTROL,

    CMD_REQ_DIAG,							/* 对设备进行各种诊断 */
    CMD_REP_DIAG,

    CMD_REQ_EXEC,							/* 执行命令 */
    CMD_REP_EXEC,

    CMD_REQ_GET_CHANNEL = 1000,				/* 获取通道配置请求 */
    CMD_REP_GET_CHANNEL,

    CMD_REQ_GET_NETWORK,					/* 获取网络配置请求 */
    CMD_REP_GET_NETWORK,

    CMD_REQ_GET_SERVICE,					/* 获取服务配置请求 */
    CMD_REP_GET_SERVICE,

    CMD_REQ_GET_SYSTEM,						/* 获取系统配置请求 */
    CMD_REP_GET_SYSTEM,

    CMD_REQ_GET_USERS,						/* 获取用户管理请求 */
    CMD_REP_GET_USERS,

    CMD_REQ_GET_ABILITY,					/* 获取设备能力请求 */
    CMD_REP_GET_ABILITY,

    CMD_REQ_GET_STATISTICS,					/* 获取设备统计信息请求 */
    CMD_REP_GET_STATISTICS,

    CMD_REQ_GET_AUDIORECORD,
    CMD_REP_GET_AUDIORECORD,

    CMD_REQ_GET_VIDEORECORD,
    CMD_REP_GET_VIDEORECORD,

    CMD_REQ_GET_SNAPSHOT,
    CMD_REP_GET_SNAPSHOT,

    CMD_REQ_GET_ALARMLOG,
    CMD_REP_GET_ALARMLOG,

    CMD_REQ_GET_SYSTEMLOG,
    CMD_REP_GET_SYSTEMLOG,

    CMD_REQ_GET_STREAM,
    CMD_REP_GET_STREAM,

    CMD_REQ_GET_AUDIO,
    CMD_REP_GET_AUDIO,

    CMD_REQ_GET_VIDEO,
    CMD_REP_GET_VIDEO,

    CMD_REQ_LST_FILE,
    CMD_REP_LST_FILE,

    CMD_REQ_GET_FILE,
    CMD_REP_GET_FILE,

    CMD_REQ_SET_CHANNEL = 2000,
    CMD_REP_SET_CHANNEL,

    CMD_REQ_SET_NETWORK,
    CMD_REP_SET_NETWORK,

    CMD_REQ_SET_SERVICE,
    CMD_REP_SET_SERVICE,

    CMD_REQ_SET_SYSTEM,
    CMD_REP_SET_SYSTEM,

    CMD_REQ_SET_USERS,
    CMD_REP_SET_USERS,

    CMD_REQ_SET_ABILITIES,
    CMD_REP_SET_ABILITIES,

    CMD_REQ_SET_STATISTICS,
    CMD_REP_SET_STATISTICS,

    CMD_REQ_MAN_FILE,
    CMD_REP_MAN_FILE,

    CMD_REQ_MAN_STORAGE,
    CMD_REP_MAN_STORAGE,

    CMD_REQ_CTRL_AUDIO = 3000,                   /* 开关录音控制 */
    CMD_REP_CTRL_AUDIO,

    CMD_REQ_CTRL_VIDEO,
    CMD_REP_CTRL_VIDEO,

    CMD_REQ_CTRL_PTZ,							/* 云台控制 */
    CMD_REP_CTRL_PTZ,

    CMD_REQ_READ_SERIALPORT,
    CMD_REP_READ_SERIALPORT,

    CMD_REQ_WRITE_SERIALPORT,
    CMD_REP_WRITE_SERIALPORT,

    CMD_REQ_CTRL_ALARMOUT,
    CMD_REP_CTRL_ALARMOUT,

    CMD_REQ_CTRL_IRCUT,
    CMD_REP_CTRL_IRCUT,

    CMD_REQ_DO_SNAPSHOT,
    CMD_REP_DO_SNAPSHOT,

    CMD_REQ_RAWDATA,
    CMD_REP_RAWDATA,

    CMD_REQ_PUT_AUDIO,
    CMD_REP_PUT_AUDIO,

    CMD_REQ_NOTIFY = 4000,					/* 请求通知消息(预留) */
    CMD_REP_NOTIFY							/* 回应通知消息 */
};

enum ndvr_reflag_e {
    RF_ERROR = -1		/**< response is error */
    , RF_OK				/**< response is ok */
    , RF_PAUSE			/**< transfer is paused */
    , RF_RESUME			/**< transfer is resume from pause state */
    , RF_STOP			/**< transfer is topped */
    , RF_KEEPALIVE /**< keep alive */
};

#endif /* _NDVR_CMD_H_ */
