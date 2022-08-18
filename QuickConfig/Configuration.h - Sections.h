#define BAUDRATE 115200

// Choose the name from boards.h that matches your setup
#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_CREALITY_V4
#endif

// The size of the print bed
#define X_BED_SIZE 230
#define Y_BED_SIZE 230

// Travel limits (mm) after homing, corresponding to endstop positions.
#define X_MIN_POS 1
#define Y_MIN_POS 2
#define Z_MIN_POS 0
#define X_MAX_POS (X_BED_SIZE + X_MIN_POS)
#define Y_MAX_POS (Y_BED_SIZE + Y_MIN_POS)
#define Z_MAX_POS 240

/**
 * Default Max Feed Rate (mm/s)
 * Override with M203
 *                                      X, Y, Z, E0 [, E1[, E2...]]
 */
#define DEFAULT_MAX_FEEDRATE          { 500, 500, 11, 80 }

//#define LIMITED_MAX_FR_EDITING        // Limit edit via M203 or LCD to DEFAULT_MAX_FEEDRATE * 2
#if ENABLED(LIMITED_MAX_FR_EDITING)
  #define MAX_FEEDRATE_EDIT_VALUES    { 600, 600, 15, 50 } // ...or, set your own edit limits
#endif

#define NOZZLE_TO_PROBE_OFFSET {  -45, -7,- 1.45 }

// Most probes should stay away from the edges of the bed, but
// with NOZZLE_AS_PROBE this can be negative for a wider probing area.
#define PROBING_MARGIN 15

// X and Y axis travel speed (mm/min) between probes
#define XY_PROBE_SPEED 10000

// Feedrate (mm/min) for the first approach when double-probing (MULTIPLE_PROBING == 2)
#define Z_PROBE_SPEED_FAST (8*60)

// Feedrate (mm/min) for the "accurate" probe of each point
#define Z_PROBE_SPEED_SLOW (3*60)

#define Z_SAFE_HOMING

#if ENABLED(Z_SAFE_HOMING)
  #define Z_SAFE_HOMING_X_POINT (((X_BED_SIZE) / 2) + 1)    // X point for Z homing
  #define Z_SAFE_HOMING_Y_POINT (((Y_BED_SIZE) / 2) + 2)    // Y point for Z homing
#endif

// Homing speeds (mm/min)
#define HOMING_FEEDRATE_MM_M { (60*60), (60*60), (40*60) }

// Preheat Constants
#define PREHEAT_1_LABEL       "Warmup"
#define PREHEAT_1_TEMP_HOTEND 170
#define PREHEAT_1_TEMP_BED     60
#define PREHEAT_1_FAN_SPEED   255 // Value from 0 to 255

#define PREHEAT_2_LABEL       "PLA"
#define PREHEAT_2_TEMP_HOTEND 193
#define PREHEAT_2_TEMP_BED     60
#define PREHEAT_2_FAN_SPEED   255 // Value from 0 to 255

#define PREHEAT_3_LABEL       "ABS"
#define PREHEAT_3_TEMP_HOTEND 240
#define PREHEAT_3_TEMP_BED     75
#define PREHEAT_3_FAN_SPEED   255 // Value from 0 to 255

#define PREHEAT_4_LABEL       "PETG"
#define PREHEAT_4_TEMP_HOTEND 230
#define PREHEAT_4_TEMP_BED     75
#define PREHEAT_4_FAN_SPEED   255 // Value from 0 to 255
