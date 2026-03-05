#include "TUI_Error.h"


#define __TUI_ERROR_MSG_BUF_SIZE (256)

TUI_Error *__GetErrorBuffer() {
        static TUI_Error error_buffer = {
                TUI_ErrType_Undefined,
                NULL,
                0,
                0
        };

        return &error_buffer;
}

char *__GetStaticMessageBuffer() {
        static char buffer[__TUI_ERROR_MSG_BUF_SIZE];

        return buffer;
}



int TUI_SetErrorV(TUI_ErrorType _Type, char *_Format, va_list _Argptr) {
        if ( _Format == NULL ) {
                return -1;
        }

        int result;
        va_list argptr2;

        TUI_Error *error = __GetErrorBuffer();
        error->type = _Type;
        
        va_copy(argptr2, _Argptr);
        result = vsnprintf(error->message, error->size, _Format, argptr2);
        va_end(argptr2);
        
        if ( (size_t)result < error->size || result == -1 ) {
                return result;
        }


        va_copy(argptr2, _Argptr);
        
        if ( !error->is_static && error->message != NULL ) {
                free(error->message);
        }
        
        error->size = (size_t)result + 1;
        error->message = malloc(error->size);
        
        if ( error->message == NULL ) {
                error->message = __GetStaticMessageBuffer();
                error->size = __TUI_ERROR_MSG_BUF_SIZE;
                error->is_static = 1;
        } else {
                error->is_static = 0;
        }
        
        result = vsnprintf(error->message, error->size, _Format, argptr2);
        va_end(argptr2);

        return result;
}



int TUI_SetError(TUI_ErrorType _Type, char *_Format, ...) {
        va_list argptr;
        int result;

        va_start(argptr, _Format);
        result = TUI_SetErrorV(_Type, _Format, argptr);
        va_end(argptr);

        return result;
}



TUI_Error TUI_GetError() {
        return *__GetErrorBuffer();
}


char *TUI_GetErrorMsg() {
        return __GetErrorBuffer()->message;
}