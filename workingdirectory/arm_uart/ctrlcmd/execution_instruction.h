#ifndef _EXEC_INSTRUCTION_
#define _EXEC_INSTRUCTION_

#ifdef __cplusplus
extern "C" {
#endif
/**********************云台控制命令 begin*************************/    

#define LIGHT_PWRON      2    /* 接通灯光电源 */

#define WIPER_PWRON      3    /* 接通雨刷开关 */

#define FAN_PWRON        4    /* 接通风扇开关 */

#define HEATER_PWRON     5    /* 接通加热器开关 */

#define AUX_PWRON1       6    /* 接通辅助设备开关 */

#define AUX_PWRON2       7    /* 接通辅助设备开关 */

#define SET_PRESET       8    /* 设置预置点 */

#define CLE_PRESET       9    /* 清除预置点 */


#define ZOOM_IN         11    /* 焦距以速度SS变大(倍率变大) */

#define ZOOM_OUT        12    /* 焦距以速度SS变小(倍率变小) */

#define FOCUS_NEAR      13  /* 焦点以速度SS前调 */

#define FOCUS_FAR       14  /* 焦点以速度SS后调 */

#define IRIS_OPEN       15  /* 光圈以速度SS扩大 */

#define IRIS_CLOSE      16  /* 光圈以速度SS缩小 */

#define TILT_UP            21    /* 云台以SS的速度上仰 */

#define TILT_DOWN        22    /* 云台以SS的速度下俯 */

#define PAN_LEFT        23    /* 云台以SS的速度左转 */

#define PAN_RIGHT        24    /* 云台以SS的速度右转 */

#define UP_LEFT            25    /* 云台以SS的速度上仰和左转 */

#define UP_RIGHT        26    /* 云台以SS的速度上仰和右转 */

#define DOWN_LEFT        27    /* 云台以SS的速度下俯和左转 */

#define DOWN_RIGHT        28    /* 云台以SS的速度下俯和右转 */

#define PAN_AUTO        29    /* 云台以SS的速度左右自动扫描 */


#define FILL_PRE_SEQ    30    /* 将预置点加入巡航序列 */

#define SET_SEQ_DWELL    31    /* 设置巡航点停顿时间 */

#define SET_SEQ_SPEED    32    /* 设置巡航速度 */

#define CLE_PRE_SEQ        33    /* 将预置点从巡航序列中删除 */

#define STA_MEM_CRUISE    34    /* 开始记录轨迹 */

#define STO_MEM_CRUISE    35    /* 停止记录轨迹 */

#define RUN_CRUISE        36    /* 开始轨迹 */

#define RUN_SEQ            37    /* 开始巡航 */

#define STOP_SEQ        38    /* 停止巡航 */

#define GOTO_PRESET        39    /* 快球转到预置点 */

#define DEL_SEQ         43  /* 删除巡航路径 */

#define STOP_CRUISE        44    /* 停止轨迹 */

#define DELETE_CRUISE    45    /* 删除单条轨迹 */

#define DELETE_ALL_CRUISE 46/* 删除所有轨迹 */

#define PAN_CIRCLE      50   /* 云台以SS的速度自动圆周扫描 */

#define DRAG_PTZ        51   /* 拖动PTZ */

#define LINEAR_SCAN     52   /* 区域扫描 */ //2014-03-15 

#define CLE_ALL_PRESET  53   /* 预置点全部清除 */ 

#define CLE_ALL_SEQ     54   /* 巡航全部清除 */ 

#define CLE_ALL_CRUISE  55   /* 轨迹全部清除 */ 

#define POPUP_MENU      56   /* 显示操作菜单 */

#define TILT_DOWN_ZOOM_IN   58  /* 云台以SS的速度下俯&&焦距以速度SS变大(倍率变大) */

#define TILT_DOWN_ZOOM_OUT  59  /* 云台以SS的速度下俯&&焦距以速度SS变小(倍率变小) */

#define PAN_LEFT_ZOOM_IN    60  /* 云台以SS的速度左转&&焦距以速度SS变大(倍率变大)*/

#define PAN_LEFT_ZOOM_OUT   61  /* 云台以SS的速度左转&&焦距以速度SS变小(倍率变小)*/

#define PAN_RIGHT_ZOOM_IN   62  /* 云台以SS的速度右转&&焦距以速度SS变大(倍率变大) */

#define PAN_RIGHT_ZOOM_OUT  63  /* 云台以SS的速度右转&&焦距以速度SS变小(倍率变小) */

#define UP_LEFT_ZOOM_IN     64  /* 云台以SS的速度上仰和左转&&焦距以速度SS变大(倍率变大)*/

#define UP_LEFT_ZOOM_OUT    65  /* 云台以SS的速度上仰和左转&&焦距以速度SS变小(倍率变小)*/

#define UP_RIGHT_ZOOM_IN    66  /* 云台以SS的速度上仰和右转&&焦距以速度SS变大(倍率变大)*/

#define UP_RIGHT_ZOOM_OUT   67  /* 云台以SS的速度上仰和右转&&焦距以速度SS变小(倍率变小)*/

#define DOWN_LEFT_ZOOM_IN   68  /* 云台以SS的速度下俯和左转&&焦距以速度SS变大(倍率变大) */

#define DOWN_LEFT_ZOOM_OUT  69  /* 云台以SS的速度下俯和左转&&焦距以速度SS变小(倍率变小) */

#define DOWN_RIGHT_ZOOM_IN  70  /* 云台以SS的速度下俯和右转&&焦距以速度SS变大(倍率变大) */

#define DOWN_RIGHT_ZOOM_OUT 71  /* 云台以SS的速度下俯和右转&&焦距以速度SS变小(倍率变小) */

#define TILT_UP_ZOOM_IN     72  /* 云台以SS的速度上仰&&焦距以速度SS变大(倍率变大) */

#define TILT_UP_ZOOM_OUT    73  /* 云台以SS的速度上仰&&焦距以速度SS变小(倍率变小) */

/**********************云台控制命令 end*************************/

#ifdef __cplusplus
}
#endif

#endif
















