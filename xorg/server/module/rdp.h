/*
Copyright 2005-2013 Jay Sorg

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef _RDP_H
#define _RDP_H

#include <xorg-server.h>
#include <scrnintstr.h>
#include <gcstruct.h>
#include <mipointer.h>
#include <randrstr.h>

#include "rdpPri.h"

#define PixelDPI 100
#define PixelToMM(_size) (((_size) * 254 + (PixelDPI) * 5) / ((PixelDPI) * 10))

#define RDPMIN(_val1, _val2) ((_val1) < (_val2) ? (_val1) : (_val2))
#define RDPMAX(_val1, _val2) ((_val1) < (_val2) ? (_val2) : (_val1))
#define RDPCLAMP(_val, _lo, _hi) \
  (_val) < (_lo) ? (_lo) : (_val) > (_hi) ? (_hi) : (_val)

/* defined in rdpClientCon.h */
typedef struct _rdpClientCon rdpClientCon;

struct _rdpPointer
{
    int cursor_x;
    int cursor_y;
    int old_button_mask;
    int button_mask;
    DeviceIntPtr device;
};
typedef struct _rdpPointer rdpPointer;

struct _rdpKeyboard
{
    int pause_spe;
    int ctrl_down;
    int alt_down;
    int shift_down;
    int tab_down;
    /* this is toggled every time num lock key is released, not like the
       above *_down vars */
    int scroll_lock_down;
    DeviceIntPtr device;
};
typedef struct _rdpKeyboard rdpKeyboard;

/* move this to common header */
struct _rdpRec
{
    int width;
    int height;
    int depth;
    int paddedWidthInBytes;
    int sizeInBytes;
    int num_modes;
    int bitsPerPixel;
    char *pfbMemory;
    ScreenPtr pScreen;
    rdpDevPrivateKey privateKeyRecGC;
    rdpDevPrivateKey privateKeyRecPixmap;

    CopyWindowProcPtr CopyWindow;
    CreateGCProcPtr CreateGC;
    CreatePixmapProcPtr CreatePixmap;
    DestroyPixmapProcPtr DestroyPixmap;
    ModifyPixmapHeaderProcPtr ModifyPixmapHeader;
    CloseScreenProcPtr CloseScreen;
    CompositeProcPtr Composite;
    GlyphsProcPtr Glyphs;

    /* keyboard and mouse */
    miPointerScreenFuncPtr pCursorFuncs;
    /* mouse */
    rdpPointer pointer;
    /* keyboard */
    rdpKeyboard keyboard;

    /* RandR */
    RRSetConfigProcPtr rrSetConfig;
    RRGetInfoProcPtr rrGetInfo;
    RRScreenSetSizeProcPtr rrScreenSetSize;
    RRCrtcSetProcPtr rrCrtcSet;
    RRCrtcSetGammaProcPtr rrCrtcSetGamma;
    RRCrtcGetGammaProcPtr rrCrtcGetGamma;
    RROutputSetPropertyProcPtr rrOutputSetProperty;
    RROutputValidateModeProcPtr rrOutputValidateMode;
    RRModeDestroyProcPtr rrModeDestroy;
    RROutputGetPropertyProcPtr rrOutputGetProperty;
    RRGetPanningProcPtr rrGetPanning;
    RRSetPanningProcPtr rrSetPanning;

    int listen_sck;
    char uds_data[256];
    rdpClientCon *clientConHead;
    rdpClientCon *clientConTail;
};
typedef struct _rdpRec rdpRec;
typedef struct _rdpRec * rdpPtr;
#define XRDPPTR(_p) ((rdpPtr)((_p)->driverPrivate))

struct _rdpGCRec
{
    GCFuncs *funcs;
    GCOps *ops;
};
typedef struct _rdpGCRec rdpGCRec;
typedef struct _rdpGCRec * rdpGCPtr;

struct _rdpPixmapRec
{
    int i1;
};
typedef struct _rdpPixmapRec rdpPixmapRec;
typedef struct _rdpPixmapRec * rdpPixmapPtr;

#endif
