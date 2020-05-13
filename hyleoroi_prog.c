/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



/*---(controls)-----------------------*/
tGLOBAL     my;
/*> tDEBUG      debug;                                                                <*/
char          unit_answer [LEN_FULL];



/*---(trig values)--------------------*/
float       my_sin [4000];
float       my_cos [4000];




/*====================------------------------------------====================*/
/*===----                            utilities                         ----===*/
/*====================------------------------------------====================*/
void  o___UTILITIES_______o () { return; }

long
TIME_stamp         (void)                      /* PURPOSE : timestamp in microseconds      */
{
   /* second
    * millisecond  ms  0.001 sec
    * microsecond  us  0.000001 sec
    * nanosecond   ns  0.000000001 sec
    * picosecond   ps  0.000000000001 sec
    */
   /*---(locals variables)-+-----------+-*/
   long        tint        = 0;
   struct      timeval     tv;
   /*---(calculate)----------------------*/
   gettimeofday(&tv, NULL);
   tint += (int) (tv.tv_sec  * 1000);
   tint += (int) (tv.tv_usec / 1000);
   /*---(complete)-----------------------*/
   return tint;
}




/*====================------------------------------------====================*/
/*===----                   standard program functions                 ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char      verstring    [500];

char*        /*--: return versioning information ---------[ ------ [ ------ ]-*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc  ]", 15);
#elif  __CBANG__  > 0
   strncpy (t, "[cbang    ]", 15);
#else
   strncpy (t, "[unknown  ]", 15);
#endif
   snprintf (verstring, 100, "%s   %s : %s", t, VER_NUM, VER_TXT);
   return verstring;
}

char             /* [------] minimal pre-argument program initialization -----*/
PROG_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   float       d           =  0.0;          /* degrees in tenths              */
   /*---(begin)--------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   rc = STDIN_check ();
   DEBUG_TOPS   yLOG_value   ("stdin"     , rc);
   --rce;  if (rc < 0) {
      fprintf (stderr, "warning.  nothing on stdin.  nothing to do.  done.\n");
      DEBUG_TOPS   yLOG_note    ("nothing on stding");
      DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(globals)------------------------*/
   FORMAT_init  ();
   my.print       =  '-';
   my.space       =    0;
   my.explode     =  0.0;
   my.focus       = NULL;
   my.noempty     =  '-';
   my.hints       =  '-';
   my.ring        =  170;
   my.point       =   24;
   my.full_size   =   360;
   my.type        = '-';
   my.format      = 'r';
   my.ghost       = '-';
   my.max_depth   =  -1;
   my.empty       = NULL;
   my.node_dump   =  '-';
   /*---(default run-time options)-------*/
   DEBUG_TOPS   yLOG_note    ("pre-load trig values");
   for (i = 0; i < 4000; ++i) {
      d   = (float) i / 10;
      my_sin [i] = sin (d * DEG2RAD);
      my_cos [i] = cos (d * DEG2RAD);
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] process the command line arguments --------------*/
PROG_args          (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;             /* loop iterator -- arguments     */
   char       *a           = NULL;          /* current argument               */
   int         len         = 0;             /* argument length                */
   int         x_total     = 0;
   int         x_args      = 0;
   /*---(begin)--------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(process)------------------------*/
   for (i = 1; i < argc; ++i) {
      /*---(read)------------------------*/
      a   = argv [i];
      len = strlen(a);
      ++x_total;
      /*---(filter)----------------------*/
      if (a[0] == '@')  continue;
      ++x_args;
      DEBUG_ARGS   yLOG_info  ("argument"  , a);
      /*---(startup/shutdown)------------*/
      if      (strcmp (a, "--print"             ) == 0)    my.print          = 'y';
      else if (strcmp (a, "--noempty"           ) == 0)    my.noempty        = 'y';
      else if (strcmp (a, "--hints"             ) == 0)    my.hints          = 'y';
      else if (strcmp (a, "--ghost"             ) == 0)    my.ghost          = 'y';
      else if (strcmp (a, "--block"             ) == 0) {
         my.format         = 'b';
         my.inc            =  STOP;
      }
      else if (strcmp (a, "--radial"            ) == 0) {
         my.format         = 'r';
         my.inc            =  PLAY;
      }
      else if (strcmp (a, "--space"             ) == 0) {
         if (i + 1 < argc) if (atoi (argv [i + 1]) > 0 )  my.space   = atoi (argv[++i]);
      }
      else if (strcmp (a, "--explode"           ) == 0) {
         if (i + 1 < argc) if (atof (argv [i + 1]) > 0 )  my.explode = atof (argv[++i]);
      }
      else if (strcmp (a, "--mime"              ) == 0) {
         my.type    = 'm';
      }
      else if (strcmp (a, "--dirtree"           ) == 0) {
         my.type    = 'd';
      }
      else if (strcmp (a, "--node-dump"         ) == 0) {
         my.node_dump    = 'y';
      }
      /*---(color options)---------------*/
      else if (strcmp (a, "--color-white"       ) == 0)  yCOLOR_diff_scheme (YCOLOR_WHITE);
      else if (strcmp (a, "--color-light"       ) == 0)  yCOLOR_diff_scheme (YCOLOR_LIGHT);
      else if (strcmp (a, "--color-dark"        ) == 0)  yCOLOR_diff_scheme (YCOLOR_DARK );
      else if (strcmp (a, "--color-black"       ) == 0)  yCOLOR_diff_scheme (YCOLOR_BLACK);
      else if (strcmp (a, "--color-start"       ) == 0) {
         if (i + 1 < argc) if (atoi (argv [i + 1]) > 0 ) yCOLOR_diff_start (atoi (argv[++i]));
      }
      else if (strcmp (a, "--color-chaos"       ) == 0) {
         if (i + 1 < argc) if (atoi (argv [i + 1]) > 0 ) yCOLOR_diff_chaos (atoi (argv[++i]));
      }
   }
   /*---(display urgents)----------------*/
   DEBUG_ARGS   yLOG_note    ("summarization of argument processing");
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] post-argument program initialization ------------*/
PROG_begin         (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   int         x_cum       = 0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---()-------------------------------*/
   FORMAT_set     ("dirtree");
   NODE_init      ();
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS   yLOG_break   ();
   return 0;
}

char             /* [------] post-argument program initialization ------------*/
PROG_visual_beg    (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   int         x_cum       = 0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---()-------------------------------*/
   DRAW_globals   ();
   DRAW_window_sizes ();
   yX11_start   (my.w_title, my.w_wide, my.w_tall, YX_FOCUSABLE, YX_FIXED, YX_SILENT);
   FONT_load      ();
   DRAW_init      ();
   DRAW_resize    (my.w_wide, my.w_tall);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS   yLOG_break   ();
   return 0;
}

char                /* PURPOSE : shutdown program and free memory ------------*/
PROG_visual_end    (void)
{
   DEBUG_TOPS   yLOG_break   ();
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*> yGLTEX_free  ();                                                               <*/
   FONT_unload  ();
   yX11_end     ();
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS   yLOGS_end     ();
   return 0;
}

char                /* PURPOSE : shutdown program and free memory ------------*/
PROG_end           (void)
{
   DEBUG_TOPS   yLOG_break   ();
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS   yLOGS_end     ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   helpers for unit testing                   ----===*/
/*====================------------------------------------====================*/
static void      o___UNIT_TEST_______________o (void) {;}

char       /*----: set up programgents/debugging -----------------------------*/
PROG__unit_quiet    (void)
{
   char       *x_args [1]  = { "hyleoroi" };
   yURG_logger (1, x_args);
   PROG_init   ();
   yURG_urgs   (1, x_args);
   PROG_args   (1, x_args);
   PROG_begin  ();
   return 0;
}

char       /*----: set up programgents/debugging -----------------------------*/
PROG__unit_loud    (void)
{
   char       *x_args [2]  = { "hyleoroi_unit", "@@kitchen"    };
   yURG_logger (2, x_args);
   PROG_init   ();
   yURG_urgs   (2, x_args);
   PROG_args   (2, x_args);
   PROG_begin  ();
   return 0;
}

char       /*----: set up programgents/debugging -----------------------------*/
PROG__unit_end     (void)
{
   PROG_end ();
}





/*===============================[[ end-code ]]===============================*/
