;------------------------------------------------------------------------------
;
; Copyright (c) 2016 - 2020, Intel Corporation. All rights reserved.<BR>
; SPDX-License-Identifier: BSD-2-Clause-Patent
;
;
; Module Name:
;
;  SecEntry.nasm
;
; Abstract:
;
;  This is the code that goes from real-mode to protected mode.
;  It consumes the reset vector.
;
;------------------------------------------------------------------------------

SECTION .text

extern  ASM_PFX(SecStartup)
extern  ASM_PFX(TempRamInitParams)
extern  ASM_PFX(PcdGet32(PcdStage1StackSize))
extern  ASM_PFX(PcdGet32(PcdStage1DataSize))
extern  ASM_PFX(PcdGet32(PcdStage1StackBaseOffset))

%macro POST_CODE 1
    mov     ax, %1
    out     80h, ax
%endmacro

; Add delay macro for debugging visibility
; This creates a simple CPU loop to slow down execution
%macro DEBUG_DELAY 1
    push    rax
    push    rcx
    mov     rcx, %1              ; Load delay count into RCX
delay_loop_%1:
    dec     rcx                  ; Decrement counter
    jnz     delay_loop_%1        ; Jump if not zero (continue loop)
    pop     rcx                  ; Restore original RCX
    pop     rax                  ; Restore original RAX
%endmacro

global  ASM_PFX(_ModuleEntryPoint)
ASM_PFX(_ModuleEntryPoint):
        movd    mm0, eax

        ; POST Code: Entry into SecEntry.nasm
        POST_CODE 00a0h
        DEBUG_DELAY 0100000h     ; ~1 second delay (16.7 million cycles)

        ;
        ; RDI: time stamp
        ;

        ;
        ; Add a dummy reference to TempRamInitParams to prevent
        ; compiler from removing this symbol
        ;
        mov     rax, ASM_PFX(TempRamInitParams)

        ;
        ; Setup stack
        ; ECX: Bootloader stack base
        ; EDX: Bootloader stack top
        ;
        mov     rax, ASM_PFX(PcdGet32(PcdStage1StackBaseOffset))
        mov     eax, dword [rax]
        mov     rsp, rax
        add     rsp, rcx
        mov     rax, ASM_PFX(PcdGet32(PcdStage1StackSize))
        mov     eax, dword [rax]
        add     rsp, rax

        ; POST Code: Stack setup complete
        POST_CODE 00a1h
        DEBUG_DELAY 080000h      ; ~0.5 second delay (8.4 million cycles)
        
        ; POST Code: Before C code transition
        POST_CODE 00a2h


        ;
        ; Check stage1 stack base offset
        ;
        xor     rbx, rbx             ; Use EBX for Status
        mov     rax, ASM_PFX(PcdGet32(PcdStage1DataSize))
        mov     eax, dword [rax]
        add     rax, rsp
        cmp     rax, rdx
        jle     CheckStackRangeDone

        ;
        ; Error in stack range
        ;
        bts     rbx, 1               ; Set BIT1 in Status
        mov     rsp, rdx             ; Set ESP to the end

        
CheckStackRangeDone:
        ; POST Code: Stack validation start
        POST_CODE 00b0h
        
        ; Display stack base in POST codes (for debugging)
        mov     rax, rcx              ; Stack base
        shr     rax, 24               ; Get high byte
        out     80h, ax               ; Output high byte as 00 XX
        
        DEBUG_DELAY 050000h           ; ~0.2 second delay
        
        mov     rax, rcx
        shr     rax, 16
        out     80h, ax               ; Output mid-high byte as 00 XX
        
        DEBUG_DELAY 050000h           ; ~0.2 second delay
        
        ; POST Code: Stack validation complete
        POST_CODE 00b1h

        ;
        ; CpuBist error check
        ;
        movd    eax, mm0
        emms                         ; Exit MMX Instruction
        cmp     eax, 0
        jz      CheckStatusDone

        ;
        ; Error in CpuBist
        ;
        bts     rbx, 0               ; Set BIT0 in Status

CheckStatusDone:
        ;
        ; Setup HOB
        ; This structure has to match the layout of STAGE1A_ASM_PARAM
        ;
        push    rbx                  ; Status
        push    rdi                  ; TimeStamp[0] [63:0]
        shl     rdx, 32              ; Move CarTop to high 32bit
        add     rdx, rcx             ; Add back CarBase
        push    rdx
        mov     rcx, rsp             ; Argument 1

        sub     rsp, 32              ; 32 bytes shadow store for x64
        and     esp, 0xfffffff0      ; Align stack to 16 bytes

        

        call    ASM_PFX(SecStartup)  ; Jump to C code
        jmp     $



        

