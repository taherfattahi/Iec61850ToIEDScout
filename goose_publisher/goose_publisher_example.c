/*
 * goose_publisher_example.c
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "goose_publisher.h"


void goosePublisher(char* interface, uint8_t dsMacList[6], uint16_t appId, uint16_t vlanId, uint8_t vlanPriority,
	char* goCbRef, uint32_t confRev, bool simulation, char* goID, char* dataSetRef, int numDatSetEntries) {

	LinkedList dataSetValues = LinkedList_create();
	//MmsValue* optFlds = MmsValue_newBitString(2); // Intermidiate
	//MmsValue_setBitStringFromInteger(optFlds, 0); // 20

	MmsValue* optFlds = MmsValue_newBitString(2); // close
	MmsValue_setBitStringFromInteger(optFlds, 1);

	//MmsValue* optFlds = MmsValue_newBitString(2); // Open
	//MmsValue_setBitStringFromInteger(optFlds, 2);

	//MmsValue_setBitStringBit(optFlds, 30, true);
	//MmsValue_setAllBitStringBits(optFlds);

	//MmsValue* optFlds = MmsValue_newBitString(2); // Bad State
	//MmsValue_setBitStringFromInteger(optFlds, 3); //15


	MmsValue* optFlds1 = MmsValue_newBitString(13); // Open
	MmsValue_setBitStringFromInteger(optFlds1, 49152);

	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, optFlds);
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBoolean(false));
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBoolean(false));

	CommParameters gooseCommParameters;

	gooseCommParameters.appId = appId;
	size_t sizeOfDsMacList = sizeof(dsMacList) / sizeof(dsMacList[0]);
	for (int i = 0; i < sizeOfDsMacList; i++) {
		gooseCommParameters.dstAddress[i] = dsMacList[i];
	}
	gooseCommParameters.vlanId = vlanId;
	gooseCommParameters.vlanPriority = vlanPriority;


	GoosePublisher publisher = GoosePublisher_create(&gooseCommParameters, interface);

	if (publisher) {
		GoosePublisher_setGoCbRef(publisher, goCbRef);
		GoosePublisher_setConfRev(publisher, confRev);
		GoosePublisher_setSimulation(publisher, simulation);
		GoosePublisher_setGoID(publisher, goID);
		GoosePublisher_setDataSetRef(publisher, dataSetRef);
		//int i = 0;

		//for (i = 0; i < 3; i++) {
			//Thread_sleep(1000);

		if (GoosePublisher_publish(publisher, dataSetValues) == -1) {
			printf("Error sending message!\n");
		}
		//}

		GoosePublisher_destroy(publisher);

	}
	else {
		printf("Failed to create GOOSE publisher. Reason can be that the Ethernet interface doesn't exist or root permission are required.\n");
	}

	LinkedList_destroyDeep(dataSetValues, (LinkedListValueDeleteFunction)MmsValue_delete);

}

// has to be executed as root!
int
main(int argc, char** argv)
{
	char* interface;

    if (argc > 1)
       interface = argv[1];
    else
       interface = "11";

	//char* numDatSetEntriesChar = argv[2];
	//int numDatSetEntries = strtol(numDatSetEntriesChar, NULL, 10);

	//uint8_t dsMacList[6] = {0x10, 0x7b, 0x44, 0xd8, 0xd6, 0xb3};
	//goosePublisher("2", dsMacList, 24, 0, 4, "C07_BCU3CTRL/LLN0$GO$Control_DataSet1", 1, true, "26", "C07_BCU3CTRL/LLN0$DataSet1", numDatSetEntries);

    printf("Using interface %s\n", interface);

	LinkedList dataSetValues = LinkedList_create();

	//MmsValue* optFlds = MmsValue_newBitString(2); // Intermidiate
	//MmsValue_setBitStringFromInteger(optFlds, 0); // 20

	//MmsValue*  optFlds = MmsValue_newBitString(2); // close
	//MmsValue_setBitStringFromInteger(optFlds, 1);
	
	MmsValue* optFlds = MmsValue_newBitString(2); // Open
	MmsValue_setBitStringFromInteger(optFlds, 2);
	//MmsValue_setBitStringBit(optFlds, 30, true);
	//MmsValue_setAllBitStringBits(optFlds);

	//MmsValue* optFlds = MmsValue_newBitString(2); // Bad State
	//MmsValue_setBitStringFromInteger(optFlds, 3); //15

	//MmsValue* optFlds1 = MmsValue_newBitString(13); // Open
	//MmsValue_setBitStringFromInteger(optFlds1, 49152);

	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, optFlds);
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBoolean(false));
	LinkedList_add(dataSetValues, MmsValue_newBitString(16));
	LinkedList_add(dataSetValues, MmsValue_newBoolean(false));

	//LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(1234));
	//LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
	//LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(5678));

	CommParameters gooseCommParameters;

	gooseCommParameters.appId = 24;
	gooseCommParameters.dstAddress[0] = 0x04;
	gooseCommParameters.dstAddress[1] = 0x0e;
	gooseCommParameters.dstAddress[2] = 0x3c;
	gooseCommParameters.dstAddress[3] = 0x89;
	gooseCommParameters.dstAddress[4] = 0xc8;
	gooseCommParameters.dstAddress[5] = 0xba;
	gooseCommParameters.vlanId = 0;
	gooseCommParameters.vlanPriority = 4;

	/*
	 * Create a new GOOSE publisher instance. As the second parameter the interface
	 * name can be provided (e.g. "eth0" on a Linux system). If the second parameter
	 * is NULL the interface name as defined with CONFIG_ETHERNET_INTERFACE_ID in
	 * stack_config.h is used.
	 */

	GoosePublisher publisher = GoosePublisher_create(&gooseCommParameters, interface);

	if (publisher) {
		GoosePublisher_setGoCbRef(publisher, "C07_BCU3CTRL/LLN0$GO$Control_DataSet1");
		GoosePublisher_setConfRev(publisher, 1);
		GoosePublisher_setSimulation(publisher, true);
		GoosePublisher_setGoID(publisher, "26");
		GoosePublisher_setDataSetRef(publisher, "C07_BCU3CTRL/LLN0$DataSet1");

		int i = 0;

		//for (i = 0; i < 3; i++) {
			//Thread_sleep(1000);

		if (GoosePublisher_publish(publisher, dataSetValues) == -1) {
			printf("Error sending message!\n");
		}
		//}

		GoosePublisher_destroy(publisher);

	}
	else {
		printf("Failed to create GOOSE publisher. Reason can be that the Ethernet interface doesn't exist or root permission are required.\n");
	}

	LinkedList_destroyDeep(dataSetValues, (LinkedListValueDeleteFunction)MmsValue_delete);
	
}


