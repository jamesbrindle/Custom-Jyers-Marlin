#define MEATPACK

/**
 * PWM Fan Scaling
 *
 * Define the min/max speeds for PWM fans (as set with M106).
 *
 * With these options the M106 0-255 value range is scaled to a subset
 * to ensure that the fan has enough power to spin, or to run lower
 * current fans with higher current. (e.g., 5V/12V fans with 12V/24V)
 * Value 0 always turns off the fan.
 *
 * Define one or both of these to override the default 0-255 range.
 */
#define FAN_MIN_PWM 178

#define HOMING_BUMP_MM      { 5, 5, 2 }       // (mm) Backoff from endstops after first bump
#define HOMING_BUMP_DIVISOR { 2, 2, 8 }       // Re-Bump Speed Divisor (Divides the Homing Feedrate)

#if PROBE_SELECTED && !IS_KINEMATIC
  #define PROBING_MARGIN_LEFT 15
  #define PROBING_MARGIN_RIGHT 0
  #define PROBING_MARGIN_FRONT 15
  #define PROBING_MARGIN_BACK 15
#endif