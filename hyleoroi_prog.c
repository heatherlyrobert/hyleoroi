/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



/*---(controls)-----------------------*/
tGLOBAL     my;
tDEBUG      debug;



/*---(trig values)--------------------*/
float       my_sin [4000];
float       my_cos [4000];


tFORMAT     g_formats [MAX_FORMAT];
/*> tFORMAT     g_formats [MAX_FORMAT] = {                                                                                                                                       <* 
 *>    /+  type, format,   full, cutoff, point, -ring, --0--, --1--, --2--, --3--, --4--, --5--, --6--,  ---tdesc----------------------,  ---fdesc--   -label-  ghost empty +/   <* 
 *>    {    'm',    'r',    360,      2,    32,   180,   200,   400,  1200,     0,     0,     0,     0, "mime two-layer"               , "radial"   , "--d----", 'y' , 'y'  },   <* 
 *>    {    'm',    'b',   2000,      2,    32,   290,   400,   600,  2000,     0,     0,     0,     0, "mime two-layer"               , "block"    , "--d----", 'y' , 'y'  },   <* 
 *>    {    'd',    'r',    360,      7,    24,   170,     0,     0,     0,     0,     0,     0,     0, "dirtree seven layer"          , "radial"   , "-------", 'y' , '-'  },   <* 
 *>    {    'd',    'b',   2000,      7,    16,   290,     0,     0,     0,     0,     0,     0,     0, "dirtree seven layer"          , "block"    , "-------", 'y' , '-'  },   <* 
 *>    {    '-',    'r',    360,      7,    16,   170,     0,     0,     0,     0,     0,     0,     0, "default"                      , "radial"   , "-------", 'y' , '-'  },   <* 
 *>    {    '-',    'b',   2000,      7,    16,   170,     0,     0,     0,     0,     0,     0,     0, "default"                      , "block"    , "-------", 'y' , '-'  },   <* 
 *>    {    '-',    '-',    360,      7,    16,   170,     0,     0,     0,     0,     0,     0,     0, "default"                      , "radial"   , "-------", 'y' , '-'  },   <* 
 *>    {    '-',    '-',      0,      7,    16,   170,     0,     0,     0,     0,     0,     0,     0, "end-of-entries"               , "end"      , "-------", 'y' , '-'  },   <* 
 *> };                                                                                                                                                                           <*/


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

char         /*--: wholesale urgents change --------------[ ------ [ ------ ]-*/
PROG_urgsmass      (char a_set, char a_extra)
{
   /*---(overall)------------------------*/
   debug.tops   = a_set;
   debug.summ   = a_set;
   /*---(startup/shutdown)---------------*/
   debug.args   = a_set;
   debug.conf   = a_set;
   debug.prog   = a_set;
   /*---(file processing)----------------*/
   debug.inpt   = a_set;
   debug.inptM  = a_set;
   debug.outp   = a_set;
   debug.outpM  = a_set;
   /*---(event handling)-----------------*/
   debug.loop   = a_set;
   debug.user   = a_set;
   debug.apis   = a_set;
   debug.sign   = a_set;
   debug.scrp   = a_set;
   debug.hist   = a_set;
   /*---(program)------------------------*/
   debug.graf   = a_set;
   debug.data   = a_set;
   debug.envi   = a_set;
   debug.enviM  = a_set;
   debug.mems   = a_set;
   /*---(specific)-----------------------*/
   if (a_extra == 'y') {
      debug.color  = a_set;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] process the command line urgent arguments -------*/
PROG_urgs          (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;        /* loop iterator -- arguments          */
   char       *a           = NULL;     /* current argument                    */
   int         x_len       = 0;        /* argument length                     */
   int         x_total     = 0;
   int         x_urgs      = 0;
   char        x_logger    = '-';
   /*---(default urgents)----------------*/
   PROG_urgsmass ('-', 'y');
   /*---(logger preprocessing)-----------*/
   debug.logger = -1;
   for (i = 1; i < argc; ++i) {
      a = argv[i];
      if (a[0] != '@')  continue;
      x_logger   = 'y';
      if       (strcmp ("@a"        , a) == 0)  debug.args = 'y';
      else if  (strcmp ("@@args"    , a) == 0)  debug.args = 'y';
      else if  (strcmp ("@f"        , a) == 0)  debug.args = 'y';
      else if  (strcmp ("@@full"    , a) == 0)  debug.args = 'y';
      else if  (strcmp ("@k"        , a) == 0)  debug.args = 'y';
      else if  (strcmp ("@@kitchen" , a) == 0)  debug.args = 'y';
      else if ((strcmp ("@q", a) == 0) || (strcmp ("@@quiet", a) == 0)) {
         x_logger = 'n';
         PROG_urgsmass ('-', 'y');
         break;
      }
   }
   /*---(startup logging)----------------*/
   if (x_logger == 'y') {
      debug.tops = 'y';
      debug.logger = yLOG_begin ("hyleoroi", yLOG_SYSTEM, yLOG_NOISE);
      DEBUG_TOPS   yLOG_info     ("purpose" ,  "file location, change, and search services");
      DEBUG_TOPS   yLOG_info     ("hyleoroi",  PROG_version ());
      DEBUG_TOPS   yLOG_info     ("yLOG"    ,  yLOG_version ());
   } else {
      debug.logger = yLOG_begin ("hyleoroi", yLOG_SYSTEM, yLOG_QUIET);
   }
   /*---(walk through urgents)-----------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   for (i = 1; i < argc; ++i) {
      /*---(prepare)---------------------*/
      a        = argv[i];
      x_len    = strlen (a);
      ++x_total;
      /*---(filter)----------------------*/
      if (a[0] != '@')  continue;
      ++x_urgs;
      DEBUG_ARGS   yLOG_info  ("urgent"    , a);
      /*---(overall)---------------------*/
      if      (strncmp(a, "@t"           ,10) == 0)  debug.tops = 'y';
      else if (strncmp(a, "@@top"        ,10) == 0)  debug.tops = 'y';
      else if (strncmp(a, "@s"           ,10) == 0)  debug.tops = debug.summ  = 'y';
      else if (strncmp(a, "@@summ"       ,10) == 0)  debug.tops = debug.summ  = 'y';
      /*---(startup/shutdown)------------*/
      else if (strncmp(a, "@a"           ,10) == 0)  debug.tops = debug.args  = 'y';
      else if (strncmp(a, "@@args"       ,10) == 0)  debug.tops = debug.args  = 'y';
      else if (strncmp(a, "@c"           ,10) == 0)  debug.tops = debug.conf  = 'y';
      else if (strncmp(a, "@@conf"       ,10) == 0)  debug.tops = debug.conf  = 'y';
      else if (strncmp(a, "@p"           ,10) == 0)  debug.tops = debug.prog  = 'y';
      else if (strncmp(a, "@@prog"       ,10) == 0)  debug.tops = debug.prog  = 'y';
      /*---(file processing)-------------*/
      else if (strncmp(a, "@i"           ,10) == 0)  debug.tops = debug.inpt  = 'y';
      else if (strncmp(a, "@@inpt"       ,10) == 0)  debug.tops = debug.inpt  = 'y';
      else if (strncmp(a, "@I"           ,10) == 0)  debug.tops = debug.inpt  = debug.inptM = 'y';
      else if (strncmp(a, "@@INPT"       ,10) == 0)  debug.tops = debug.inpt  = debug.inptM = 'y';
      else if (strncmp(a, "@o"           ,10) == 0)  debug.tops = debug.outp  = 'y';
      else if (strncmp(a, "@@outp"       ,10) == 0)  debug.tops = debug.outp  = 'y';
      else if (strncmp(a, "@O"           ,10) == 0)  debug.tops = debug.outp  = debug.outpM = 'y';
      else if (strncmp(a, "@@OUTP"       ,10) == 0)  debug.tops = debug.outp  = debug.outpM = 'y';
      /*---(processing)------------------*/
      else if (strncmp(a, "@l"           ,10) == 0)  debug.tops = debug.loop  = 'y';
      else if (strncmp(a, "@@loop"       ,10) == 0)  debug.tops = debug.loop  = 'y';
      else if (strncmp(a, "@u"           ,10) == 0)  debug.tops = debug.user  = 'y';
      else if (strncmp(a, "@@user"       ,10) == 0)  debug.tops = debug.user  = 'y';
      else if (strncmp(a, "@z"           ,10) == 0)  debug.tops = debug.apis  = 'y';
      else if (strncmp(a, "@@apis"       ,10) == 0)  debug.tops = debug.apis  = 'y';
      else if (strncmp(a, "@x"           ,10) == 0)  debug.tops = debug.sign  = 'y';
      else if (strncmp(a, "@@sign"       ,10) == 0)  debug.tops = debug.sign  = 'y';
      else if (strncmp(a, "@b"           ,10) == 0)  debug.tops = debug.scrp  = 'y';
      else if (strncmp(a, "@@scrp"       ,10) == 0)  debug.tops = debug.scrp  = 'y';
      else if (strncmp(a, "@h"           ,10) == 0)  debug.tops = debug.hist  = 'y';
      else if (strncmp(a, "@@hist"       ,10) == 0)  debug.tops = debug.hist  = 'y';
      /*---(program)---------------------*/
      else if (strncmp(a, "@g"           ,10) == 0)  debug.tops = debug.graf  = 'y';
      else if (strncmp(a, "@@graf"       ,10) == 0)  debug.tops = debug.graf  = 'y';
      else if (strncmp(a, "@d"           ,10) == 0)  debug.tops = debug.data  = 'y';
      else if (strncmp(a, "@@data"       ,10) == 0)  debug.tops = debug.data  = 'y';
      else if (strncmp(a, "@e"           ,10) == 0)  debug.tops = debug.envi  = 'y';
      else if (strncmp(a, "@@envi"       ,10) == 0)  debug.tops = debug.envi  = 'y';
      else if (strncmp(a, "@E"           ,10) == 0)  debug.tops = debug.envi  = debug.enviM = 'y';
      else if (strncmp(a, "@@ENVI"       ,10) == 0)  debug.tops = debug.envi  = debug.enviM = 'y';
      else if (strncmp(a, "@m"           ,10) == 0)  debug.tops = debug.mems  = 'y';
      else if (strncmp(a, "@@mems"       ,10) == 0)  debug.tops = debug.mems  = 'y';
      /*---(complex)---------------------*/
      else if (strncmp(a, "@f"           ,10) == 0)  PROG_urgsmass ('y', '-');
      else if (strncmp(a, "@@full"       ,10) == 0)  PROG_urgsmass ('y', '-');
      else if (strncmp(a, "@k"           ,10) == 0)  PROG_urgsmass ('y', 'y');
      else if (strncmp(a, "@@kitchen"    ,10) == 0)  PROG_urgsmass ('y', 'y');
      /*---(specific)--------------------*/
      else if (strncmp(a, "@@color"      ,10) == 0)  debug.tops = debug.color = 'y';
      /*---(unknown)--------------------*/
      else {
         DEBUG_ARGS   yLOG_note    ("urgent not understood");
      }
      /*---(done)-----------------------*/
   }
   /*---(display urgents)----------------*/
   DEBUG_ARGS   yLOG_note    ("summarization of urgent processing");
   DEBUG_ARGS   yLOG_value   ("entries"   , x_total);
   DEBUG_ARGS   yLOG_value   ("urgents"   , x_urgs);
   DEBUG_ARGS   yLOG_note    ("standard urgents");
   DEBUG_ARGS   yLOG_char    ("tops"      , debug.tops);
   DEBUG_ARGS   yLOG_char    ("summ"      , debug.summ);
   DEBUG_ARGS   yLOG_char    ("args"      , debug.args);
   DEBUG_ARGS   yLOG_char    ("conf"      , debug.conf);
   DEBUG_ARGS   yLOG_char    ("prog"      , debug.prog);
   DEBUG_ARGS   yLOG_char    ("inpt"      , debug.inpt);
   DEBUG_ARGS   yLOG_char    ("INPT"      , debug.inptM);
   DEBUG_ARGS   yLOG_char    ("outp"      , debug.outp);
   DEBUG_ARGS   yLOG_char    ("OUTP"      , debug.outpM);
   DEBUG_ARGS   yLOG_char    ("loop"      , debug.loop);
   DEBUG_ARGS   yLOG_char    ("user"      , debug.user);
   DEBUG_ARGS   yLOG_char    ("apis"      , debug.apis);
   DEBUG_ARGS   yLOG_char    ("sign"      , debug.sign);
   DEBUG_ARGS   yLOG_char    ("scrp"      , debug.scrp);
   DEBUG_ARGS   yLOG_char    ("hist"      , debug.hist);
   DEBUG_ARGS   yLOG_char    ("graf"      , debug.graf);
   DEBUG_ARGS   yLOG_char    ("data"      , debug.data);
   DEBUG_ARGS   yLOG_char    ("envi"      , debug.envi);
   DEBUG_ARGS   yLOG_char    ("ENVI"      , debug.enviM);
   DEBUG_ARGS   yLOG_note    ("specialty urgents");
   DEBUG_ARGS   yLOG_char    ("color"     , debug.color);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] minimal pre-argument program initialization -----*/
PROG_init          (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           =    0;
   float       d           =  0.0;          /* degrees in tenths              */
   /*---(begin)--------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(globals)------------------------*/
   COLOR_init ();
   my.print       =  '-';
   my.space       =    0;
   my.explode     =  0.0;
   my.focus       = NULL;
   my.noempty     =  '-';
   my.hints       =  '-';
   my.ring        =  170;
   my.point       =   24;
   for (i = 0; i < MAX_RING; ++i) {
      my.thick [i] = my.ring * (1 + i);
   }
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
      else if (strcmp (a, "--color-white"       ) == 0)  COLOR_set_scheme (COLOR_WHITE);
      else if (strcmp (a, "--color-light"       ) == 0)  COLOR_set_scheme (COLOR_LIGHT);
      else if (strcmp (a, "--color-dark"        ) == 0)  COLOR_set_scheme (COLOR_DARK );
      else if (strcmp (a, "--color-black"       ) == 0)  COLOR_set_scheme (COLOR_BLACK);
      else if (strcmp (a, "--color-start"       ) == 0) {
         if (i + 1 < argc) if (atoi (argv [i + 1]) > 0 )  my.color_start = my.color   = atoi (argv[++i]);
      }
      else if (strcmp (a, "--color-chaos"       ) == 0)  my.chaos          = 'y';
      else if (strcmp (a, "--color-ordered"     ) == 0)  my.chaos          = '-';
      else if (strcmp (a, "--color-cutoff"      ) == 0) {
         if (i + 1 < argc) if (atof (argv [i + 1]) > 0 )  my.cutoff  = atof (argv[++i]);
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
   DRAW_globals ();
   for (i = 0; i < MAX_FORMAT; ++i) {
      if (g_formats [i].name [0] = '\0')      break;
      /*> my.cutoff     = g_formats [i].cutoff;                                         <*/
      my.point      = g_formats [i].point;
      my.ring       = g_formats [i].ring;
      my.thick [0]  = g_formats [i].l0;
      my.thick [1]  = g_formats [i].l1;
      my.thick [2]  = g_formats [i].l2;
      my.thick [3]  = g_formats [i].l3;
      my.thick [4]  = g_formats [i].l4;
      my.thick [5]  = g_formats [i].l5;
      my.thick [6]  = g_formats [i].l6;
      strcpy (my.tdesc, g_formats [i].tdesc);
      strcpy (my.fdesc, g_formats [i].fdesc);
      strcpy (my.label, g_formats [i].label);
      my.ghost      = g_formats [i].ghost;
      if (my.noempty == '-')  my.noempty    = g_formats [i].noempty;
   }
   if (my.thick [0] == 0)  my.thick [0] = my.ring;
   for (i = 1; i < 7; ++i) {
      x_cum = my.thick [i - 1] + my.ring;
      if (my.thick [i] == 0)  my.thick [i] = x_cum;
   }
   my.point     =   32;
   /*> my.thick [0] =  200;                                                           <* 
    *> my.thick [1] =  600;                                                           <* 
    *> my.thick [2] = 1200;                                                           <*/
   my.thick [0] =  200;
   my.thick [1] =  400;
   my.thick [2] =  600;
   my.thick [3] =  800;
   my.thick [4] = 1000;
   my.thick [5] = 1200;
   strcpy (my.tdesc, "7-level dirtree");
   strcpy (my.fdesc, "radial/sunburst");
   COLOR_filter ();
   NODE_init    ();
   DRAW_window_sizes ();
   yXINIT_start (my.w_title, my.w_wide, my.w_tall, YX_FOCUSABLE, YX_FIXED, YX_SILENT);
   /*> yGLTEX_free  ();                                                               <*/
   FONT_load    ();
   DRAW_init    ();
   DRAW_resize  (my.w_wide, my.w_tall);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS   yLOG_break   ();
   return 0;
}

char                /* PURPOSE : shutdown program and free memory ------------*/
PROG_end           (void)
{
   DEBUG_TOPS   yLOG_break   ();
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*> yGLTEX_free  ();                                                               <*/
   FONT_unload  ();
   yXINIT_end   ();
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS   yLOG_end     ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   helpers for unit testing                   ----===*/
/*====================------------------------------------====================*/
static void      o___TESTING_________________o (void) {;}

char       /*----: set up program urgents/debugging --------------------------*/
PROG_testquiet     (void)
{
   char       *x_args [1]  = { "hyleoroi" };
   PROG_urgs   (1, x_args);
   PROG_init   ();
   PROG_args   (1, x_args);
   /*> PROG_begin  ();                                                                <*/
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
PROG_testloud      (void)
{
   char       *x_args [3]  = { "hyleoroi", "@@log", "@@args"    };
   PROG_urgs   (3, x_args);
   PROG_init   ();
   PROG_args   (3, x_args);
   PROG_begin  ();
   return 0;
}



/*===============================[[ end-code ]]===============================*/
