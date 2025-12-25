/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int gappx = 10;   /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int swallowfloating =
    0;                        /* 1 means swallow floating windows by default */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
static const int user_bh =
    6; /* 2 is the default spacing around the bar's font */
static const int vertpad = 10; /* vertical padding of bar */
static const int sidepad = 15; /* horizontal padding of bar */
static const char *fonts[] = {
    "Hack Nerd Font Mono:pixelsize=15:antialias=true:autohint=true"};
static const char dmenufont[] =
    "Hack Nerd Font Mono:pixelsize=15:antialias=true:autohint=true";

/* Red flavour colors */

static char normfgcolor[] = "#bbbbbb";
static char normbgcolor[] = "#0d0303";
static char normbordercolor[] = "#444444";

static char selfgcolor[] = "#eeeeee";
static char selbgcolor[] = "#911d29";
static char selbordercolor[] = "#911d29";

static char hidfgcolor[] = "#bbbbbb";
static char hidbgcolor[] = "#59111D";
static char hidbordercolor[] = "#59111D";

// /* Purple flavour colors */

// static char normfgcolor[] = "#bbbbbb";
// static char normbgcolor[] = "#1d0b26";
// static char normbordercolor[] = "#444444";

// static char selfgcolor[] = "#eeeeee";
// static char selbgcolor[] = "#962f8b";
// static char selbordercolor[] = "#962f8b";

static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;

static char *colors[][3] = {
    /*               fg           bg         border                         */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
    [SchemeHid] = {hidfgcolor, hidbgcolor, hidbordercolor},
};

static const unsigned int alphas[][3] = {
    /*                       fg      bg        border     */
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel] = {OPAQUE, baralpha, borderalpha},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask  isfloating  isterminal
       noswallow  monitor */
    {"Gimp", NULL, NULL, 0, 1, 0, 0, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, 0, -1, -1},
    {"St", NULL, NULL, 0, 0, 1, 0, -1},
    {NULL, NULL, "Event Tester", 0, 0, 0, 1, -1}, /* xev */
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle}, {"|M|", centeredmaster}, {">M>", centeredfloatingmaster},
};

/* key definitions */
#define MODKEY Mod1Mask
#define ALTMOD Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},    \
      {ALTMOD, KEY, focusnthmon, {.i = TAG}},                                  \
      {ALTMOD | ShiftMask, KEY, tagnthmon, {.i = TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-c", "-g",     "3",   "-l",
                                 "10",        "-m", dmenumon, "-fn", dmenufont,
                                 "-bw",       "3",  NULL};
static const char *termcmd[] = {"st", NULL};
static const char *tabtermcmd[] = {"tabbed", "-r", "2", "st", "-w", "''", NULL};
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = {"st", "-t",     scratchpadname,
                                      "-g", "120x34", NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {ALTMOD | ShiftMask, XK_Return, spawn, {.v = tabtermcmd}},
    {MODKEY, XK_grave, togglescratch, {.v = scratchpadcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstackvis, {.i = +1}},
    {MODKEY, XK_k, focusstackvis, {.i = -1}},
    {MODKEY | ShiftMask, XK_j, focusstackhid, {.i = +1}},
    {MODKEY | ShiftMask, XK_k, focusstackhid, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_u, setlayout, {.v = &layouts[3]}},
    {MODKEY, XK_o, setlayout, {.v = &layouts[4]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {ALTMOD | ShiftMask, XK_Tab, focusmon, {.i = -1}},
    {ALTMOD, XK_Tab, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_a, show, {0}},
    {MODKEY | ShiftMask, XK_a, showall, {0}},
    {ALTMOD, XK_h, hide, {0}},
    {MODKEY, XK_minus, setgaps, {.i = -1}},
    {MODKEY, XK_equal, setgaps, {.i = +1}},
    {MODKEY | ShiftMask, XK_equal, setgaps, {.i = 0}},
    {MODKEY | ShiftMask, XK_s, xrdb, {.v = NULL}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},

    {0, XF86XK_AudioLowerVolume, spawn,
     SHCMD("/usr/bin/pamixer -d 5;kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_AudioMute, spawn,
     SHCMD("/usr/bin/pamixer -t;kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_AudioRaiseVolume, spawn,
     SHCMD("/usr/bin/pamixer -i 5;kill -44 $(pidof dwmblocks)")},
    {0, XF86XK_MonBrightnessUp, spawn,
     SHCMD("/usr/bin/xbacklight -inc 5;kill -40 $(pidof dwmblocks)")},
    {0, XF86XK_MonBrightnessDown, spawn,
     SHCMD("/usr/bin/xbacklight -dec 5;kill -40 $(pidof dwmblocks)")},
    {0, XF86XK_AudioPrev, spawn, SHCMD("/usr/bin/mpc prev")},
    {0, XF86XK_AudioPlay, spawn, SHCMD("/usr/bin/mpc toggle")},
    {0, XF86XK_AudioNext, spawn, SHCMD("/usr/bin/mpc next")},
    {0, XF86XK_Search, spawn, SHCMD("$BROWSER")},
    {0, XK_Print, spawn,
     SHCMD("/usr/bin/maim -u | xclip -selection clipboard -t image/png; xclip "
           "-out -selection clipboard > ~/Pictures/Screenshots/$(date "
           "'+%F-%H-%M-%S').png")},
    {ShiftMask, XK_Print, spawn,
     SHCMD("/usr/bin/maim -su | xclip -selection clipboard -t image/png; xclip "
           "-out -selection clipboard > ~/Pictures/Screenshots/$(date "
           "'+%F-%H-%M-%S').png")},

    {ALTMOD,
     XK_v,
     spawn,
     {.v = (const char *[]){"dmenu_cliphist", "sel", NULL}}},
    {MODKEY,
     XK_c,
     spawn,
     {.v = (const char *[]){"dmenu_cliphist", "add", NULL}}},
    {MODKEY | ShiftMask,
     XK_Escape,
     spawn,
     {.v = (const char *[]){"dmenu_sys", NULL}}},
    {ALTMOD, XK_Escape, spawn, SHCMD("~/.local/bin/change_keyboard_layout.sh")},
    {MODKEY, XK_s, spawn, SHCMD("~/.local/bin/change_theme.sh")},

    {MODKEY | ALTMOD | ShiftMask, XK_s, spawn, SHCMD("pavucontrol")},
    {MODKEY | ALTMOD | ShiftMask, XK_b, spawn, SHCMD("blueman-manager")},
    {MODKEY | ALTMOD | ShiftMask, XK_d, spawn, SHCMD("discord")},
    {MODKEY | ALTMOD | ShiftMask, XK_o, spawn, SHCMD("obsidian")},
    {MODKEY | ALTMOD | ShiftMask, XK_v, spawn, SHCMD("stremio")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
/* click                event mask      button          function        argument
 */
#ifndef __OpenBSD__
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button1, sigstatusbar, {.i = 1}},
    {ClkStatusText, 0, Button2, sigstatusbar, {.i = 2}},
    {ClkStatusText, 0, Button3, sigstatusbar, {.i = 3}},
    {ClkStatusText, 0, Button4, sigstatusbar, {.i = 4}},
    {ClkStatusText, 0, Button5, sigstatusbar, {.i = 5}},
    {ClkStatusText, ShiftMask, Button1, sigstatusbar, {.i = 6}},
#endif
    {ClkStatusText, ShiftMask, Button3, spawn,
     SHCMD("st -e nvim ~/workplace/repos/dwmblocks/blocks.def.h")},
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button1, togglewin, {0}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
