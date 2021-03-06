/* appearance */
static const unsigned int borderpx  = 4;        
static const unsigned int gappx     = 5;        
static const unsigned int snap      = 32;   
static const int showbar            = 1;       
static const int topbar             = 1;        
static const char *fonts[]          = { "monospace:size=15" };
static const char dmenufont[]       = "monospace:size=15";
static const char col_black[]	    = "#000000";
static const char col_gray1[]       = "#222222";
static const char col_darkblue[]    = "#000033";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_green[]   = "#00e000";	
static const char col_cyan[]    = "#005577";
static const unsigned int baralpha = 0xa0;//0x0 is full tranparent
static const unsigned int borderalpha = 0xd0;//OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#ffffff", col_gray2, col_gray2 },
	[SchemeSel]  = { col_black, col_green,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
       /*               fg      bg        border     */
       [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
       [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8","9"  };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const Layout layouts[] = {
	/* symbol     arrange function */
	/* first entry is default */
	{ "[]=",      tile },
//	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#include <X11/XF86keysym.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpad[] = { "urxvt", "-title", "scratchpad", "-e", "ranger", NULL };
static Key keys[] = {
	{ MODKEY|ControlMask,		XK_a,	   spawn,	   SHCMD("urxvt -title scratchpad -e alsamixer") },
	{ MODKEY|ControlMask,           XK_Return, togglescratch, {.v = scratchpad } },
	
	{ MODKEY|ShiftMask|ControlMask, XK_Escape, spawn,	   SHCMD("poweroff") },
	{ MODKEY|ShiftMask|ControlMask, XK_r,      spawn,	   SHCMD("reboot") },
	{ MODKEY|ShiftMask, 		XK_s, 	   spawn,	   SHCMD("spotify") },	
	{ MODKEY,                       XK_b,      spawn,          SHCMD("brave") },
	{ MODKEY|ShiftMask, 		XK_i, 	   spawn,	   SHCMD("statusmyip") },   //show ip addr	
	{ MODKEY, 			XK_m, 	   spawn,	   SHCMD("statuscpumem") }, //show mem and cpu info on status
	{ ControlMask,			XK_Left,   spawn, 	   SHCMD("volctl mute; refreshbar") },		//unmute
	{ ControlMask,			XK_Up,     spawn, 	   SHCMD("volctl up; refreshbar")  },		//vol up
	{ ControlMask,			XK_Down,   spawn, 	   SHCMD("volctl down; refreshbar")  }, 	//vol down
	{ MODKEY|ControlMask,		XK_Up,     spawn, 	   SHCMD("volctl bup; refreshbar")  },		//big vol up
	{ MODKEY|ControlMask,		XK_Down,   spawn, 	   SHCMD("volctl bdown; refreshbar")  },	//big vol down
	{0, XF86XK_AudioMute, 	                   spawn,          SHCMD("volctl mute; refreshbar") },		//mute
	{0, XF86XK_AudioRaiseVolume,               spawn,          SHCMD("volctl up;refreshbar") },		//volup	
	{0, XF86XK_AudioLowerVolume, 	           spawn,          SHCMD("volctl down;refreshbar") },		//voldown	
	{0, XF86XK_MonBrightnessUp, 	           spawn,          SHCMD("sudo intelbacklight -inc 70") },	//brightness up
	{0, XF86XK_MonBrightnessDown,              spawn,          SHCMD("sudo intelbacklight -dec 70") },	//brightness dwon	
	{ MODKEY,			XK_r,      spawn,	   SHCMD("redshift -P -O 1500K") },    	//red light filter on
	{ MODKEY|ShiftMask,		XK_r,      spawn,	   SHCMD("redshift -P -O 4000K") },   	//red light filter off
	
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_a,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                     XK_n,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                     XK_s,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_z,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
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
