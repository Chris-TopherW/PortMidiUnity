#include "PortMidiUnity.h"

#define true 1;
#define false 0;

#ifndef bool
typedef _Bool bool;
#endif

int32_t latency = 1;
PmStream * midi;
PmEvent midiOutputBuf[256];
int buffWritePos = 0;
int buffReadPos = 0;
PmTimestamp timestamp;
int deviceNum = -1;
bool ready = false;

int main_test_output() {
	TIME_START;

	for (int i = 0; i < Pm_CountDevices; i++)
	{
		const PmDeviceInfo* info = Pm_GetDeviceInfo(i);
		if(info == NULL)
		{
			;
		}
		else if (strcmp(info->name, "loopMIDI Port") == 0)
		{
			deviceNum = i;
		}
	}

	Pm_OpenOutput(&midi,
		deviceNum,
		DRIVER_INFO,
		OUTPUT_BUFFER_SIZE,
		(latency == 0 ? NULL : TIME_PROC),
		(latency == 0 ? NULL : TIME_INFO),
		latency);
	ready = false;
	return deviceNum;
}

void midiEvent(int status, int mess1, int mess2, int delay)
{
	PmEvent buffer2[1];
	timestamp = TIME_PROC(TIME_INFO);
	buffer2[0].timestamp = timestamp + delay;
	buffer2[0].message = Pm_Message(status, mess1, mess2);
	Pm_Write(midi, buffer2, 1);
}

int getNumDevices()
{
	if (ready)
		return Pm_CountDevices;
	else
		return 0;
}

char* printOutputDevice(int index)
{

	const PmDeviceInfo* info = Pm_GetDeviceInfo(index);
	if (info == NULL)
	{
		return "Error: no device info";
	}
	else 
	{
		return info->name;
	}
}

void shutdown()
{
	Pm_Close(midi);
}
