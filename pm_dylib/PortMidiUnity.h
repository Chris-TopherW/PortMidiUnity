#include "portmidi.h"
#include "porttime.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

#define INPUT_BUFFER_SIZE 100
#define OUTPUT_BUFFER_SIZE 0
#define DRIVER_INFO NULL
#define TIME_PROC ((int32_t (*)(void *)) Pt_Time)
#define TIME_INFO NULL
#define TIME_START Pt_Start(1, 0, 0) /* timer started w/millisecond accuracy */

#define STRING_MAX 80 /* used for console input */

PMEXPORT int main_test_output(int p_deviceNum);
PMEXPORT void midiEvent(int status, int mess1, int mess2, int delay);
PMEXPORT char* printOutputDevice(int index);
PMEXPORT int getNumDevices();
PMEXPORT void shutdown();
