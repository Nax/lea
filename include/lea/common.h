/*
 * Copyright (c) 2019, Maxime Bacoux
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LEA_COMMON_H
#define LEA_COMMON_H 1

#if defined(__cplusplus)
# define LEA_API_EXTERN extern "C"
#else
# define LEA_API_EXTERN
#endif

#if (defined(WIN32) || defined(_WIN32)) && !(defined(LEA_STATIC))
# if defined(LEA_DLL)
#  define LEA_API_DECL __declspec(dllexport)
# else
#  define LEA_API_DECL __declspec(dllimport)
# endif
#else
# define LEA_API_DECL
#endif

#define LEA_API LEA_API_EXTERN LEA_API_DECL

typedef struct LeaState_ LeaState;

typedef enum {
    LEA_OK = 0,
    LEA_ERROR_OUT_OF_MEMORY = 1,
} LeaError;

#endif
