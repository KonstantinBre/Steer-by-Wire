/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: led_blink.c
 *
 * Code generated for Simulink model 'led_blink'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed Jan 17 14:22:10 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "led_blink.h"
#include "led_blink_private.h"
#include "rtwtypes.h"
#include <math.h>

/* Block signals (default storage) */
B_led_blink_T led_blink_B;

/* Block states (default storage) */
DW_led_blink_T led_blink_DW;

/* Real-time model */
static RT_MODEL_led_blink_T led_blink_M_;
RT_MODEL_led_blink_T *const led_blink_M = &led_blink_M_;
real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void led_blink_step(void)
{
  real_T tmp;
  uint8_T tmp_0;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  led_blink_B.PulseGenerator = (led_blink_DW.clockTickCounter <
    led_blink_P.PulseGenerator_Duty) && (led_blink_DW.clockTickCounter >= 0L) ?
    led_blink_P.PulseGenerator_Amp : 0.0;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  if (led_blink_DW.clockTickCounter >= led_blink_P.PulseGenerator_Period - 1.0)
  {
    led_blink_DW.clockTickCounter = 0L;
  } else {
    led_blink_DW.clockTickCounter++;
  }

  /* MATLABSystem: '<Root>/Digital Output' */
  tmp = rt_roundd_snf(led_blink_B.PulseGenerator);
  if (tmp < 256.0) {
    if (tmp >= 0.0) {
      tmp_0 = (uint8_T)tmp;
    } else {
      tmp_0 = 0U;
    }
  } else {
    tmp_0 = MAX_uint8_T;
  }

  writeDigitalPin(13, tmp_0);

  /* End of MATLABSystem: '<Root>/Digital Output' */
  {                                    /* Sample time: [0.25s, 0.0s] */
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  led_blink_M->Timing.taskTime0 =
    ((time_T)(++led_blink_M->Timing.clockTick0)) * led_blink_M->Timing.stepSize0;
}

/* Model initialize function */
void led_blink_initialize(void)
{
  /* Registration code */
  rtmSetTFinal(led_blink_M, -1);
  led_blink_M->Timing.stepSize0 = 0.25;

  /* External mode info */
  led_blink_M->Sizes.checksums[0] = (4052094993U);
  led_blink_M->Sizes.checksums[1] = (2861084639U);
  led_blink_M->Sizes.checksums[2] = (1723898484U);
  led_blink_M->Sizes.checksums[3] = (1254800667U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    led_blink_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(led_blink_M->extModeInfo,
      &led_blink_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(led_blink_M->extModeInfo, led_blink_M->Sizes.checksums);
    rteiSetTPtr(led_blink_M->extModeInfo, rtmGetTPtr(led_blink_M));
  }

  /* Start for MATLABSystem: '<Root>/Digital Output' */
  led_blink_DW.obj.matlabCodegenIsDeleted = false;
  led_blink_DW.obj.isInitialized = 1L;
  digitalIOSetup(13, 1);
  led_blink_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void led_blink_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Digital Output' */
  if (!led_blink_DW.obj.matlabCodegenIsDeleted) {
    led_blink_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Output' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
