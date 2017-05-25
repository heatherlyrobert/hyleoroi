/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



#define     CENTER_FULL     'F'
#define     CENTER_HOLE     'E'

#define     TOOL_NODE       'n'

#define     LABEL_LABEL     'l'
#define     LABEL_DESC      'd'




tLAYER      g_layers       [MAX_FORMAT] = {
   /* ---name--------  ---description----------------------------   thick-  ---tool-------  ---label------ */

   { "ctr-norm"      , "center circle, room for label"           ,  0.1667, TOOL_NODE     , LABEL_LABEL    },
   { "ctr-big"       , "center circle, much smaller"             ,  0.1500, TOOL_NODE     , LABEL_LABEL    },

   { "wdg-six"       , "six ring size wedge"                     ,  0.1667, TOOL_NODE     , LABEL_LABEL    },
   { "wdg-qtr"       , "three ring size wedge"                   ,  0.2500, TOOL_NODE     , LABEL_LABEL    },
   { "wdg-three"     , "three ring size wedge"                   ,  0.3333, TOOL_NODE     , LABEL_LABEL    },
   { "wdg-large"     , "three ring size wedge"                   ,  0.6000, TOOL_NODE     , LABEL_LABEL    },
   { "wdg-desc"      , "two-thirds size wedge"                   ,  0.6667, TOOL_NODE     , LABEL_DESC     },

   { ""              , "end-of-list"                             ,  0.0000, 0             , 0              },
};
int         g_nlayer       = 0;


tFORMAT     g_formats [MAX_FORMAT] = {
   /* ---name-------  ---formal----------  ---format-------------  ---description----------------------------    -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  lvl  ----------ring indexes----------------  ---------ring cums------------------------------  ---labels---------------------------------------  hole  valid */
   {  "dirtree"     , "helios-dir"       , "radial/sunburst"     , "six-levels of consitently-sized rings"   , { "ctr-norm"  , "wdg-six"   , "wdg-six"   , "wdg-six"   , "wdg-six"   , "wdg-six"   , ""          , ""          , ""          , ""          }, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-',  '-',  '-'  },
   {  "mimecat"     , "helios-mime"      , "radial/sunburst"     , "three-levels, emphasizing outer layer"   , { "ctr-norm"  , "wdg-six"   , "wdg-desc"  , ""          , ""          , ""          , ""          , ""          , ""          , ""          }, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-',  '-',  '-'  },
   {  "exelocs"     , "hermes-locs"      , "radial/sunburst"     , "three-levels, emphasis on outer layer"   , { "ctr-big"   , "wdg-qtr"   , "wdg-large" , ""          , ""          , ""          , ""          , ""          , ""          , ""          }, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-',  'y',  '-'  },
   {  ""            , "end-of-list"      , "end-of-list"         , "end-of-list"                             , { ""          , ""          , ""          , ""          , ""          , ""          , ""          , ""          , ""          , ""          }, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-',  '-',  '-'  },
};
int         g_nformat      = 0;



/*====================------------------------------------====================*/
/*===----                         program level                        ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
FORMAT_init        (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         j           =    0;
   char        x_levels    =    0;
   char        x_valid     =    0;
   float       x_radius    =  0.0;
   float       x_cum       =  0.0;
   char        x_label     =  '-';
   /*---(prepare layers)-----------------*/
   g_nlayer    = 0;
   for (i = 0; i < MAX_FORMAT; ++i) {
      if (g_layers  [i].name [0] == '\0')      break;
      ++g_nlayer;
   }
   printf ("g_nlayer  = %d\n", g_nlayer);
   --rce;  if (g_layers <= 0)    return rce;
   /*---(prepare formats)----------------*/
   FORMAT_dump_formats ();
   g_nformat   = 0;
   x_valid     = 0;
   for (i = 0; i < MAX_FORMAT; ++i) {
      if (g_formats [i].name [0] == '\0')      break;
      ++g_nformat;
      x_levels = 0;
      x_cum    = 0.0;
      printf ("format %-15.15s\n", g_formats [i].name);
      for (j = 0; j < MAX_RING; ++j) {
         /*---(find layer)---------------*/
         rc = FORMAT_find_layer ( g_formats [i].layer_names [j]);
         printf ("   layer %1d %-15.15s %3d\n", j, g_formats [i].layer_names [j], rc);
         if (rc < 0) break;
         g_formats [i].layers [j] = rc;;
         /*---(get radius)---------------*/
         x_radius = FORMAT_get_radius (rc);
         if (x_radius <= 0.0) break;
         x_cum   += x_radius;
         g_formats [i].cums   [j]   = x_cum;
         x_label  = FORMAT_get_label  (rc);
         g_formats [i].labels [j]   = x_label;
         /*---(next layer)---------------*/
         ++x_levels;
      }
      if (x_levels <= 0)  continue;
      /*---(save)------------------------*/
      g_formats [i].levels = x_levels;
      g_formats [i].valid  = 'y';
      ++x_valid;
   }
   printf ("g_nformat = %d\n", g_nformat);
   FORMAT_dump_formats ();
   /*---(check for trouble)--------------*/
   --rce;  if (g_layers <= 0)    return rce;
   --rce;  if (x_valid  <= 0)    return rce;
   /*---(complete)-----------------------*/
   return 0;
}

char
FORMAT_dump_formats   (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         j           =    0;
   printf ("---name--------  v  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  l  -  -  -  -  -  -  -  -  -  -\n");
   for (i = 0; i < g_nformat; ++i) {
      printf ("%-15.15s  %c  ", g_formats [i].name, g_formats [i].valid);
      for (j = 0; j < MAX_RING; ++j) {
         printf ("%6.3f  ", g_formats [i].cums [j]);
      }
      printf ("%1d  ", g_formats [i].levels);
      for (j = 0; j < MAX_RING; ++j) {
         printf ("%c  ", g_formats [i].labels [j]);
      }
      printf ("\n");
   }
   return 0;
}

char
FORMAT_set         (char *a_name)
{
   int   i = 0;
   int  x_curr = 0;
   for (i = 0; i < MAX_RING; ++i) {
      my.ring_thick [i] = (int) (1200.0 * (i * 0.10));
      my.ring_label [i] = 'l';
   }
   x_curr = FORMAT_find_format (a_name);
   if (x_curr < 0) return -1;
   /*> printf ("setting %-15.15s  %2d  ", a_name, x_curr);                            <*/
   for (i = 0; i < MAX_RING; ++i) {
      my.ring_thick [i] = (int) (g_formats [x_curr].cums [i] * 1200.0);
      my.ring_label [i] = g_formats [x_curr].labels [i];
      /*> printf ("%6.3f(%c)  ", g_formats [x_curr].labels [i], g_formats [x_curr].cums   [i]);   <*/
      /*> printf ("%4d(%c)  "  , my.ring_thick [i], my.ring_label [i]);               <*/
   }
   /*> printf ("\n");                                                                 <*/
   strlcpy (my.fentry, g_formats [x_curr].name  , 60);
   strlcpy (my.fdesc , g_formats [x_curr].format, 60);
   strlcpy (my.tdesc , g_formats [x_curr].desc  , 60);
   my.hole  = g_formats [x_curr].hole;
   my.point = 32;
   return 0;
}

float
FORMAT_get_radius  (int a_layer)
{
   if (a_layer <  0       )  return 0.0;
   if (a_layer >= g_nlayer)  return 0.0;
   return g_layers [a_layer].radius;
}

char
FORMAT_get_label   (int a_layer)
{
   if (a_layer <  0       )  return 0.0;
   if (a_layer >= g_nlayer)  return 0.0;
   return g_layers [a_layer].label;
}

int
FORMAT_find_format (char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_name     == NULL)  return rce;
   --rce;  if (a_name [0] == '\0')  return rce;
   /*---(walk list)----------------------*/
   for (i = 0; i < g_nformat; ++i) {
      /*---(filter)----------------------*/
      if (g_formats [i].name[0] != a_name [0])       continue;
      if (strcmp (g_formats [i].name, a_name) != 0)  continue;
      /*---(found)-----------------------*/
      return i;
   }
   /*---(complete)-----------------------*/
   --rce;
   return rce;
}

int
FORMAT_find_layer  (char *a_name)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_name     == NULL)  return rce;
   --rce;  if (a_name [0] == '\0')  return rce;
   /*---(walk list)----------------------*/
   for (i = 0; i < g_nlayer; ++i) {
      /*---(filter)----------------------*/
      if (g_layers [i].name[0] != a_name [0])       continue;
      if (strcmp (g_layers [i].name, a_name) != 0)  continue;
      /*---(found)-----------------------*/
      return i;
   }
   /*---(complete)-----------------------*/
   --rce;
   return rce;
}


/*===============================[[ end-code ]]===============================*/
