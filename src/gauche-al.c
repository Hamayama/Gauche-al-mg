/*
 * gauche-al.c
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

#include "gauche-al.h"

void Scm_finalize_PCMData(ScmObj obj, void *data)
{
    ScmPCMData *z = SCM_PCM_DATA(obj);
    if (z->data) {
        /* don't use deprecated function */
        /* alutUnloadWAV(z->format, z->data, z->size, z->freq); */
        free(z->data);
        z->data = NULL;
        z->size = 0;
    }
}

ScmObj Scm_MakePCMData(ALenum format, void *data, ALsizei size, ALsizei freq, ALboolean loop)
{
    if (data == NULL) {
        return SCM_FALSE;
    }
    ScmPCMData *z = SCM_NEW(ScmPCMData);
    SCM_SET_CLASS(z, SCM_CLASS_PCM_DATA);
    Scm_RegisterFinalizer(SCM_OBJ(z), Scm_finalize_PCMData, NULL);
    z->format = format;
    z->data = data;
    z->size = size;
    z->freq = freq;
    z->loop = loop;

    SCM_RETURN(SCM_OBJ(z));
}
    
ScmObj Scm_MakeALCcontext(ALCcontext *data)
{
    if (data == NULL) {
        return SCM_FALSE;
    }
    ScmALCcontext *z = SCM_NEW(ScmALCcontext);
    SCM_SET_CLASS(z, SCM_CLASS_ALC_CONTEXT);
    z->data = data;

    SCM_RETURN(SCM_OBJ(z));
}

static void Scm_finalize_ALCdevice(ScmObj obj, void *data)
{
    ScmALCdevice *z = SCM_ALC_DEVICE(obj);
    if (z->data) {
        alcCloseDevice(z->data);
        z->data = NULL;
    }
}

ScmObj Scm_MakeALCdevice(ALCdevice *data)
{
    if (data == NULL) {
        return SCM_FALSE;
    }
    ScmALCdevice *z = SCM_NEW(ScmALCdevice);
    SCM_SET_CLASS(z, SCM_CLASS_ALC_DEVICE);
    Scm_RegisterFinalizer(SCM_OBJ(z), Scm_finalize_ALCdevice, NULL);
    z->data = data;

    SCM_RETURN(SCM_OBJ(z));
}

int Scm_ALStateInfoSize(int state)
{
    switch (state) {
    case AL_DOPPLER_FACTOR:
    case AL_DOPPLER_VELOCITY:
    case AL_DISTANCE_MODEL:
        return 1;
    }
    return -1;
}
 
int Scm_ALCStateInfoSize(ALCdevice *device, int token)
{
    switch (token) {
    case ALC_MAJOR_VERSION:
    case ALC_MINOR_VERSION:
    case ALC_ATTRIBUTES_SIZE:
        return 1;
    case ALC_ALL_ATTRIBUTES:
        {
            ALCint v;
            alcGetIntegerv(device, token, 1, &v);
            return v;
        }
    }
    return -1;
}
 
/*
 * Module initialization function.
 * This is called when esound.so is dynamically loaded into gosh.
 */
extern void Scm_Init_al_lib(ScmModule*);
extern void Scm_Init_alc_lib(ScmModule*);
extern void Scm_Init_alut_lib(ScmModule*);

ScmObj Scm_Init_al(void)
{
    ScmModule *mod;

    /* Register this DSO to Gauche */
    SCM_INIT_EXTENSION(al);

    /* Create "al" module if it doesn't exist yet. */
    mod = SCM_MODULE(SCM_FIND_MODULE("al", TRUE));

    /* Register stub-generated procedures inside "al" module */
    Scm_Init_al_lib(mod);
    Scm_Init_alc_lib(mod);
    Scm_Init_alut_lib(mod);
}

