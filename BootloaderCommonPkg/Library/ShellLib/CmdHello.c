/** @file
  Shell command `hello` to print or modify the OS boot option list.

  Copyright (c) 2017 - 2021, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/ShellLib.h>
#include <Library/DebugLib.h>


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
ShellCommandHelloFunc (
  IN SHELL  *Shell,
  IN UINTN   Argc,
  IN CHAR16 *Argv[]
  );

CONST SHELL_COMMAND ShellCommandHello = {
  L"hello",
  L"Display hello message",
  &ShellCommandHelloFunc
};
/**
  display hello message.

  @param[in]  Shell        shell instance
  @param[in]  Argc         number of command line arguments
  @param[in]  Argv         command line arguments

  @retval EFI_SUCCESS

**/
STATIC
EFI_STATUS
EFIAPI
ShellCommandHelloFunc (
  IN SHELL  *Shell,
  IN UINTN   Argc, // start from 1
  IN CHAR16 *Argv[] // start from 0
  )
{
    CHAR16 Name1[100];
    

    // using if else
    // if(Argc == 2){
    //     ShellPrint (L"Hello %s from SBL Shell!\n", Argv[1]); // hello jane
    //     ShellPrint (L"Total arguments: %d\n", Argc);
    // }
    // else if(Argc == 3){
    //     ShellPrint (L"Hello %s and %s from SBL Shell!\n", Argv[1], Argv[2]); // hello jane bob
    //     ShellPrint (L"Total arguments: %d\n", Argc);
    // }
    // else{
    //     ShellPrint (L"Hello World from SBL Shell!\n");
    //     ShellPrint (L"Total arguments: %d\n", Argc);
    // }
    // // using for loop
    // for(UINT16 i=0;i<Argc;i++){
    //     if(Argv[2] == '-c'){
            
    //     }
    //     ShellPrint (L"Hello %s from SBL Shell!\n", Argv[i]);
    // }
    // switch

    // option 1: uppercase first letter (-u)
    if (StrCmp(Argv[1], L"-u") == 0){
        StrCpyS(Name1, sizeof(Name1) / sizeof(CHAR16), Argv[2]);
        // Uppercase the first letter
        if (Name1[0] >= L'a' && Name1[0] <= L'z') {
            Name1[0] = Name1[0] - (L'a' - L'A');
        }

        ShellPrint(L"Hello %s!\n", Name1);
    }
    // option 2: count times to repeat (-c)
    else if(StrCmp(Argv[1], L"-c") == 0){
        UINT16 count = (UINT16)StrDecimalToUint64(Argv[2]); // convert string to uint64
        for (UINT16 i = 0; i < count; i++){
            ShellPrint(L"hello %s \n", Argv[3]);
        }
    }
    

  return EFI_SUCCESS;
}