/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int deltamv = 20; /* deltamvmv = the amount of pixels each movement will be by */
static const unsigned int gappx     = 5;
static const unsigned int snap      = 60; /* snap pixel */
static const int showbar            = 1;  /* 0 means no bar */
static const int topbar             = 1;  /* 0 means bottom bar */
static const char *fonts[]          = { "Siji:style=Regular:size=13" };
static const char dmenufont[]       = "Siji:style=Regular:size=13";

static const char background[]  = "#111314";
static const char foreground[]  = "#B7BBB7";


static const char black1[]      = "#505050";
static const char black2[]      = "#505050";
                                          
                                          
static const char red1[]	= "#fb9fb1";
static const char red2[]	= "#B04C50";
                                          
                                          
static const char green1[]      = "#acc267";
static const char green2[]      = "#acc267";
                                          
                                          
static const char yellow1[]     = "#ddb26f";
static const char yellow2[]     = "#E2995C";
                                          
                                          
static const char blue1[]       = "#66899D";
static const char blue2[]       = "#66899D";
                                          
                                          
static const char magenta1[]    = "#e1a3ee";
static const char magenta2[]    = "#FF99FF";
                                          
                                          
static const char cyan1[]       = "#53cdbd";
static const char cyan2[]       = "#527C77";
                                          
                                          
static const char white1[]      = "#d0d0d0";
static const char white2[]      = "#f5f5f5";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] =	  { blue1, background, background },
	[SchemeSel]  =	  { red2 , background,  background },
};

/* tagging */
static const char *tags[] = { "home", "extra", "music", "news","💰"};


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask  iscentered isfloating	nokill alwaysfloat monitor */
	{ "Gimp",    NULL, NULL,             0,      0, 1, 0, 0, -1 },
	{ "Firefox", NULL, NULL,             1 << 3, 0, 0, 0, 0, -1 },
	{ NULL,      NULL, "newspod",        1 << 3, 0, 0, 0, 0, -1 },
	{ "Spotify", NULL, NULL,             1 << 2, 0, 0, 0, 0, -1 },
	{ NULL,      NULL, "pulsemixer",     0,      1, 1, 0, 0, -1 },
	{ NULL,      NULL, "launch_once.sh", 0,      1, 1, 0, 0, -1 },
	{ NULL,      NULL, "neomutt",        0,      1, 1, 0, 0, -1 },
	{ NULL,      NULL, "calcurse",       0,      1, 1, 0, 0, -1 },
	{ NULL,      NULL, "scratch",        0,      1, 1, 1, 1, -1 },
	{ NULL,      NULL, "castnow",        0,      0, 1, 0, 0, -1 },
	{ NULL,      NULL, "popup",          0,      1, 1, 0, 0, -1 },
	{ "feh",     NULL, NULL,             0,      1, 1, 0, 0, -1 },
	{ NULL,      NULL, "sxiv",           0,      1, 1, 0, 0, -1 },
	{ NULL,      NULL, "tmuxdd",         0,      1, 1, 1, 1, -1 },
	{ "mpv",     NULL, NULL,             0,      0, 0, 1, 0, -1 },
};

/* layout(s) */
static const float mfact     = 0.52; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
//custom functions
#include "maximize.c"
#include "nokill.c"
#include "mv.c"
#include "moveplace.c"
#include "zoomswap.c"
#include "warp.c"
#include "scratchpad.c"
#include "layouts.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "+++",      gaplessgrid },
	// { "+++",      horizgrid },
	{ "|M|",      centeredmaster },
	{ NULL,       NULL },
	// { "><>",      NULL },    /* no layout function means floating behavior */
	// { "[M]",      monocle },
};

#include "cyclelayout.c"

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,              KEY, view,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,  KEY, toggleview, {.ui = 1 << TAG} }, \
	{ AltMask,             KEY, tag,        {.ui = 1 << TAG} }, \
	{ AltMask|ControlMask, KEY, toggletag,  {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };

static const char term[]           = { "st"};
static const char exec[]           = { "-e" };
static const char scratchpadname[] = { "tmuxdd" };
static const char *termcmd[]       = { term, exec, "fish", NULL };
static const char *scratchpadcmd[] = { term, "-t", scratchpadname, "-e", "tmuxdd", "-g", "90x24", NULL };
static const char *email[]         = { term, exec, "launch_once.sh", "neomutt", NULL };
static const char *mixer[]         = { term, exec, "launch_once.sh", "pulsemixer", NULL };
// static const char *calender[]      = { term, exec, "launch_once.sh", "calcurse", NULL };
static const char *reddit[]        = { term, exec, "rtv", NULL };
static const char *rss[]           = { term, exec, "newsboat", NULL };
static const char *sysmonitor2[]   = { term, exec, "htop", NULL };
static const char *sysmonitor[]    = { term, exec, "vtop", NULL };
static const char *nm[]            = { "dmenu_connection_manager.sh", NULL };
static const char *mute[]          = { "lmc", "mute", NULL };
static const char *vdown[]         = { "lmc", "down", "5", NULL };
static const char *ldown[]         = { "llc.sh", "down", "7", NULL };
static const char *lup[]           = { "llc.sh", "up", "7", NULL };
static const char *vup[]           = { "lmc", "up", "5", NULL };
static const char *mplay[]         = { "lmc", "toggle", NULL };
static const char *mnext[]         = { "lmc", "next", NULL };
static const char *mprev[]         = { "lmc", "prev", NULL };
static const char *mount[]         = { "dmenumount", NULL };
static const char *unmount[]       = { "dmenuumount", NULL };
static const char *search[]        = { "ducksearch", NULL };
static const char *clip[]          = { "clipmenu", NULL };
static const char *plumb[]         = { "cabl", NULL };
static const char *killit[]        = { "dmenu-killall", NULL };
static const char *power[]         = { "power_menu.sh", NULL };
static const char *filemanager[]   = { "dmenu-open.sh", NULL };
static const char *screenshot[]    = { "windowshot.sh", NULL };
static const char *tutoral[]       = { "tutorialvids", NULL };
static const char *td[]            = { "td-toggle", NULL };
static const char *calc[]          = { "calc.sh", NULL };
static const char *dock[]          = { "dock_monitor", NULL };
static const char *undock[]        = { "single_monitor", NULL };
static const char *spell[]         = { "spellcheck.sh", NULL };
static const char *cast[]          = { "castcontrol.sh", NULL };
static const char *todo[]          = { "dmenu_googletasks.sh", NULL };
static const char *kdeconnect[]    = { "dmenu_kdeconnect.sh", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,              XK_u,            togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,              XK_d,            spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,    XK_l,            mv,             {.i = -1} },
	{ MODKEY|ShiftMask,    XK_h,            mv,             {.i = +1} },
	{ MODKEY|ShiftMask,    XK_j,            mv,             {.i = -2} },
	{ MODKEY|ShiftMask,    XK_k,            mv,             {.i = +2} },
	{ MODKEY,              XK_y,            spawn,          {.v = mixer } },
	{ MODKEY,              XK_Return,       spawn,          {.v = termcmd } },
	{ MODKEY,              XK_e,            spawn,          {.v = email } },
	{ MODKEY,              XK_n,            spawn,          {.v = rss } },
	{ MODKEY|ShiftMask,    XK_n,            spawn,          {.v = reddit } },
	{ MODKEY,              XK_c,            spawn,          {.v = calc } },
	{ MODKEY,              XK_m,            spawn,          {.v = mute } },
	{ MODKEY,              XK_i,            spawn,          {.v = sysmonitor2 } },
	{ MODKEY|ShiftMask,    XK_i,            spawn,          {.v = sysmonitor } },
	{ MODKEY|ControlMask,  XK_a,            spawn,          {.v = vdown } },
	{ MODKEY|ControlMask,  XK_s,            spawn,          {.v = ldown } },
	{ MODKEY|ControlMask,  XK_d,            spawn,          {.v = lup } },
	{ MODKEY|ControlMask,  XK_f,            spawn,          {.v = vup } },
	{ MODKEY|ControlMask,  XK_h,            spawn,          {.v = vdown } },
	{ MODKEY|ControlMask,  XK_j,            spawn,          {.v = ldown } },
	{ MODKEY|ControlMask,  XK_k,            spawn,          {.v = lup } },
	{ MODKEY|ControlMask,  XK_l,            spawn,          {.v = vup } },
	{ MODKEY,              XK_o,            spawn,          {.v = mount } },
	{ MODKEY|ShiftMask,    XK_o,            spawn,          {.v = unmount } },
	{ MODKEY,              XK_w,            spawn,          {.v = search } },
	{ MODKEY,              XK_p,            spawn,          {.v = clip } },
	{ MODKEY|ShiftMask,    XK_p,            spawn,          {.v = plumb } },
	{ AltMask|ControlMask, XK_q,            spawn,          {.v = killit } },
	{ MODKEY|ShiftMask,    XK_x,            spawn,          {.v = power } },
	{ MODKEY|ShiftMask,    XK_s,            spawn,          {.v = spell } },
	{ MODKEY,              XK_r,            spawn,          {.v = filemanager } },
	{ MODKEY,              XK_t,            spawn,          {.v = todo } },
	{ ShiftMask|MODKEY,    XK_t,            spawn,          {.v = tutoral } },
	{ ControlMask|AltMask, XK_t,            spawn,          {.v = td } },
	{ MODKEY,              XK_equal,        spawn,          {.v = kdeconnect } },
	{ MODKEY,              XK_bracketright, spawn,          {.v = mnext } },
	{ MODKEY,              XK_bracketleft,  spawn,          {.v = mprev } },
	{ MODKEY,              XK_backslash,    spawn,          {.v = mplay } },
	{ MODKEY|ShiftMask,    XK_backslash,    spawn,          {.v = cast } },
	{ MODKEY,              XK_F7,           spawn,          {.v = dock } },
	{ MODKEY,              XK_F8,           spawn,          {.v = undock } },
	{ MODKEY,              XK_F11,          spawn,          {.v = nm } },
	{ 0,                   XK_Print,        spawn,          {.v = screenshot }},
	{ 0,                   0x1008ff41,      spawn,          SHCMD("xset dpms force off")},
	{ 0,                   0x1008ff11,      spawn,          {.v = vdown } },
	{ 0,                   0x1008ff13,      spawn,          {.v = vup } },
	{ 0,                   0x1008ff12,      spawn,          {.v = mute } },

	{ MODKEY|ControlMask,  XK_b,            togglebar,      {0} },
	{ MODKEY,              XK_j,            focusstack,     {.i = +1 } },
	{ MODKEY,              XK_k,            focusstack,     {.i = -1 } },
	{ MODKEY,              XK_a,            incnmaster,     {.i = +1 } },
	{ MODKEY,              XK_s,            incnmaster,     {.i = -1 } },
	{ MODKEY,              XK_h,            setmfact,       {.f = -0.05} },
	{ MODKEY,              XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY,              XK_v,            zoomswap,       {0} },
	{ MODKEY,              XK_semicolon,    view,		{0} },
	{ MODKEY,              XK_5,		view,		{0} },
	{ MODKEY,              XK_q,            killclient,     {0} },
	{ MODKEY|ShiftMask,    XK_q,            forcekill,      {0} },
	{ MODKEY,              XK_BackSpace,    killclient,     {0} },
	{ MODKEY|ShiftMask,    XK_BackSpace,    forcekill,      {0} },
	{ MODKEY,              XK_apostrophe,   toggleNoKill,   {0} },
	{ MODKEY,              XK_f,            max,            {.i = 2} },
	{ MODKEY,              XK_Tab,          cyclelayout,    {.i = +1} },
	{ MODKEY|ShiftMask,    XK_Tab,          cyclelayout,    {.i = -1} },
	{ MODKEY,		XK_6,		cyclelayout,    {.i = +1} },
	{ MODKEY|ShiftMask,    XK_z,            togglefloating, {0} },
	// { MODKEY,              XK_0,            view,           {.ui = ~0 } },
	{ MODKEY,              XK_grave,        view,           {.ui = ~0 } },
	// { MODKEY|ShiftMask,    XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,    XK_grave,        tag,            {.ui = ~0 } },
	{ MODKEY,              XK_comma,        focusmon,       {.i = -1 } },
	{ MODKEY,              XK_period,       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_comma,        tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,    XK_period,       tagmon,         {.i = +1 } },
	{ MODKEY,              XK_g,            moveplace,      {.ui = WIN_C  }},
	{ MODKEY,              XK_Up,           moveplace,      {.ui = WIN_C  }},
	{ MODKEY,              XK_z,            moveplace,      {.ui = WIN_SW }},
	{ MODKEY,              XK_b,            moveplace,      {.ui = WIN_SE }},
	{ MODKEY,              XK_Left,         moveplace,      {.ui = WIN_SW }},
	{ MODKEY,              XK_Right,        moveplace,      {.ui = WIN_SE }},
	{ MODKEY,              0x1008ff27,      moveplace,      {.ui = WIN_NE }},
	{ MODKEY,              0x1008ff26,      moveplace,      {.ui = WIN_NW }},

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_7,                      1)
	TAGKEYS(                        XK_8,                      2)
	TAGKEYS(                        XK_9,                      3)
	TAGKEYS(                        XK_0,                      4)
	{ MODKEY|ShiftMask|ControlMask,             XK_q,      quit,           {0} },
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
