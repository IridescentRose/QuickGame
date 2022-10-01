#include <Timer.h>
#include <time.h>
#include <psprtc.h>

/**
 * @brief Start a timer
 * 
 * @param timer Timer to use
 */
void QuickGame_Timer_Start(QGTimer* timer) {
    timer->resolution = sceRtcGetTickResolution();
    sceRtcGetCurrentTick(&timer->last);
    timer->total = 0;
}

/**
 * @brief Get Delta from last delta request / start
 * 
 * @param timer Timer to use
 * @return double Delta Time
 */
double QuickGame_Timer_Delta(QGTimer* timer) {
    u64 current;
    sceRtcGetCurrentTick(&current);

	double dt = (double)(current - timer->last) / ((double)timer->resolution);
    timer->total += dt;

    timer->last = current;

    return dt;
}

/**
 * @brief Elapsed total time since start
 * 
 * @param timer Timer to use
 * @return double Elapsed Time
 */
double QuickGame_Timer_Elapsed(QGTimer* timer) {
    return timer->total;
}

/**
 * @brief Resets a timer
 * 
 * @param timer Timer to use
 */
void QuickGame_Timer_Reset(QGTimer* timer) {
    sceRtcGetCurrentTick(&timer->last);
    timer->total = 0.0f;
}