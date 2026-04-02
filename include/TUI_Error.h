#ifndef __TUI_ERROR_H__
#define __TUI_ERROR_H__
#pragma once



#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>



typedef enum TUI_ErrorType {
        TUI_ErrType_Undefined = 0,
        TUI_ErrType_Other = 1,

        TUI_ErrType_SystemError,
        TUI_ErrType_LibraryError,
        TUI_ErrType_UserError,
        TUI_ErrType_AllocationError,

        TUI_ErrType_TUIerror,

        TUI_ErrType_WrongInput,
        TUI_ErrType_WrongFormat,
        TUI_ErrType_WrongFile,
} TUI_ErrorType;



typedef struct TUI_Error {
        TUI_ErrorType type;
        
        char *message;
        size_t size;

        bool is_static;
} TUI_Error;



int TUI_SetErrorV(TUI_ErrorType _Type, char *_Format, va_list _Args);

int TUI_SetError(TUI_ErrorType _Code, char *_Format, ...);

TUI_Error TUI_GetError();






#endif // __TUI_ERROR_H__
