/*
 * gauche-al.h
 *
 *   Copyright (c) 2005 KOGURO, Naoki
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without 
 *   modification, are permitted provided that the following conditions 
 *   are met:
 *
 *   1. Redistributions of source code must retain the above copyright 
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright 
 *      notice, this list of conditions and the following disclaimer in the 
 *      documentation and/or other materials provided with the distribution.
 *   3. Neither the name of the authors nor the names of its contributors 
 *      may be used to endorse or promote products derived from this 
 *      software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
 *   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 *   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 *   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */

#if MacOSX
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <OpenAL/alut.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#endif

#include <gauche.h>
#include <gauche/extend.h>
#include <gauche/class.h>
#include <gauche/uvector.h>

#define CONST_CHAR_PTR(string) ((const char*)Scm_GetStringConst(SCM_STRING(string)))


/* PCMData */
typedef struct ScmPCMDataRec {
    SCM_HEADER;
    ALenum format;
    ALsizei size;
    ALsizei freq;
    ALboolean loop;
    ALvoid *data;
} ScmPCMData;

SCM_CLASS_DECL(Scm_PCMDataClass);
#define SCM_CLASS_PCM_DATA 		(&Scm_PCMDataClass)
#define SCM_PCM_DATA(obj) 		((ScmPCMData*)(obj))
#define SCM_PCM_DATA_P(obj)		SCM_XTYPEP(obj, SCM_CLASS_PCM_DATA)
#define SCM_PCM_DATA_FORMAT(obj)	(SCM_PCM_DATA(obj)->format)
#define SCM_PCM_DATA_FREQ(obj)	(SCM_PCM_DATA(obj)->freq)
#define SCM_PCM_DATA_DATA(obj)	(SCM_PCM_DATA(obj)->data)

extern void Scm_finalize_PCMData(ScmObj obj, void *data);
extern ScmObj Scm_MakePCMData(ALenum format, void *data, ALsizei size, ALsizei freq, ALboolean loop);

/* ALCcontext */
typedef struct ScmALCcontextRec {
    SCM_HEADER;
    ALCcontext *data;
} ScmALCcontext;

SCM_CLASS_DECL(Scm_ALCcontextClass);
#define SCM_CLASS_ALC_CONTEXT 		(&Scm_ALCcontextClass)
#define SCM_ALC_CONTEXT(obj) 		((ScmALCcontext*)(obj))
#define SCM_ALC_CONTEXT_P(obj)		SCM_XTYPEP(obj, SCM_CLASS_ALC_CONTEXT)
#define SCM_ALC_CONTEXT_DATA(obj)	(SCM_ALC_CONTEXT(obj)->data)

extern ScmObj Scm_MakeALCcontext(ALCcontext *data);

/* ALCdevice */
typedef struct ScmALCdeviceRec {
    SCM_HEADER;
    ALCdevice *data;
} ScmALCdevice;

SCM_CLASS_DECL(Scm_ALCdeviceClass);
#define SCM_CLASS_ALC_DEVICE 		(&Scm_ALCdeviceClass)
#define SCM_ALC_DEVICE(obj) 		((ScmALCdevice*)(obj))
#define SCM_ALC_DEVICE_P(obj)		SCM_XTYPEP(obj, SCM_CLASS_ALC_DEVICE)
#define SCM_ALC_DEVICE_DATA(obj)	(SCM_ALC_DEVICE(obj)->data)

extern ScmObj Scm_MakeALCdevice(ALCdevice *data);

extern int Scm_ALStateInfoSize(int state);
extern int Scm_ALCStateInfoSize(ALCdevice *device, int state);

extern void Scm_Init_allib(ScmModule *module);
