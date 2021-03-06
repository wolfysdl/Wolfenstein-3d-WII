/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2006 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/
#include "SDL_config.h"

#ifndef _SDL_mouse_c_h
#define _SDL_mouse_c_h

typedef struct SDL_Mouse SDL_Mouse;

struct SDL_Cursor
{
    SDL_Mouse *mouse;

    SDL_Cursor *next;

    void *driverdata;
};

struct SDL_Mouse
{
    /* Create a cursor from a surface */
    SDL_Cursor *(*CreateCursor) (SDL_Surface * surface, int hot_x, int hot_y);

    /* Show the specified cursor, or hide if cursor is NULL */
    int (*ShowCursor) (SDL_Cursor * cursor);

    /* This is called when a mouse motion event occurs */
    void (*MoveCursor) (SDL_Cursor * cursor);

    /* Free a window manager cursor */
    void (*FreeCursor) (SDL_Cursor * cursor);

    /* Warp the mouse to (x,y) */
    void (*WarpMouse) (SDL_Mouse * mouse, SDL_WindowID windowID, int x,
                       int y);

    /* Free the mouse when it's time */
    void (*FreeMouse) (SDL_Mouse * mouse);

    /* Data common to all mice */
    SDL_WindowID focus;
    int x;
    int y;
    int xdelta;
    int ydelta;
    Uint8 buttonstate;
    SDL_bool relative_mode;
    SDL_bool flush_motion;

    SDL_Cursor *cursors;
    SDL_Cursor *def_cursor;
    SDL_Cursor *cur_cursor;
    SDL_bool cursor_shown;

    void *driverdata;
};


/* Initialize the mouse subsystem */
extern int SDL_MouseInit(void);

/* Get the mouse at an index */
extern SDL_Mouse *SDL_GetMouse(int index);

/* Add a mouse, possibly reattaching at a particular index (or -1),
   returning the index of the mouse, or -1 if there was an error.
 */
extern int SDL_AddMouse(const SDL_Mouse * mouse, int index);

/* Remove a mouse at an index, clearing the slot for later */
extern void SDL_DelMouse(int index);

/* Clear the button state of a mouse at an index */
extern void SDL_ResetMouse(int index);

/* Set the mouse focus window */
extern void SDL_SetMouseFocus(int index, SDL_WindowID windowID);

/* Send a mouse motion event for a mouse at an index */
extern int SDL_SendMouseMotion(int index, int relative, int x, int y);

/* Send a mouse button event for a mouse at an index */
extern int SDL_SendMouseButton(int index, Uint8 state, Uint8 button);

/* Send a mouse wheel event for a mouse at an index */
extern int SDL_SendMouseWheel(int index, int x, int y);

/* Shutdown the mouse subsystem */
extern void SDL_MouseQuit(void);

#endif /* _SDL_mouse_c_h */

/* vi: set ts=4 sw=4 expandtab: */
