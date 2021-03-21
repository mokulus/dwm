/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char dmenufont[]       = "monospace:size=12";
static const char *fonts[]          = { dmenufont };

/* vscode */
static const char col_fg[]        = "#ffffff";
static const char col_bg[]        = "#000000";
static const char col_cyan[]      = "#0dbc79";

/* srcery */
/* static const char col_fg[]        = "#D0BFA1"; */
/* static const char col_bg[]        = "#1C1B19"; */
/* static const char col_cyan[]      = "#519F50"; */

/* zenburn */
/* static const char col_fg[]        = "#dcdccc"; */
/* static const char col_bg[]        = "#3f3f3f"; */
/* static const char col_cyan[]      = "#7f9f7f"; */

/* tomorrow night */
/* static const char col_fg[]        = "#c5c8c6"; */
/* static const char col_bg[]        = "#000000"; */
/* static const char col_cyan[]      = "#81a2be"; */

static const char col_border[] = "#222222";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg, col_bg, col_border },
	[SchemeSel]  = { col_bg, col_cyan, col_cyan },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "float",   NULL,     NULL,           0,         1,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};


/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_cyan, "-sf", col_bg, NULL };
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL }; */
static const char *termcmd[]  = { "/bin/sh", "-c", "$TERMINAL", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd} },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd} },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,			XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("torrent-add") },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	/* { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, */
	/* { MODKEY,                       XK_period, focusmon,       {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
        { MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} }, /* quit */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {1} }, /* refresh */
	/* { MODKEY,			XK_minus,	 spawn,		SHCMD("amixer sset Master 5%-") }, */
	{ MODKEY,			XK_minus,	 spawn,		SHCMD("pulsemixer --change-volume -5") },
	/* { MODKEY,			XK_equal,	 spawn,		SHCMD("amixer sset Master 5%+") }, */
	{ MODKEY,			XK_equal,	 spawn,		SHCMD("pulsemixer --change-volume +5") },
	{ MODKEY,			XK_BackSpace,	 spawn,		SHCMD("sysact") },
	{ MODKEY,			XK_w,		 spawn,		SHCMD("$BROWSER") },
	{ MODKEY,			XK_p,		 spawn,		SHCMD("mpc toggle") },
	{ MODKEY|ShiftMask,		XK_p,		 spawn,		SHCMD("mpc pause; pauseallmpv") },
	{ MODKEY,			XK_bracketleft,	 spawn,		SHCMD("mpc seek -10") },
	{ MODKEY|ShiftMask,		XK_bracketleft,	 spawn,		SHCMD("mpc seek -60") },
	{ MODKEY,			XK_bracketright, spawn,		SHCMD("mpc seek +10") },
	{ MODKEY|ShiftMask,		XK_bracketright, spawn,		SHCMD("mpc seek +60") },
	{ MODKEY,			XK_comma,	 spawn,		SHCMD("mpc prev") },
	{ MODKEY|ShiftMask,		XK_comma,	 spawn,		SHCMD("mpc seek 0") },
	{ MODKEY,			XK_period,	 spawn,		SHCMD("mpc next") },
	{ MODKEY|ShiftMask,		XK_period,	 spawn,		SHCMD("mpc repeat") },
	/* { MODKEY,			XK_a,		 spawn,		SHCMD("$TERMINAL -e alsamixer") }, */
	{ MODKEY,			XK_a,		 spawn,		SHCMD("$TERMINAL -e pulsemixer") },
	{ MODKEY|ShiftMask,		XK_a,		 spawn,		SHCMD("anki") },
	{ MODKEY,			XK_c,		 spawn,		SHCMD("read-book") },
	{ MODKEY,			XK_v,		 spawn,		SHCMD("play-video") },
	/* { MODKEY,			XK_n,		 spawn,		SHCMD("$TERMINAL -e newsboat") }, */
	{ MODKEY,			XK_m,		 spawn,		SHCMD("$TERMINAL -e ncmpcpp") },
	/* { MODKEY|ShiftMask,		XK_m,		 spawn,		SHCMD("amixer sset Master toggle") }, */
	{ MODKEY|ShiftMask,		XK_m,		 spawn,		SHCMD("pulsemixer --toggle-mute") },
	{ MODKEY,			XK_e,		 spawn,		SHCMD("emacsclient -c") },

	{ MODKEY,			XK_s,		 spawn,		SHCMD("systemctl suspend") },
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

