//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: MSG_DRIVER_ENTRY
//
// MessageText:
//
// Driver_Entry      
//
#define MSG_DRIVER_ENTRY                 0x40000001L

//
// MessageId: MSG_CREATE
//
// MessageText:
//
// Create
//
#define MSG_CREATE                       0x40000002L

//
// MessageId: MSG_READ
//
// MessageText:
//
// Read
//
#define MSG_READ                         0x40000003L

//
// MessageId: MSG_WRITE
//
// MessageText:
//
// Write
//
#define MSG_WRITE                        0x40000004L

//
// MessageId: MSG_SHUTDOWN
//
// MessageText:
//
// Shutdown
//
#define MSG_SHUTDOWN                     0x40000005L

//
// MessageId: MSG_IOCTL
//
// MessageText:
//
// IOCtl
//
#define MSG_IOCTL                        0x40000006L

//
// MessageId: MSG_DRIVERUNLOAD
//
// MessageText:
//
// UnloadDriver      
// 
// 
//
#define MSG_DRIVERUNLOAD                 0x40000007L

