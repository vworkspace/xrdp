/**
 * FreeRDP: A Remote Desktop Protocol Server
 * freerdp wrapper
 *
 * Copyright 2011 Jay Sorg
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* include other h files */
#include "arch.h"
#include "parse.h"
#include "os_calls.h"
#include "defines.h"

/* this is the freerdp main header */
#include <freerdp/freerdp.h>
//#include "/home/jay/git/jsorg71/staging/include/freerdp/freerdp.h"

struct bitmap_item
{
  int width;
  int height;
  char* data;
};

struct brush_item
{
  int bpp;
  int width;
  int height;
  char* data;
  char b8x8[8];
};

struct pointer_item
{
  int hotx;
  int hoty;
  char data[32 * 32 * 3];
  char mask[32 * 32 / 8];
};

#define CURRENT_MOD_VER 2

struct mod
{
  int size; /* size of this struct */
  int version; /* internal version */
  /* client functions */
  int (*mod_start)(struct mod* v, int w, int h, int bpp);
  int (*mod_connect)(struct mod* v);
  int (*mod_event)(struct mod* v, int msg, long param1, long param2,
                   long param3, long param4);
  int (*mod_signal)(struct mod* v);
  int (*mod_end)(struct mod* v);
  int (*mod_set_param)(struct mod* v, char* name, char* value);
  int (*mod_session_change)(struct mod* v, int, int);
  int (*mod_get_wait_objs)(struct mod* v, tbus* read_objs, int* rcount,
                           tbus* write_objs, int* wcount, int* timeout);
  int (*mod_check_wait_objs)(struct mod* v);
  long mod_dumby[100 - 9]; /* align, 100 minus the number of mod
                              functions above */
  /* server functions */
  int (*server_begin_update)(struct mod* v);
  int (*server_end_update)(struct mod* v);
  int (*server_fill_rect)(struct mod* v, int x, int y, int cx, int cy);
  int (*server_screen_blt)(struct mod* v, int x, int y, int cx, int cy,
                           int srcx, int srcy);
  int (*server_paint_rect)(struct mod* v, int x, int y, int cx, int cy,
                           char* data, int width, int height, int srcx, int srcy);
  int (*server_set_cursor)(struct mod* v, int x, int y, char* data, char* mask);
  int (*server_palette)(struct mod* v, int* palette);
  int (*server_msg)(struct mod* v, char* msg, int code);
  int (*server_is_term)(struct mod* v);
  int (*server_set_clip)(struct mod* v, int x, int y, int cx, int cy);
  int (*server_reset_clip)(struct mod* v);
  int (*server_set_fgcolor)(struct mod* v, int fgcolor);
  int (*server_set_bgcolor)(struct mod* v, int bgcolor);
  int (*server_set_opcode)(struct mod* v, int opcode);
  int (*server_set_mixmode)(struct mod* v, int mixmode);
  int (*server_set_brush)(struct mod* v, int x_orgin, int y_orgin,
                          int style, char* pattern);
  int (*server_set_pen)(struct mod* v, int style,
                        int width);
  int (*server_draw_line)(struct mod* v, int x1, int y1, int x2, int y2);
  int (*server_add_char)(struct mod* v, int font, int charactor,
                         int offset, int baseline,
                         int width, int height, char* data);
  int (*server_draw_text)(struct mod* v, int font,
                          int flags, int mixmode, int clip_left, int clip_top,
                          int clip_right, int clip_bottom,
                          int box_left, int box_top,
                          int box_right, int box_bottom,
                          int x, int y, char* data, int data_len);
  int (*server_reset)(struct mod* v, int width, int height, int bpp);
  int (*server_query_channel)(struct mod* v, int index,
                              char* channel_name,
                              int* channel_flags);
  int (*server_get_channel_id)(struct mod* v, char* name);
  int (*server_send_to_channel)(struct mod* v, int channel_id,
                                char* data, int data_len,
                                int total_data_len, int flags);
  int (*server_bell_trigger)(struct mod* v);
  long server_dumby[100 - 25]; /* align, 100 minus the number of server
                                  functions above */
  /* common */
  tbus handle; /* pointer to self as long */
  tbus wm;
  tbus painter;
  int sck;
  /* mod data */
  int width;
  int height;
  int bpp;

  struct rdp_freerdp* inst;
  struct bitmap_item bitmap_cache[4][4096];
  struct brush_item brush_cache[64];
  struct pointer_item pointer_cache[32];

};
