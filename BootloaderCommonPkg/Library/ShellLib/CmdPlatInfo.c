/** @file
  Shell command `hello` to print or modify the OS boot option list.

  Copyright (c) 2017 - 2021, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/ShellLib.h>
#include <Library/DebugLib.h>
#include <Library/BootloaderCoreLib.h> 
#include <Library/BaseMemoryLib.h>

#define PLATFORM_NAME_SIZE 8

/**
  Print or modify the OS boot option list.

  @param[in]  Shell        shell instance
  @param[in]  Argc         number of command line arguments
  @param[in]  Argv         command line arguments

  @retval EFI_SUCCESS

**/
STATIC
EFI_STATUS
EFIAPI
ShellCommandPlatInfoFunc (
  IN SHELL  *Shell,
  IN UINTN   Argc,
  IN CHAR16 *Argv[]
  );

CONST SHELL_COMMAND ShellCommandPlatInfo = {
  L"platinfo",
  L"Display platform info",
  &ShellCommandPlatInfoFunc
};
/**
  display platinfo message.

  @param[in]  Shell        shell instance
  @param[in]  Argc         number of command line arguments
  @param[in]  Argv         command line arguments

  @retval EFI_SUCCESS

**/
STATIC
EFI_STATUS
EFIAPI
ShellCommandPlatInfoFunc (
  IN SHELL  *Shell,
  IN UINTN   Argc, // start from 1
  IN CHAR16 *Argv[] // start from 0
  )
{
    
    UINT8 PlatformName[PLATFORM_NAME_SIZE + 1];
    //Get Platform ID and Boot Mode
    

    CopyMem (PlatformName, GetPlatformName (), PLATFORM_NAME_SIZE);
    PlatformName[PLATFORM_NAME_SIZE] = 0;
    // using shellprint
    ShellPrint(L"\n=================PLATFORM INFO=================\n");
    ShellPrint(L"PlatformName       : %a\n", PlatformName);
    ShellPrint(L"Board ID           : 0x%02X\n", GetPlatformId());
    ShellPrint(L"Boot Mode          : %d\n", GetBootMode());
    ShellPrint(L"Boot Partition     : BP%d\n", GetCurrentBootPartition());

    // using debug
    // DEBUG ((DEBUG_INFO, "PlatformName: %a\n", PlatformName));
    // DEBUG ((DEBUG_INIT, "BOOT: BP%d \nMODE: %d\nBoardID: 0x%02X\n",
    //       GetCurrentBootPartition (), GetBootMode (), GetPlatformId ()));


    return EFI_SUCCESS;
}