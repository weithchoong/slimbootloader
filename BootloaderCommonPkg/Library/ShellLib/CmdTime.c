// /** @file
//   Shell command `time` to print or modify the OS boot option list.

//   Copyright (c) 2017 - 2021, Intel Corporation. All rights reserved.<BR>
//   SPDX-License-Identifier: BSD-2-Clause-Patent

// **/

// #include <Library/ShellLib.h>
// #include <Library/DebugLib.h>
// #include <Uefi.h>
// #include <Library/UefiLib.h>
// #include <Library/UefiBootServicesTableLib.h>
// #include <Library/UefiRuntimeServicesTableLib.h>

// /**
//   Print or modify the OS boot option list.

//   @param[in]  Shell        shell instance
//   @param[in]  Argc         number of command line arguments
//   @param[in]  Argv         command line arguments

//   @retval EFI_SUCCESS

// **/
// STATIC
// EFI_STATUS
// EFIAPI
// ShellCommandTimeFunc (
//   IN SHELL  *Shell,
//   IN UINTN   Argc,
//   IN CHAR16 *Argv[]
//   );

// CONST SHELL_COMMAND ShellCommandTime = {
//   L"time",
//   L"Display current time",
//   &ShellCommandTimeFunc
// };
// /**
//   display current system time

//   @param[in]  Shell        shell instance
//   @param[in]  Argc         number of command line arguments
//   @param[in]  Argv         command line arguments

//   @retval EFI_SUCCESS

// **/
// STATIC
// EFI_STATUS
// EFIAPI
// ShellCommandTimeFunc (
//   IN SHELL  *Shell,
//   IN UINTN   Argc,
//   IN CHAR16 *Argv[]


//   )
// {
// //     // create timer event
// //     EFI_EVENT TimerEvent;
// //     EFI_STATUS Status;
// //     EFI_TIME Time;
    
// //     // Create a periodic timer event
// //   Status = gBS->CreateEvent(
// //     EVT_TIMER | EVT_NOTIFY_SIGNAL,
// //     TPL_CALLBACK,
// //     NULL,
// //     NULL,
// //     &TimerEvent
// //   );
// //   if (EFI_ERROR(Status)) {
// //     ShellPrint(L"Failed to create timer event: %u\n", Status);
// //     return Status;
// //   }

// //   // Set timer to fire every 1 second (1e7 = 10,000,000 * 100ns = 1s)
// //   Status = gBS->SetTimer(
// //     TimerEvent,
// //     TimerPeriodic,
// //     10000000
// //   );
// //   if (EFI_ERROR(Status)) {
// //     ShellPrint(L"Failed to set timer: %u\n", Status);
// //     gBS->CloseEvent(TimerEvent);
// //     return Status;
// //   }


// //    Print(L"Live Clock (press Ctrl+C to exit):\n");

// //   // Loop forever, printing time every second
// //   while (TRUE) {
// //     UINTN Index;
// //     Status = gBS->WaitForEvent(1, &TimerEvent, &Index);
// //     if (EFI_ERROR(Status)) {
// //       Print(L"WaitForEvent failed: %u\n", Status);
// //       break;
// //     }

// //     Status = gRT->GetTime(&Time, NULL);
// //     if (!EFI_ERROR(Status)) {
// //       Print(L"%04u/%02u/%02u %02u:%02u:%02u\r",
// //         Time.Year, Time.Month, Time.Day,
// //         Time.Hour, Time.Minute, Time.Second);
// //     } else {
// //       Print(L"GetTime failed: %u\n", Status);
// //     }
// //   }

// //   gBS->CloseEvent(TimerEvent);

//     return EFI_SUCCESS;
// }