#include <Windows.h>
#include <SetupAPI.h>
#include "Header.h"
#include <iostream>

GUID GUID_DEVINTERFACE_USB_PRINT = { 0x28d78fad, 0x5a12, 0x11D1, 0xae, 0x5b, 0x00, 0x00, 0xf8, 0x03, 0xa8, 0xc2 };


#pragma warning(disable : 4996)

int main()
{
	HDEVINFO DeviceInfoSet;
	GUID InterfaceClassGuid = GUID_DEVINTERFACE_USB_PRINT;
	DWORD MemberIndex = 0;// deviceCount = 0;
	DWORD size;
	SP_DEVICE_INTERFACE_DATA devInterfaceData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA devInterfaceDetailsData;
	//PSP_DEVINFO_DATA DeviceInfoData;
	SP_DEVINFO_DATA DeviceInfoData;


	DeviceInfoSet = SetupDiGetClassDevs(
		&InterfaceClassGuid,
		NULL,
		NULL,
		DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

	if (DeviceInfoSet == INVALID_HANDLE_VALUE)
	{
		std::cout << "Error!" << std::endl;
		return 0;
	}

	devInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	if (!SetupDiEnumDeviceInterfaces(
		DeviceInfoSet,
		NULL,				//DeviceInfoData,
		&InterfaceClassGuid,//[in]  const GUID * InterfaceClassGuid,
		MemberIndex,		//[in]  DWORD  MemberIndex,
		&devInterfaceData    //[out] PSP_DEVICE_INTERFACE_DATA DeviceInterfaceData
	)) {
		std::cout << "No Printer Device Found!" << std::endl;
	}
	else {
		std::cout << "Printer Found!!" << std::endl;
	}

	while (SetupDiEnumDeviceInterfaces(DeviceInfoSet, NULL, &InterfaceClassGuid, MemberIndex, &devInterfaceData))
	{
		char devicePath[1024];

		MemberIndex++;
		size = 0;

		SetupDiGetDeviceInterfaceDetail(
			DeviceInfoSet, //[in]            HDEVINFO                           DeviceInfoSet,
			&devInterfaceData, //[in]            PSP_DEVICE_INTERFACE_DATA          DeviceInterfaceData,
			NULL, //[out, optional] PSP_DEVICE_INTERFACE_DETAIL_DATA_A DeviceInterfaceDetailData,
			NULL, //[in]            DWORD                              DeviceInterfaceDetailDataSize,
			&size, //[out, optional] PDWORD                             RequiredSize,
			NULL//[out, optional] PSP_DEVINFO_DATA                   DeviceInfoData
		);
		DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

		devInterfaceDetailsData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);

		if (devInterfaceDetailsData) {
			devInterfaceDetailsData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
			DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

			

			if (!SetupDiGetDeviceInterfaceDetail(
				DeviceInfoSet, //[in]            HDEVINFO                           DeviceInfoSet,
				&devInterfaceData, //[in]            PSP_DEVICE_INTERFACE_DATA          DeviceInterfaceData,
				devInterfaceDetailsData, //[out, optional] PSP_DEVICE_INTERFACE_DETAIL_DATA_A DeviceInterfaceDetailData,
				size, //[in]            DWORD                              DeviceInterfaceDetailDataSize,
				0, //[out, optional] PDWORD                             RequiredSize,
				&DeviceInfoData //[out, optional] PSP_DEVINFO_DATA                   DeviceInfoData
			)) {
				free(devInterfaceDetailsData);
				SetupDiDestroyDeviceInfoList(DeviceInfoSet);
				return 0;
			}
			
			std::cout << "Device Path:\t" << devInterfaceDetailsData->DevicePath << std::endl;
			strcpy(devicePath, devInterfaceDetailsData->DevicePath);


		}

	}
	
	
	//std::cout << "Hello, World!" << std::endl;
}