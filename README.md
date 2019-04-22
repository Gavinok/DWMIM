Gavins personal fork of dwm
============================
Patches added:
1. uslessgaps /tilegaps (can be alternated or fully disabled in dwm.c)
2. center
3. scratchpad
4. max (custom script to merge fullscreen and monocle)
5. moveplace (customized for corners and centering windows)
6. mv (custom script for moving floating windows)
7. ispermanent 
8. statuscolors
9. zoomswap
10. warp
11. alwaysfloating (custom script to keep a client floating)
11. centerwindowname
11. nokill (custom script for prevent accidentally killing a client)
12. alpha for transparency in the bar

dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
