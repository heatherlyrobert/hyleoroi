/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



#define     CENTER_FULL     'F'
#define     CENTER_HOLE     'E'

#define     TOOL_NODE       'n'

#define     LABEL_LABEL     'l'
#define     LABEL_DESC      'd'




tLAYER      g_layers       [MAX_FORMAT] = {
   /* ---name--------  ---description----------------------------   thick-  ---tool-------  ---tool------- */

   { "ctr-norm"      , "center circle, room for label"           ,  0.1667, TOOL_NODE     , LABEL_LABEL    },
   { "ctr-big"       , "center circle, much smaller"             ,  0.1500, TOOL_NODE     , LABEL_LABEL    },

   { "wdg-six"       , "six ring size wedge"                     ,  0.1667, TOOL_NODE     , LABEL_LABEL    },
   { "wdg-qtr"       , "three ring size wedge"                   ,  0.2500, TOOL_NODE     , LABEL_LABEL    },
   { "wdg-three"     , "three ring size wedge"                   ,  0.3333, TOOL_NODE     , LABEL_LABEL    },
   { "wdg-large"     , "three ring size wedge"                   ,  0.6000, TOOL_NODE     , LABEL_LABEL    },
   { "wdg-big"       , "two-thirds size wedge"                   ,  0.6667, TOOL_NODE     , LABEL_LABEL    },

   { ""              , "end-of-list"                             ,  0.0000, 0             , 0              },
};
int         g_nlayer       = 0;


tFORMAT     g_formats [MAX_FORMAT] = {
   /* ---name-------  ---format-------------  ---description----------------------------    -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  -1234567890-  lvl  ----------ring indexes----------------  ---------ring cums------------------------------  valid */
   {  "dir"         , "radial/sunburst"     , "six-levels of consitently-sized rings"   , { "ctr-norm"  , "wdg-six"   , "wdg-six"   , "wdg-six"   , "wdg-six"   , "wdg-six"   , ""          , ""          , ""          , ""          }, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  '-'  },
   {  "mime"        , "radial/sunburst"     , "three-levels, emphasizing outer layer"   , { "ctr-norm"  , "wdg-six"   , "wdg-big"   , ""          , ""          , ""          , ""          , ""          , ""          , ""          }, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  '-'  },
   {  "hermes"      , "radial/sunburst"     , "three-levels of consistently-sized rings", { "ctr-big"   , "wdg-qtr"   , "wdg-large" , ""          , ""          , ""          , ""          , ""          , ""          , ""          }, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  '-'  },
   {  ""            , "end-of-list"         , "end-of-list"                             , { ""          , ""          , ""          , ""          , ""          , ""          , ""          , ""          , ""          , ""          }, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  '-'  },
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
         g_formats [i].cums [j]   = x_cum;
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

/*> /+> my.cutoff     = g_formats [i].cutoff;                                         <+/    <* 
 *> my.point      = g_formats [i].point;                                                     <* 
 *> my.ring       = g_formats [i].ring;                                                      <* 
 *> my.thick [0]  = g_formats [i].l0;                                                        <* 
 *> my.thick [1]  = g_formats [i].l1;                                                        <* 
 *> my.thick [2]  = g_formats [i].l2;                                                        <* 
 *> my.thick [3]  = g_formats [i].l3;                                                        <* 
 *> my.thick [4]  = g_formats [i].l4;                                                        <* 
 *> my.thick [5]  = g_formats [i].l5;                                                        <* 
 *> my.thick [6]  = g_formats [i].l6;                                                        <* 
 *> strcpy (my.tdesc, g_formats [i].tdesc);                                                  <* 
 *> strcpy (my.fdesc, g_formats [i].fdesc);                                                  <* 
 *> strcpy (my.label, g_formats [i].label);                                                  <* 
 *> ++g_nformats;                                                                            <* 
 *> if (my.thick [0] == 0)  my.thick [0] = my.ring;                                          <* 
 *> for (i = 1; i < 7; ++i) {                                                                <* 
 *>    x_cum = my.thick [i - 1] + my.ring;                                                   <* 
 *>    if (my.thick [i] == 0)  my.thick [i] = x_cum;                                         <* 
 *> }                                                                                        <* 
 *> my.point     =   32;                                                                     <* 
 *> my.thick [0] =  200;                                                                     <* 
 *> my.thick [1] =  600;                                                                     <* 
 *> my.thick [2] = 1200;                                                                     <* 
 *> strcpy (my.tdesc, "3-level explosion");                                                  <* 
 *> /+> my.thick [0] =  200;                                                           <*    <* 
 *>  *> my.thick [1] =  400;                                                           <*    <* 
 *>  *> my.thick [2] =  600;                                                           <*    <* 
 *>  *> my.thick [3] =  800;                                                           <*    <* 
 *>  *> my.thick [4] = 1000;                                                           <*    <* 
 *>  *> my.thick [5] = 1200;                                                           <+/   <* 
 *> /+> strcpy (my.tdesc, "7-level dirtree");                                          <+/   <* 
 *> strcpy (my.fdesc, "radial/sunburst");                                                    <* 
 *> return 0;                                                                                <*/

char
FORMAT_dump_formats   (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         j           =    0;
   for (i = 0; i < g_nformat; ++i) {
      printf ("%-15.15s  %c  ", g_formats [i].name, g_formats [i].valid);
      for (j = 0; j < MAX_RING; ++j) {
         printf ("%6.3f  ", g_formats [i].cums [j]);
      }
      printf ("%1d\n", g_formats [i].levels);
   }
   return 0;
}

char
FORMAT_set         (char *a_name)
{
   int   i = 0;
   int  x_curr = 0;
   for (i = 0; i < MAX_RING; ++i) {
      my.thick [i] = 1200 * (i * 0.10);
   }
   x_curr = FORMAT_find_format (a_name);
   if (x_curr < 0) return -1;
   for (i = 0; i < MAX_RING; ++i) {
      my.thick [i] = 1200 * g_formats [x_curr].cums [i];
   }
   strlcpy (my.fdesc, g_formats [x_curr].format, 60);
   strlcpy (my.tdesc, g_formats [x_curr].desc  , 60);
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
