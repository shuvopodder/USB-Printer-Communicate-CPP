#include <Windows.h>
#include <SetupAPI.h>
#include "Header.h"
#include <iostream>

GUID GUID_DEVINTERFACE_USB_PRINT = { 0x28d78fad, 0x5a12, 0x11D1, 0xae, 0x5b, 0x00, 0x00, 0xf8, 0x03, 0xa8, 0xc2 };

int main()
{
	HDEVINFO DeviceInfoSet;
	GUID InterfaceClassGuid = GUID_DEVINTERFACE_USB_PRINT;
	DWORD MemberIndex = 0;// deviceCount = 0;
	DWORD size;
	SP_DEVICE_INTERFACE_DATA devInterfaceData;


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
	
	
	//std::cout << "Hello, World!" << std::endl;
}