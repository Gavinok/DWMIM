/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */

// gaps
static const unsigned int gappx     = 6;

static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */

static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";

static const char black1[]       = "#151515";
static const char black2[]       = "#505050";
static const char red1[]       = "#fb9fb1";
static const char red2[]       = "#fb9fb1";
static const char green1[]        = "#acc267";
static const char green2[]        = "#acc267";
static const char yellow1[]        = "#ddb26f";
static const char yellow2[]        = "#ddb26f";
static const char blue1[]        = "#6fc2ef";
static const char blue2[]        = "#6fc2ef";
static const char magenta1[]        = "#e1a3ee";
static const char magenta2[]        = "##FF99FF";
static const char cyan1[]        = "#12cfc0";
static const char cyan2[]        = "#12cfc0";
static const char white1[]        = "#d0d0d0";
static const char white2[]        = "#f5f5f5";
static const char *colors[][3]      = {

	/*               fg         bg         border   */
	[SchemeNorm] = { white1, black1, black2 },
	[SchemeSel]  = { black1, magenta1,  white2 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "🎵", "🗞️" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

	/* class      instance    title       tags mask     iscentered     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,			0,				0,          1,           -1 },
	{ "Firefox",  NULL,       NULL,			1 << 8,			0,			0,           -1 },
	{ NULL,		  NULL,      "newspod" ,    3 << 8,			0,          0,           -1 },
	{ "Spotify",  NULL,		  NULL,			1 << 7,			0,			1,           -1 },
	{ NULL,		  NULL,      "pulsemixer",  0,				0,			1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 2;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ AltMask,						KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", black1, "-nf", white1, "-sb", magenta1, "-sf", black1, NULL };
static const char *termcmd[]  = { "st", "tmux",  NULL };

static const char *mixer[]  = { "st", "pulsemixer", NULL };
static const char *email[]  = { "st", "neomutt", NULL };
static const char *reddit[] = { "st", "rtv", NULL };
static const char *rss[]	= { "st", "newspod", NULL };
static const char *calender[]  = { "st", "calcurse", NULL };
static const char *sysmonitor[]  = { "st", "htop", NULL };
static const char *sysmonitor2[]  = { "st", "vtop", NULL };
static const char *nm[]  = { "networkmanager_dmenu", NULL };
static const char *music[]  = { "spotify", NULL };
static const char *refreshdwm[]  = { "st", "bash \"pushd ~/dwm; sudo make clean install; popd\"", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,		spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_y,		spawn,          {.v = mixer } },
	{ MODKEY,						XK_Return,  spawn,          {.v = termcmd } },
	{ MODKEY,						XK_e,		spawn,          {.v = email } },
	{ MODKEY,						XK_n,		spawn,          {.v = rss } },
	{ MODKEY|ShiftMask,				XK_n,		spawn,          {.v = reddit } },
	{ MODKEY,						XK_g,		spawn,          {.v = calender } },
	{ MODKEY,						XK_m,		spawn,          {.v = music } },
	{ MODKEY,						XK_asciitilde,		spawn,          {.v = refreshdwm } },
	{ MODKEY,						XK_i,		spawn,          {.v = sysmonitor2 } },
	{ MODKEY|ShiftMask,				XK_i,		spawn,          {.v = sysmonitor } },
	{ MODKEY,						XK_F11,		spawn,          {.v = nm } },
	{ MODKEY|ControlMask,			XK_a,		spawn,          SHCMD("lmc down 5") },
	{ MODKEY|ControlMask,			XK_s,		spawn,          SHCMD("xbacklight -dec 7") },
	{ MODKEY|ControlMask,			XK_d,		spawn,          SHCMD("xbacklight -inc 7") },
	{ MODKEY|ControlMask,			XK_f,		spawn,          SHCMD("lmc up 5") },
	{ MODKEY,                       XK_w,		spawn,          SHCMD("ducksearch") },
	{ AltMask|ControlMask,          XK_q,		spawn,          SHCMD("dmenu-killall") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_a,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_s,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_v,		zoom,           {0} },
	{ MODKEY,                       XK_Tab,     view,           {0} },
	{ MODKEY,						XK_q,		killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_z,		setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_z,		togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

