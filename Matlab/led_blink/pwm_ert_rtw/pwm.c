/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pwm.c
 *
 * Code generated for Simulink model 'pwm'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Jan 19 14:01:52 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "pwm.h"
#include "pwm_private.h"
#include "rtwtypes.h"
#include <math.h>

/* Block signals (default storage) */
B_pwm_T pwm_B;

/* Block states (default storage) */
DW_pwm_T pwm_DW;

/* Real-time model */
static RT_MODEL_pwm_T pwm_M_;
RT_MODEL_pwm_T *const pwm_M = &pwm_M_;
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
void pwm_step(void)
{
  real_T tmp;
  uint8_T tmp_0;

  /* Constant: '<Root>/Diirection' */
  pwm_B.Diirection = pwm_P.Diirection_Value;

  /* MATLABSystem: '<Root>/Diretion' */
  tmp = rt_roundd_snf(pwm_B.Diirection);
  if (tmp < 256.0) {
    if (tmp >= 0.0) {
      tmp_0 = (uint8_T)tmp;
    } else {
      tmp_0 = 0U;
    }
  } else {
    tmp_0 = MAX_uint8_T;
  }

  writeDigitalPin(30, tmp_0);

  /* End of MATLABSystem: '<Root>/Diretion' */
  /* DiscretePulseGenerator: '<Root>/PWM Signal' */
  pwm_B.PWMSignal = (pwm_DW.clockTickCounter < pwm_P.PWMSignal_Duty) &&
    (pwm_DW.clockTickCounter >= 0L) ? pwm_P.PWMSignal_Amp : 0.0;

  /* DiscretePulseGenerator: '<Root>/PWM Signal' */
  if (pwm_DW.clockTickCounter >= pwm_P.PWMSignal_Period - 1.0) {
    pwm_DW.clockTickCounter = 0L;
  } else {
    pwm_DW.clockTickCounter++;
  }

  /* MATLABSystem: '<Root>/PWM' */
  tmp = rt_roundd_snf(pwm_B.PWMSignal);
  if (tmp < 256.0) {
    if (tmp >= 0.0) {
      tmp_0 = (uint8_T)tmp;
    } else {
      tmp_0 = 0U;
    }
  } else {
    tmp_0 = MAX_uint8_T;
  }

  writeDigitalPin(31, tmp_0);

  /* End of MATLABSystem: '<Root>/PWM' */
  {                                    /* Sample time: [0.25s, 0.0s] */
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  pwm_M->Timing.taskTime0 =
    ((time_T)(++pwm_M->Timing.clockTick0)) * pwm_M->Timing.stepSize0;
}

/* Model initialize function */
void pwm_initialize(void)
{
  /* Registration code */
  rtmSetTFinal(pwm_M, -1);
  pwm_M->Timing.stepSize0 = 0.25;

  /* External mode info */
  pwm_M->Sizes.checksums[0] = (3817528086U);
  pwm_M->Sizes.checksums[1] = (3836750816U);
  pwm_M->Sizes.checksums[2] = (2102188636U);
  pwm_M->Sizes.checksums[3] = (3489231907U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    pwm_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(pwm_M->extModeInfo,
      &pwm_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(pwm_M->extModeInfo, pwm_M->Sizes.checksums);
    rteiSetTPtr(pwm_M->extModeInfo, rtmGetTPtr(pwm_M));
  }

  /* Start for MATLABSystem: '<Root>/Diretion' */
  pwm_DW.obj_p.matlabCodegenIsDeleted = false;
  pwm_DW.obj_p.isInitialized = 1L;
  digitalIOSetup(30, 1);
  pwm_DW.obj_p.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/PWM' */
  pwm_DW.obj.matlabCodegenIsDeleted = false;
  pwm_DW.obj.isInitialized = 1L;
  digitalIOSetup(31, 1);
  pwm_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void pwm_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Diretion' */
  if (!pwm_DW.obj_p.matlabCodegenIsDeleted) {
    pwm_DW.obj_p.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Diretion' */
  /* Terminate for MATLABSystem: '<Root>/PWM' */
  if (!pwm_DW.obj.matlabCodegenIsDeleted) {
    pwm_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
