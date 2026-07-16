#ifndef EPWM_H
#define EPWM_H

#define TB_PERIOD 1000
#define DUTY_MAX TB_PERIOD
#define DUTY_MIN 0
#define PWM_FRQ SYSCLK_FRQ / (2 * TB_PERIOD)

void InitEPwm1Simple(void);
void InitEPwm6Simple(void);
void InitEPwm1Soc(void);

// 原来的所有内容

#endif
