// my_driver.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "ntddk.h"
#include "MyDriverMessages.h"

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath);
NTSTATUS CreateMyDriver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP);
NTSTATUS ReadMyDiver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP);
NTSTATUS WriteMyDriver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP);

NTSTATUS ShutdownMyDriver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP);
//NTSTATUS CleanupMyDriver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP);
NTSTATUS IOCtlMyDriver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP);
VOID MyDriverUnload(IN PDRIVER_OBJECT DriverObject);
BOOLEAN GetMessage(IN NTSTATUS ErrorCode, IN PVOID IoObject, IN PIRP IRP);

#ifdef ALLOC_PRAGMA
#pragma alloc_text(page, GetMessage)

#endif

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	UNICODE_STRING nameString, linkString;
	PDEVICE_OBJECT deviceObject;
	NTSTATUS status;

	GetMessage(MSG_DRIVER_ENTRY, DriverObject, NULL);
	RtlInitUnicodeString(&nameString, L"\\Device\\MyDriver");
	status = IoCreateDevice(DriverObject, sizeof(65533), &nameString, 0, 0, FALSE, &deviceObject);

	if (!NT_SUCCESS(status)) return status;
	deviceObject->Flags |= DO_DIRECT_IO;
	deviceObject->Flags |= ~DO_DEVICE_INITIALIZING;

	RtlInitUnicodeString(&linkString, L"\\DosDevices\\MyDriver");
	status = IoCreateSymbolicLink(&linkString, &nameString);

	if (!NT_SUCCESS(status))
	{
		IoDeleteDevice(DriverObject->DeviceObject);
		return status;
	}

	DriverObject->MajorFunction[IRP_MJ_CREATE] = CreateMyDriver;
	DriverObject->MajorFunction[IRP_MJ_READ] = ReadMyDiver;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = WriteMyDriver;
	DriverObject->MajorFunction[IRP_MJ_SHUTDOWN] = ShutdownMyDriver;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IOCtlMyDriver;
	return STATUS_SUCCESS;



}
NTSTATUS CreateMyDriver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP)
{
	GetMessage(MSG_CREATE, DeviceObject, NULL);
	return STATUS_SUCCESS;
}

NTSTATUS ReadMyDiver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP)
{
	GetMessage(MSG_READ, DeviceObject, NULL);
	return STATUS_SUCCESS;
}

NTSTATUS WriteMyDriver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP)
{
	GetMessage(MSG_WRITE, DeviceObject, NULL);
	return STATUS_SUCCESS;
}

NTSTATUS ShutdownMyDriver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP)
{
	GetMessage(MSG_SHUTDOWN, DeviceObject, NULL);
	IoCompleteRequest(IRP, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}
/*NTSTATUS CleanupMyDriver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP)
{
	
}*/
NTSTATUS IOCtlMyDriver(IN PDEVICE_OBJECT DeviceObject, IN PIRP IRP)
{
	GetMessage(MSG_IOCTL, DeviceObject, NULL);
	IoCompleteRequest(IRP, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}
VOID MyDriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING linkString;
	GetMessage(MSG_DRIVERUNLOAD, DriverObject, NULL);

	RtlInitUnicodeString(&linkString, L"\\Device\\MyDriver");
	IoDeleteSymbolicLink(&linkString);
	IoDeleteDevice(DriverObject->DeviceObject);
}
BOOLEAN GetMessage(IN NTSTATUS ErrorCode, IN PVOID IoObject, IN PIRP IRP)
{
	PIO_ERROR_LOG_PACKET Log_Packet;
	PIO_STACK_LOCATION IrpStackLocation;
	PWCHAR pInsertString;
	STRING AnsiInsertSring;
	UNICODE_STRING UniInsertString;
	UCHAR SizeOfPacket;
	SizeOfPacket = sizeof(IO_ERROR_LOG_PACKET);
	Log_Packet = IoAllocateErrorLogEntry(IoObject, SizeOfPacket);

	if (Log_Packet == NULL) return FALSE;

	Log_Packet -> ErrorCode = ErrorCode;
	Log_Packet -> UniqueErrorValue = 0;
	Log_Packet -> RetryCount = 0;
	Log_Packet -> SequenceNumber = 0;
	Log_Packet -> IoControlCode = 0;
	Log_Packet -> DumpDataSize = 0;

	if(IRP != NULL)
	{
		IrpStackLocation = IoGetCurrentIrpStackLocation(IRP);
		Log_Packet -> MajorFunctionCode = IrpStackLocation -> MajorFunction;
		Log_Packet -> FinalStatus = IRP->IoStatus.Status;
	}
	else
	{
		Log_Packet->MajorFunctionCode = 0;
		Log_Packet->FinalStatus = 0;
	}
	IoWriteErrorLogEntry(Log_Packet);

	return TRUE;
}



// int _tmain(int argc, _TCHAR* argv[])
// {
// 	return 0;
// }

