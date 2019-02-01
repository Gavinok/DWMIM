
/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */

//deltamvmv = the amount of pixels each movement will be by
static const unsigned int deltamv = 20; 

// gaps
static const unsigned int gappx     = 13;

static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";

static const char black1[]      = "#151515";
static const char black2[]      = "#505050";
static const char red1[]		= "#fb9fb1";
static const char red2[]		= "#fb9fb1";
static const char green1[]      = "#acc267";
static const char green2[]      = "#acc267";
static const char yellow1[]     = "#ddb26f";
static const char yellow2[]     = "#f0c674";
static const char blue1[]       = "#6fc2ef";
static const char blue2[]       = "#6fc2ef";
static const char magenta1[]    = "#e1a3ee";
static const char magenta2[]    = "##ff99ff";
static const char cyan1[]       = "#12cfc0";
static const char cyan2[]       = "#12cfc0";
static const char white1[]      = "#d0d0d0";
static const char white2[]      = "#f5f5f5";
static const char col_black[]   = "#000000";
static const char col_red[]     = "#ff0000";
static const char col_yellow[]  = "#ffff00";
static const char col_white[]   = "#ffffff";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { white1, black1, black2 },
	[SchemeSel]  = { black1, magenta1,  white2 },
	//status colors 
	[SchemeWarn] =	 { yellow1, black1, black1 },
	[SchemeUrgent]=	 { red1, black1, black1 },
	[SchemeTime]=	 { blue1, black1, black1 },
	[SchemeCharging]= { yellow2, black1, black1 },
	[SchemeSafe]= { green1, black1, black1 },
};

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "🎶", "📪", "☕️"};
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "🎶", "📪"};

//custom functions
#include "maximize.c"
#include "mv.c"
#include "moveplace.c"
#include "zoomswap.c"
#include "warp.c"
#include "scratchpad.c"
// #include "notsofullscreen.c"

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

	/* class      instance    title       tags mask     iscentered     isfloating	ispermanent		alwaysfloating		monitor */
	{ "Gimp",     NULL,       NULL,			0,				0,          1,			0,				0,					-1 },
	{ "Firefox",  NULL,       NULL,			1 << 8,			0,			0,			0,				0,					-1 },
	{ NULL,		  NULL,      "newspod" ,    1 << 8,			0,          0,			0,				0,					-1 },
	{ "Spotify",  NULL,		  NULL,			1 << 7,			0,			0,			0,				0,					-1 },
	{ NULL,		  NULL,      "pulsemixer",  0,				1,			1,			0,				0,					-1 },
	{ NULL,		  NULL,      "neomutt",		0,				1,			1,			0,				0,					-1 },
	{ NULL,		  NULL,      "calcurse",	0,				1,			1,			0,				0,					-1 },
	{ NULL,		  NULL,      "tmuxdd",		0l,				1,			1,			1,				1,					-1 },
};

/* layout(s) */
static const float mfact     = 0.52; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	// { "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ AltMask,						KEY,      tag,            {.ui = 1 << TAG} }, \
	{ AltMask|ShiftMask,			KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", black1, "-nf", white1, "-sb", magenta1, "-sf", black1, NULL };

static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = { "tmuxdd"};
static const char *scratchpadcmd[] = { "st", "-e", scratchpadname, "-g", "120x34", NULL };
static const char *email[]  = { "st", "-e", "neomutt", NULL };
static const char *mixer[]  = { "st", "-e", "pulsemixer", NULL };
static const char *calender[]  = { "st", "-e", "calcurse", NULL }; 
static const char *reddit[] = { "st", "-e", "rtv", NULL };
static const char *rss[]	= { "st", "-e", "newspod", NULL };
static const char *sysmonitor[]  = { "st", "-e", "htop", NULL };
static const char *sysmonitor2[]  = { "st", "-e", "gotop", NULL };
static const char *nm[]  = { "dmenuconnect.sh", NULL };
static const char *music[]  = { "spotify", NULL };
static const char *Vdown[]  = { "lmc", "down", "5", NULL };
static const char *Ldown[]  = { "xbacklight", "-dec", "7", NULL };
static const char *Lup[]  = { "xbacklight", "-inc", "7", NULL };
static const char *Vup[]  = { "lmc", "up", "5", NULL };
static const char *mount[]  = { "dmenumount", NULL };
static const char *unmount[]  = { "dmenuumount", NULL };
static const char *search[]  = { "ducksearch", NULL };
static const char *clip[]  = { "clipmenu", NULL };
static const char *killit[]  = { "dmenu-killall", NULL };
static const char *power[]  = { "power_menu.sh", NULL };
static const char *filemanager[]  = {"st", "-e", "nnn", "-l", NULL };
static const char *tutoral[]  = {"tutorialvids", NULL };
static const char *help[]  = {"st", "-e", "ranger", "~/Documents/cheatsheets/", NULL };
static const char *dock[]  = {"dock_monitor", NULL };
static const char *undock[]  = {"single_monitor", NULL };
static const char *blackscreen[]  = {"xset", "dpms", "force", "off", NULL };
static const char *print[]  = {"maim", "-i", "$(xdotool", "getactivewindow)", "~/$(date", "+%s).png", NULL }; 



static Key keys[] = {
	/* modifier                     key        function        argument */
	// { MODKEY,                       XK_u, toggleview,			{.ui = 1 << 9}},
	// { MODKEY|ControlMask,           XK_u,	  spawn,			{.v = scratchpadcmd}},
	{ MODKEY,                       XK_u,  togglescratch,	   {.v = scratchpadcmd } },
	// { MODKEY,                       XK_XF86Launch1,  spawn,	   {.v = blackscreen } },
	{ MODKEY,                       XK_Print,  spawn,			{.v = print } },
	{ AltMask,                      XK_u,		tag,			{.ui = 1 << 9}},
	{ MODKEY|ShiftMask,				XK_l,		mv,				{.i = -1} },
	{ MODKEY|ShiftMask,				XK_h,		mv,				{.i = +1} },
	{ MODKEY|ShiftMask,				XK_j,		mv,				{.i = -2} },
	{ MODKEY|ShiftMask,				XK_k,		mv,				{.i = +2} },
	{ MODKEY,                       XK_d,		spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_y,		spawn,			{.v = mixer } },
	{ MODKEY,						XK_Return,  spawn,          {.v = termcmd } },
	{ MODKEY,						XK_e,		spawn,			{.v = email } },
	{ MODKEY,						XK_n,		spawn,          {.v = rss } },
	{ MODKEY|ShiftMask,				XK_n,		spawn,          {.v = reddit } },
	{ MODKEY,						XK_c,		spawn,			{.v = calender } },
	{ MODKEY,						XK_m,		spawn,          {.v = music } },
	{ MODKEY,						XK_i,		spawn,          {.v = sysmonitor2 } },
	{ MODKEY|ShiftMask,				XK_i,		spawn,          {.v = sysmonitor } },
	{ MODKEY|ControlMask,			XK_a,		spawn,          {.v = Vdown } },
	{ MODKEY|ControlMask,			XK_s,		spawn,          {.v = Ldown } },
	{ MODKEY|ControlMask,			XK_d,		spawn,          {.v = Lup } },
	{ MODKEY|ControlMask,			XK_f,		spawn,          {.v = Vup } },
	{ MODKEY,                       XK_o,		spawn,          {.v = mount } },
	{ MODKEY|ShiftMask,             XK_o,		spawn,          {.v = unmount } },
	{ MODKEY,                       XK_w,		spawn,          {.v = search } },
	{ MODKEY,                       XK_p,		spawn,          {.v = clip } },
	{ AltMask|ControlMask,          XK_q,		spawn,          {.v = killit } },
	{ MODKEY|ShiftMask,				XK_x,		spawn,          {.v = power } },
	{ MODKEY,						XK_r,		spawn,          {.v = filemanager } },
	{ MODKEY|ShiftMask,				XK_t,		spawn,          {.v = tutoral } },
	{ MODKEY|ControlMask,			XK_t,		spawn,          {.v = help } },
	{ MODKEY,						XK_F7,		spawn,          {.v = dock } },
	{ MODKEY,						XK_F8,		spawn,          {.v = undock } },
	{ MODKEY,						XK_F11,		spawn,          {.v = nm } },

	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_a,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_s,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_v,		zoomswap,       {0} },
	{ MODKEY,                       XK_Tab,     view,           {0} },
	{ MODKEY,						XK_q,		killclient,     {0} },
	// { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	// { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	// { MODKEY,                       XK_equal,      setlayout,      {.v = &layouts[1]} },
	// { MODKEY,                       XK_f,		setlayout,      {0} },
	{ MODKEY,                       XK_f,		togglemaximize,      {0} },
	{ MODKEY|ShiftMask,             XK_z,		togglefloating, {0} },
	{ MODKEY,                       XK_0,		view,           {.ui = ~0 } },
	{ MODKEY,                       XK_grave,   view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,		tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_grave,   tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_g,      moveplace,      {.ui = WIN_C  }},
	{ MODKEY,                       XK_z,      moveplace,      {.ui = WIN_SW }},
	{ MODKEY,                       XK_b,      moveplace,      {.ui = WIN_SE }},
	{ MODKEY,                       XK_b,      moveplace,      {.ui = WIN_SE }},

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
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
