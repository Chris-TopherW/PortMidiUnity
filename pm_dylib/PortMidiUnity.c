#include "PortMidiUnity.h"

int32_t latency = 1;
PmStream * midi;
int chord[] = { 60, 67, 76, 83, 90 };
PmTimestamp timestamp;
int deviceNum = -1;

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
	return deviceNum;
}

void playNote(int mess1, int mess2, int delay, int length)
{
	PmEvent buffer2[2];
	timestamp = TIME_PROC(TIME_INFO);
	buffer2[0].timestamp = timestamp + delay;
	buffer2[0].message = Pm_Message(0x90, mess1, mess2);
	buffer2[1].timestamp = timestamp + delay + length;
	buffer2[1].message = Pm_Message(0x80, mess1, mess2);
	Pm_Write(midi, buffer2, 2);
}

char* printOutputDevices()
{
	//char allDeviceInfo[100];
	char name[10];
	strcpy(name, "Name");
	
	//for (int i = 0; i < Pm_CountDevices(); i++) {
	//	char* deflt;
	//	const PmDeviceInfo* info = Pm_GetDeviceInfo(i);
	//	deflt = info->name;
	//	strcat(allDeviceInfo, deflt);
	//}
	return name;
}

void shutdown()
{
	Pm_Close(midi);
}
