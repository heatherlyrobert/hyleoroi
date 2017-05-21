/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */


tCOLOR      g_colors [400];
int         g_ncolor;
int         g_acolor;


static char s_scheme [400][10] =
{  /* colors taken from Tatarize at "godsnotwheregodsnot.ru" */

   "#000000", "#FFFF00", "#1CE6FF", "#FF34FF", "#FF4A46", "#008941", "#006FA6", "#A30059",
   "#FFDBE5", "#7A4900", "#0000A6", "#63FFAC", "#B79762", "#004D43", "#8FB0FF", "#997D87",
   "#5A0007", "#809693", "#FEFFE6", "#1B4400", "#4FC601", "#3B5DFF", "#4A3B53", "#FF2F80",
   "#61615A", "#BA0900", "#6B7900", "#00C2A0", "#FFAA92", "#FF90C9", "#B903AA", "#D16100",
   "#DDEFFF", "#000035", "#7B4F4B", "#A1C299", "#300018", "#0AA6D8", "#013349", "#00846F",
   "#372101", "#FFB500", "#C2FFED", "#A079BF", "#CC0744", "#C0B9B2", "#C2FF99", "#001E09",
   "#00489C", "#6F0062", "#0CBD66", "#EEC3FF", "#456D75", "#B77B68", "#7A87A1", "#788D66",
   "#885578", "#FAD09F", "#FF8A9A", "#D157A0", "#BEC459", "#456648", "#0086ED", "#886F4C",

   "#34362D", "#B4A8BD", "#00A6AA", "#452C2C", "#636375", "#A3C8C9", "#FF913F", "#938A81",
   "#575329", "#00FECF", "#B05B6F", "#8CD0FF", "#3B9700", "#04F757", "#C8A1A1", "#1E6E00",
   "#7900D7", "#A77500", "#6367A9", "#A05837", "#6B002C", "#772600", "#D790FF", "#9B9700",
   "#549E79", "#FFF69F", "#201625", "#72418F", "#BC23FF", "#99ADC0", "#3A2465", "#922329",
   "#5B4534", "#FDE8DC", "#404E55", "#0089A3", "#CB7E98", "#A4E804", "#324E72", "#6A3A4C",
   "#83AB58", "#001C1E", "#D1F7CE", "#004B28", "#C8D0F6", "#A3A489", "#806C66", "#222800",
   "#BF5650", "#E83000", "#66796D", "#DA007C", "#FF1A59", "#8ADBB4", "#1E0200", "#5B4E51",
   "#C895C5", "#320033", "#FF6832", "#66E1D3", "#CFCDAC", "#D0AC94", "#7ED379", "#012C58",

   "#7A7BFF", "#D68E01", "#353339", "#78AFA1", "#FEB2C6", "#75797C", "#837393", "#943A4D",
   "#B5F4FF", "#D2DCD5", "#9556BD", "#6A714A", "#001325", "#02525F", "#0AA3F7", "#E98176",
   "#DBD5DD", "#5EBCD1", "#3D4F44", "#7E6405", "#02684E", "#962B75", "#8D8546", "#9695C5",
   "#E773CE", "#D86A78", "#3E89BE", "#CA834E", "#518A87", "#5B113C", "#55813B", "#E704C4",
   "#00005F", "#A97399", "#4B8160", "#59738A", "#FF5DA7", "#F7C9BF", "#643127", "#513A01",
   "#6B94AA", "#51A058", "#A45B02", "#1D1702", "#E20027", "#E7AB63", "#4C6001", "#9C6966",
   "#64547B", "#97979E", "#006A66", "#391406", "#F4D749", "#0045D2", "#006C31", "#DDB6D0",
   "#7C6571", "#9FB2A4", "#00D891", "#15A08A", "#BC65E9", "#FFFFFE", "#C6DC99", "#203B3C",

   "#671190", "#6B3A64", "#F5E1FF", "#FFA0F2", "#CCAA35", "#374527", "#8BB400", "#797868",
   "#C6005A", "#3B000A", "#C86240", "#29607C", "#402334", "#7D5A44", "#CCB87C", "#B88183",
   "#AA5199", "#B5D6C3", "#A38469", "#9F94F0", "#A74571", "#B894A6", "#71BB8C", "#00B433",
   "#789EC9", "#6D80BA", "#953F00", "#5EFF03", "#E4FFFC", "#1BE177", "#BCB1E5", "#76912F",
   "#003109", "#0060CD", "#D20096", "#895563", "#29201D", "#5B3213", "#A76F42", "#89412E",
   "#1A3A2A", "#494B5A", "#A88C85", "#F4ABAA", "#A3F3AB", "#00C6C8", "#EA8B66", "#958A9F",
   "#BDC9D2", "#9FA064", "#BE4700", "#658188", "#83A485", "#453C23", "#47675D", "#3A3F00",
   "#061203", "#DFFB71", "#868E7E", "#98D058", "#6C8F7D", "#D7BFC2", "#3C3E6E", "#D83D66",

   "#2F5D9B", "#6C5E46", "#D25B88", "#5B656C", "#00B57F", "#545C46", "#866097", "#365D25",
   "#252F99", "#00CCFF", "#674E60", "#FC009C", "#92896B", "-------", "-------", "-------",
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
   "-------", "-------", "-------", "-------", "-------", "-------", "-------", "-------", 
};



/*====================------------------------------------====================*/
/*===----                        overall program                       ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
COLOR_init         (void)
{
   COLOR_set_scheme (COLOR_WHITE);
   my.chaos       =  '-';
   my.color       =    0;
   my.color_start =    0;
   my.color_seed  =    1;
   return 0;
}

char
COLOR_wrap         (void)
{
   return 0;
}

int
COLOR_count        (void)
{
   return g_acolor;
}



/*====================------------------------------------====================*/
/*===----                        general/support                       ----===*/
/*====================------------------------------------====================*/
static void      o___GENERAL_________________o (void) {;}

float
COLOR_unhex         (char a_one, char a_two)
{
   float       x_one       = 0.0;
   float       x_two       = 0.0;
   if      (a_one >= '0' && a_one <= '9')   x_one = a_one - '0';
   else if (a_one >= 'a' && a_one <= 'f')   x_one = a_one - 'a' + 10;
   else if (a_one >= 'A' && a_one <= 'F')   x_one = a_one - 'A' + 10;
   else                                     x_one = 0.0;
   if      (a_two >= '0' && a_two <= '9')   x_two = a_two - '0';
   else if (a_two >= 'a' && a_two <= 'f')   x_two = a_two - 'a' + 10;
   else if (a_two >= 'A' && a_two <= 'F')   x_two = a_two - 'A' + 10;
   else                                     x_two = 0.0;
   return ((x_one * 16.0) + x_two) / 255;
}



/*====================------------------------------------====================*/
/*===----                       filtering/selecting                    ----===*/
/*====================------------------------------------====================*/
static void      o___FILTERING_______________o (void) {;}

char
COLOR_filter       (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   float       x_red       = 0.0;
   float       x_grn       = 0.0;
   float       x_blu       = 0.0;
   float       x_bri       = 0.0;
   /*---(header)-------------------------*/
   DEBUG_COLOR  yLOG_enter   (__FUNCTION__);
   DEBUG_COLOR  yLOG_note    ("set global values");
   g_ncolor        =    0;
   g_acolor        =    0;
   my.color        =    0;
   if (my.chaos == 'y') {
      if (my.color_start == 0)  my.color_seed  = my.color_start = 1;
      else                      my.color_seed  = my.color_start;
   }
   /*---(establish values)---------------*/
   for (i = 0; i < 400; ++i) {
      /*---(filter)----------------------*/
      if (s_scheme [i][0] == '-')  break;
      /*---(read scheme)-----------------*/
      x_red =  COLOR_unhex (s_scheme [i][1], s_scheme [i][2]);
      x_grn =  COLOR_unhex (s_scheme [i][3], s_scheme [i][4]);
      x_blu =  COLOR_unhex (s_scheme [i][5], s_scheme [i][6]);
      x_bri =  x_red + x_grn + x_blu;
      ++g_acolor;
      /*---(filter)----------------------*/
      if (my.cutoff  > 1.5 && x_bri > my.cutoff) {
         DEBUG_COLOR  yLOG_complex ("skipped"   , "%3d, red=%4.2f, grn=%4.2f, blu=%4.2f, bri=%4.2f", g_acolor, x_red, x_grn, x_blu, x_bri);
         continue;
      }
      if (my.cutoff <= 1.5 && x_bri < my.cutoff) {
         DEBUG_COLOR  yLOG_complex ("skipped"   , "%3d, red=%4.2f, grn=%4.2f, blu=%4.2f, bri=%4.2f", g_acolor, x_red, x_grn, x_blu, x_bri);
         continue;
      }
      /*---(save to palette)-------------*/
      g_colors [g_ncolor].red = x_red;
      g_colors [g_ncolor].grn = x_grn;
      g_colors [g_ncolor].blu = x_blu;
      g_colors [g_ncolor].bri = x_bri;
      ++g_ncolor;
      DEBUG_COLOR  yLOG_complex ("saved"     , "%3d, red=%4.2f, grn=%4.2f, blu=%4.2f, bri=%4.2f, new=%3d", g_acolor, x_red, x_grn, x_blu, x_bri, g_ncolor);
      /*---(done)------------------------*/
   }
   /*---(summary)------------------------*/
   DEBUG_COLOR  yLOG_value   ("g_acolor", g_acolor);
   DEBUG_COLOR  yLOG_value   ("g_ncolor"   , g_ncolor);
   /*---(complete)-----------------------*/
   DEBUG_COLOR  yLOG_exit    (__FUNCTION__);
   return 0;
}

int
COLOR_selected     (void)
{
   return g_ncolor;
}



/*====================------------------------------------====================*/
/*===----                        color setting                         ----===*/
/*====================------------------------------------====================*/
static void      o___SETTING_________________o (void) {;}

char
COLOR_set_scheme   (char a_scheme)
{
   switch (a_scheme) {
   case COLOR_BLACK :
      my.scheme = COLOR_BLACK;
      my.cutoff  = 0.7;
      break;
   case COLOR_DARK  :
      my.scheme = COLOR_DARK;
      my.cutoff  = 1.2;
      break;
   case COLOR_LIGHT :
      my.scheme = COLOR_LIGHT;
      my.cutoff  = 1.7;
      break;
   default          :
   case COLOR_WHITE :
      my.scheme = COLOR_WHITE;
      my.cutoff  = 2.3;
      break;
   }
   return 0;
}

/*> float       s_rstart    = 25.0;                                                   <* 
 *> float       s_rinc      = 90.0;                                                   <*/
float       s_rstart    =  10.0;
float       s_rinc      = 180.0;
float       s_explode   =   1.1;

char         /*===[[ set the foreground color ]]==========[ leaf   [ ------ ]=*/
COLOR_fore         (void)
{
   switch (my.scheme) {
   case  'w' :
   case  'l' :
      glColor4f (0.0f, 0.0f, 0.0f, 1.0f);
      break;
   case  'd' :
   case  'b' :
      glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
      break;
   }
   if (debug.tops == 'y')  glColor4f (1.0f, 0.0f, 0.0f, 1.0f);
   return 0;
}

char         /*===[[ set the background color ]]==========[ leaf   [ ------ ]=*/
COLOR_back         (void)
{
   switch (my.scheme) {
   case  'w' : glClearColor  (1.0f, 1.0f, 1.0f, 1.0f);   /* white */
               glColor4f     (1.0f, 1.0f, 1.0f, 1.0f);   /* white */
               break;
   case  'l' : glClearColor  (0.6f, 0.6f, 0.6f, 1.0f);   /* light */
               glColor4f     (0.6f, 0.6f, 0.6f, 1.0f);   /* light */
               break;
   case  'd' : glClearColor  (0.2f, 0.2f, 0.2f, 1.0f);   /* dark  */
               glColor4f     (0.2f, 0.2f, 0.2f, 1.0f);   /* dark  */
               break;
   case  'b' : glClearColor  (0.0f, 0.0f, 0.0f, 1.0f);   /* black */
               glColor4f     (0.0f, 0.0f, 0.0f, 1.0f);   /* black */
               break;
   }
   return 0;
}

char         /*--: set the node color --------------------[ leaf   [ ------ ]-*/
COLOR_node         (tNODE *a_node)
{
   glColor4f (g_colors [a_node->color].red, g_colors [a_node->color].grn, g_colors [a_node->color].blu, 1.00);
   return 0;
}

char         /*--: set the node color --------------------[ leaf   [ ------ ]-*/
COLOR_label        (tNODE *a_node, char a_style)
{
   if (a_style == 'h')
      glColor4f   (1.0f, 1.0f, 1.0f, 1.0f);
   else if (g_colors [a_node->color].bri < 0.8)    /* was 1.5  */
      glColor4f   (1.0f, 1.0f, 1.0f, 1.0f);
   else  
      glColor4f   (0.0f, 0.0f, 0.0f, 1.0f);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                        color cursor                          ----===*/
/*====================------------------------------------====================*/
static void      o___CURSOR__________________o (void) {;}

int
COLOR_next         (void)
{
   int         x_color     = 0;
   if (my.chaos == 'y') {
      x_color  = rand_r (&(my.color_seed)) % g_ncolor;
   } else {
      if (my.color >= g_ncolor)  my.color -= g_ncolor;
      x_color  = my.color;
      ++my.color;
   }
   return x_color;
}


/*===============================[[ end-code ]]===============================*/
