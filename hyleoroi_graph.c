/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



/*---(window)----------------------------*/

/*---(sizes)-----------------------------*/

/*---(opengl objects)--------------------*/
uint        s_tex       =     0;            /* texture for image              */
uint        s_fbo       =     0;            /* framebuffer                    */
uint        s_depth     =     0;            /* depth buffer                   */

/*---(fonts)--------------------------*/
char       *face_sm     = "verdana_sm";
char       *face_bg     = "verdana";
int         txf_sm;
int         txf_bg;

tCOLOR      g_colors [400];
int         g_ncolor;
int         n_all_color;


char        scheme [400][10] =
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

char
DRAW_window_sizes  (void)
{
   /*---(header)----------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(window configuration)-----------*/
   strlcpy (my.w_title, "arachne", LEN_STR);
   /*---(widths)-------------------------*/
   DEBUG_TOPS   yLOG_note    ("set window/panel widths");
   strcpy (my.w_title, "hyleoroi -- tree data structure visualization");
   my.t_wide       =  100;
   my.m_wide       =  700;
   my.a_wide       =  150;
   my.c_wide       = my.m_wide + my.a_wide;
   my.w_wide       = my.t_wide + my.c_wide;
   /*---(lefts)--------------------------*/
   DEBUG_TOPS   yLOG_note    ("set window/panel left positions");
   my.t_left       =  0;
   my.m_left       = my.c_left = my.t_wide;
   my.a_left       = my.m_left + my.m_wide;
   /*---(talls)--------------------------*/
   DEBUG_TOPS   yLOG_note    ("set window/panel heights");
   my.m_tall       =  700;
   my.c_tall       =   20;
   my.a_tall       = my.m_tall;
   my.w_tall       = my.t tall = my.m_tall + my.c_tall.
   /*---(bottoms)------------------------*/
   DEBUG_TOPS   yLOG_note    ("set window/panel bottom positions");
   my.t_bott       = my.c_bott =   0;  
   my.m_bott       = my.a_bott = my.c_tall;
   /*---(complete)--------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                       graphics preparation                   ----===*/
/*====================------------------------------------====================*/
static void      o___ONE_TIME________________o (void) {;}

float
DRAW_unhex         (char a_one, char a_two)
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

char         /*===[[ set global drawing values ]]=========[ leaf   [ ------ ]=*/
DRAW_globals       (void)
{
   /*---(heading)------------------------*/
   DEBUG_COLOR  yLOG_enter   (__FUNCTION__);
   int         i           =    0;
   float       x_bright    =  0.0;
   /*---(set globals)--------------------*/
   yLOG_snote   ("title");
   my.tex_h        = 2400;
   my.tex_w        = 2400;
   yLOG_snote   ("action");
   my.single       =  0.0;
   my.angle        =  0.0;
   my.inc          = PLAY;
   my.action       =    1;
   yLOG_snote   ("coordinates");
   my.xdist        =  0.0;
   my.ydist        =  0.0;
   my.zdist        =  400;
   yLOG_snote   ("colors");
   g_ncolor         =    0;
   n_all_color     =    0;
   DEBUG_COLOR  yLOG_note    ("adding colors from scheme");
   DEBUG_COLOR  yLOG_complex ("my.cutoff" , "%4.2f", my.cutoff);
   for (i = 0; i < 400; ++i) {
      if (scheme [i][0] == '-')  break;
      g_colors [g_ncolor].red = DRAW_unhex (scheme [i][1], scheme [i][2]);
      g_colors [g_ncolor].grn = DRAW_unhex (scheme [i][3], scheme [i][4]);
      g_colors [g_ncolor].blu = DRAW_unhex (scheme [i][5], scheme [i][6]);
      x_bright = g_colors [g_ncolor].red + g_colors [g_ncolor].grn + g_colors [g_ncolor].blu;
      g_colors [g_ncolor].bri = x_bright;
      ++n_all_color;
      DEBUG_COLOR  yLOG_complex ("color"     , "red=%4.2f, grn=%4.2f, blu=%4.2f, bri=%4.2f", g_colors [g_ncolor].red, g_colors [g_ncolor].grn, g_colors [g_ncolor].blu, x_bright);
      if (my.cutoff  > 1.5 && x_bright > my.cutoff) {
         DEBUG_COLOR  yLOG_note    ("skipped");
         continue;
      }
      if (my.cutoff <= 1.5 && x_bright < my.cutoff) {
         DEBUG_COLOR  yLOG_note    ("skipped");
         continue;
      }
      ++g_ncolor;
   }
   DEBUG_COLOR  yLOG_value   ("g_ncolor"   , g_ncolor);
   /*---(complete)-----------------------*/
   DEBUG_COLOR  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ initialize graphics settings ]]======[ leaf   [ ------ ]=*/
DRAW_init          (void)
{
   /*---(header)-------------------------*/
   yLOG_senter  (__FUNCTION__);
   /*---(color)--------------------------*/
   yLOG_snote   ("color");
   DRAW__color_back  ();
   glClearDepth  (1.0f);
   /*---(textures)-----------------------*/
   yLOG_snote   ("texture");
   glShadeModel  (GL_SMOOTH);
   glEnable      (GL_TEXTURE_2D);            /* NEW */
   /*---(blending)-----------------------*/
   yLOG_snote   ("blending");
   glEnable      (GL_DEPTH_TEST);
   glEnable      (GL_ALPHA_TEST);
   glAlphaFunc   (GL_GEQUAL, 0.0125);
   /*> glAlphaFunc   (GL_GEQUAL, 0.0625);                                             <*/
   glEnable      (GL_BLEND);
   glBlendFunc   (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   /*---(anti-aliasing)------------------*/
   yLOG_snote   ("antialias" );
   glHint        (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
   glEnable      (GL_POLYGON_SMOOTH);
   glHint        (GL_POLYGON_SMOOTH_HINT, GL_NICEST);
   /*---(simple defaulting)--------------*/
   yLOG_snote   ("detault" );
   glLineWidth     (0.50f);
   /*---(flush)--------------------------*/
   yLOG_snote   ("flush" );
   glFlush       ();
   DRAW_resize   ( 10, 10);
   /*---(complete)-----------------------*/
   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   heatherly font handling                    ----===*/
/*====================------------------------------------====================*/
static void      o___FONTS___________________o (void) {;}

char
FONT_load          (void)
{
   txf_sm = yFONT_load (face_sm);
   if (txf_sm < 0) {
      fprintf(stderr, "Problem loading %s\n", face_sm);
      exit(1);
   }
   txf_bg = yFONT_load (face_bg);
   if (txf_bg < 0) {
      fprintf(stderr, "Problem loading %s\n", face_bg);
      exit(1);
   }
   return 0;
}

char
FONT_unload        (void)
{
   yFONT_free (txf_sm);
   yFONT_free (txf_bg);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      texture drawing                         ----===*/
/*====================------------------------------------====================*/
static void      o___TEXTURE_________________o (void) {;}

char         /*===[[ create texture for drawing ]]========[ leaf   [ ------ ]=*/
TEX_create         (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(generate)-----------------------*/
   glGenFramebuffersEXT         (1, &s_fbo);
   DEBUG_GRAF   yLOG_value   ("s_fbo"     , s_fbo);
   glGenTextures                (1, &s_tex);
   DEBUG_GRAF   yLOG_value   ("s_tex"     , s_tex);
   glGenRenderbuffersEXT        (1, &s_depth);
   DEBUG_GRAF   yLOG_value   ("s_depth"   , s_depth);
   /*---(bind)---------------------------*/
   DEBUG_GRAF   yLOG_info    ("bind"      , "s_fbo framebuffer and s_tex texture");
   glBindFramebufferEXT         (GL_FRAMEBUFFER_EXT,  s_fbo);
   glBindTexture                (GL_TEXTURE_2D,       s_tex);
   /*---(settings)-----------------------*/
   DEBUG_GRAF   yLOG_info    ("settings"  , "filters, wraps, and mipmaps");
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri              (GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexEnvi                    (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glTexParameteri              (GL_TEXTURE_2D,  GL_GENERATE_MIPMAP, GL_TRUE);
   /*---(copy)---------------------------*/
   DEBUG_GRAF   yLOG_info    ("copy"      , "glTexImage2D and Framebuffer");
   glTexImage2D                 (GL_TEXTURE_2D, 0, GL_RGBA, my.tex_w, my.tex_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
   glFramebufferTexture2DEXT    (GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, s_tex, 0);
   /*---(depth)--------------------------*/
   DEBUG_GRAF   yLOG_info    ("bind"      , "s_depth depth buffer");
   glBindRenderbufferEXT        (GL_RENDERBUFFER_EXT, s_depth);
   glRenderbufferStorageEXT     (GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, my.tex_w, my.tex_h);
   glFramebufferRenderbufferEXT (GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, s_depth);
   /*---(unbind)-------------------------*/
   DEBUG_GRAF   yLOG_info    ("unbind"    , "s_fbo framebuffer");
   glBindFramebufferEXT         (GL_FRAMEBUFFER_EXT, 0);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ release texture ]]===================[ leaf   [ ------ ]=*/
TEX_free           (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(generate)-----------------------*/
   glDeleteTextures             (1, &s_tex);
   DEBUG_GRAF   yLOG_value   ("s_tex"     , s_tex);
   glDeleteRenderbuffersEXT     (1, &s_depth);
   DEBUG_GRAF   yLOG_value   ("s_depth"   , s_depth);
   glDeleteFramebuffersEXT      (1, &s_fbo);
   DEBUG_GRAF   yLOG_value   ("s_fbo"     , s_fbo);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        color setting                         ----===*/
/*====================------------------------------------====================*/
static void      o___COLORS__________________o (void) {;}

/*> float       s_rstart    = 25.0;                                                   <* 
 *> float       s_rinc      = 90.0;                                                   <*/
float       s_rstart    =  10.0;
float       s_rinc      = 180.0;
float       s_explode   =   1.1;

char         /*===[[ set the foreground color ]]==========[ leaf   [ ------ ]=*/
DRAW__color_fore   ()
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
   return 0;
}

char         /*===[[ set the background color ]]==========[ leaf   [ ------ ]=*/
DRAW__color_back   ()
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
DRAW__color_node     (tNODE *a_node)
{
   glColor4f (g_colors [a_node->color].red, g_colors [a_node->color].grn, g_colors [a_node->color].blu, 1.00);
   return 0;
}

char         /*--: set the node color --------------------[ leaf   [ ------ ]-*/
DRAW__color_text     (tNODE *a_node, char a_style)
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
/*===----                        radial shapes                         ----===*/
/*====================------------------------------------====================*/
static void      o___RADIAL__________________o (void) {;}

static int   s_beg      =    0;     /* horizontal beginning for shape   */
static float s_cen      =  0.0;     /* horizontal placement for text    */
static int   s_end      =    0;     /* horizontal ending    for shape   */
static int   s_top      =    0;     /* vertical   beginning for shape   */
static float s_mid      =  0.0;     /* vertical   placement for text    */
static int   s_bot      =    0;     /* vertical   ending    for shape   */

char         /*-> establish drawing outline --------------[ leaf   [ ------ ]-*/
DRAW__radial_vals    (tNODE *a_node)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_node == NULL) {
      DEBUG_GRAF   yLOG_snote   ("a_node null");
      DEBUG_GRAF   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(set node values)----------------*/
   s_beg   = 0;
   s_end   = my.thick [a_node->level];
   s_top   = a_node->beg * 10;
   s_bot   = a_node->end * 10;
   /*---(text placement)-----------------*/
   s_mid   = ((float) s_top / 10.0) + ((float) (s_bot - s_top)) / (2.0 * 10.0);
   if (a_node->level == 0)  s_mid   =  0.0;
   else                     s_mid   = -(s_mid) + 90.0;
   if (a_node->level == 0)  s_cen   =  0.0;
   else                     s_cen   = my.thick [a_node->level - 1] + 10.0;
   /*---(report)-------------------------*/
   DEBUG_GRAF   yLOG_svalue  ("s_beg/in"  , s_beg);
   DEBUG_GRAF   yLOG_svalue  ("s_end/out" , s_end);
   DEBUG_GRAF   yLOG_svalue  ("s_top/beg" , s_top);
   DEBUG_GRAF   yLOG_svalue  ("s_bot/end" , s_bot);
   DEBUG_GRAF   yLOG_complex ("s_mid"     , "%8.3f", s_mid);
   DEBUG_GRAF   yLOG_complex ("s_cen"     , "%8.3f", s_cen);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> draw an outline only -------------------[ ------ [ ------ ]-*/
DRAW__radial_empty   (tNODE *a_node, char a_type)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   float       x           =  0.0;          /* x_coordinate                   */
   float       y           =  0.0;          /* y_coordinate                   */
   int         i           =    0;          /* loop iterator -- deg tenths    */
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(set values)---------------------*/
   rc = DRAW__radial_vals  (a_node);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set defaults)-------------------*/
   if (a_type == 's') {
      glLineWidth (my.space);
      DRAW__color_back ();
   } else {
      glLineWidth (1);
      glColor4f ( 0.25,  0.25, 0.25, 1.00);
   }
   /*---(draw)---------------------------*/
   glBegin (GL_LINES); {
      /*---(curved outer)----------------*/
      DEBUG_GRAF   yLOG_snote   ("outer curve");
      for (i = s_top; i <= s_bot; i +=  5) {
         x   = s_end  * my_sin [i];
         y   = s_end  * my_cos [i];
         /*> DEBUG_GRAF   yLOG_complex ("coord"     , "x=%8.3f, y=%8.3f", x, y);      <*/
         glVertex3f ( x, y, 0.0f);
      }
      /*---(final point)-----------------*/
      x   = s_end  * my_sin [s_bot];
      y   = s_end  * my_cos [s_bot];
      /*> DEBUG_GRAF   yLOG_complex ("coord"     , "x=%8.3f, y=%8.3f", x, y);         <*/
      glVertex3f ( x, y, 0.0f);
   } glEnd();
   /*---(complete)----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ draw a single wedge ]]===============[ leaf   [ ------ ]=*/
DRAW__radial_full    (tNODE *a_node)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   float       x           = 0.0;           /* x_coordinate                   */
   float       y           = 0.0;           /* y_coordinate                   */
   int         i           =   0;           /* loop iterator -- deg tenths    */
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(set values)---------------------*/
   rc = DRAW__radial_vals  (a_node);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(draw)---------------------------*/
   DRAW__color_node  (a_node);
   glBegin (GL_POLYGON); {
      /*---(set level)-------------------*/
      glTranslatef ( 0.0,  0.0, - (a_node->level * 20));
      /*---(first side)------------------*/
      DEBUG_GRAF   yLOG_snote   ("first side");
      glVertex3f ( 0, 0, 0.0f);
      x   = s_end  * my_sin [s_top];
      y   = s_end  * my_cos [s_top];
      /*> DEBUG_GRAF   yLOG_complex ("coord"     , "x=%8.3f, y=%8.3f", x, y);         <*/
      glVertex3f ( x, y, 0.0f);
      /*---(curved outer)----------------*/
      DEBUG_GRAF   yLOG_snote   ("outer curve");
      for (i = s_top; i <= s_bot; i += 50) {
         x   = s_end  * my_sin [i];
         y   = s_end  * my_cos [i];
         /*> DEBUG_GRAF   yLOG_complex ("coord"     , "x=%8.3f, y=%8.3f", x, y);      <*/
         glVertex3f ( x, y, 0.0f);
      }
      /*---(second side)-----------------*/
      DEBUG_GRAF   yLOG_snote   ("second side");
      x   = s_end  * my_sin [s_bot];
      y   = s_end  * my_cos [s_bot];
      /*> DEBUG_GRAF   yLOG_("coord"     , "x=%8.3f, y=%8.3f", x, y);         <*/
      glVertex3f ( x, y, 0.0f);
      /*---(back to home)----------------*/
      glVertex3f ( 0, 0, 0.0f);
      /*---(done)------------------------*/
   } glEnd();
   /*---(complete)----------------------*/
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*===[[ draw a single wedge ]]===============[ leaf   [ ------ ]=*/
DRAW__radial_text    (tNODE *a_node, char a_style)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_text      [100] = "";
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_node->label [0] == '-')    return rce;
   --rce;
   if      (a_node->level  > 7  ) {
      if   (a_node->width <= 1.0)   return  rce;
   }
   else if (a_node->level  > 4  ) {
      if   (a_node->width <= 1.5)   return  rce;
   }
   else if (a_node->level <= 4  ) {
      if   (a_node->width <= 2.0)   return  rce;
   }
   /*---(draw text)----------------------*/
   glPushMatrix(); {
      DRAW__color_text   (a_node, a_style);
      glRotatef   (s_mid, 0.0, 0.0, 1.0);
      glTranslatef(s_cen, 0.0, 0.0);
      if (my.hints == 'y') { 
         glTranslatef(-s_cen, 0.0, 0.0);
         glRotatef   (-2.0, 0.0, 0.0, 1.0);
         glTranslatef(s_cen, 0.0, 0.0);
         yFONT_print (txf_bg, my.point, YF_MIDLEF, a_node->label);
         glTranslatef(-s_cen, 0.0, 0.0);
         /*> glRotatef   (1.0 + (6.0 - a_node->level) * 1.0, 0.0, 0.0, 1.0);    <*/
         glRotatef   (+6.0 - (a_node->level * 0.8), 0.0, 0.0, 1.0);
         glTranslatef(s_cen, 0.0, 0.0);
         yFONT_print (txf_bg, my.point, YF_MIDLEF, a_node->hint);
         /*> sprintf (x_text, "%s.%s", a_node->hint, a_node->label);            <* 
          *> yFONT_print (txf_bg, 12, YF_MIDLEF, x_text);                       <*/
      } else {
         if (a_node->level == 0)
            yFONT_print (txf_bg, my.point, YF_MIDCEN, a_node->name );
         else 
            if (my.type   == 'm') yFONT_print (txf_bg, my.point, YF_MIDLEF, a_node->desc);
            else                  yFONT_print (txf_bg, my.point, YF_MIDLEF, a_node->name);
      }
   } glPopMatrix();
   /*---(complete)----------------------*/
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       actual drawing                         ----===*/
/*====================------------------------------------====================*/
static void      o___DRAWING_________________o (void) {;}

char         /*===[[ draw a single wedge ]]===============[ leaf   [ ------ ]=*/
DRAW_node          (
      /*---(formal parameters)+-------------+---------------------------------*/
      int         a_level      ,            /* recursion/hierarchy level      */
      tNODE      *a_node      ,             /* node to draw                   */
      char        a_style     )             /* node to draw                   */
{  /*---(design notes)-------------------*/
   /*
    *  a_style : 'o' == outline, 'h' == home, '-' = normal
    *
    */
   /*---(local variables)--+-----------+-*/
   char        x_ghost     = '-';
   /*---(defense)------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   if (a_node == NULL) {
      DEBUG_GRAF   yLOG_note    ("a_node null");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return -1;
   }
   if (a_node->name [0] == '-')  x_ghost = 'y';
   if (x_ghost == 'y' && my.ghost != 'y') {
      DEBUG_GRAF   yLOG_note    ("skipping ghost");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return -1;
   }
   /*---(draw)---------------------------*/
   glPushMatrix(); {
      if (x_ghost != 'y')  DRAW__radial_full   (a_node);
      else                 DRAW__radial_empty  (a_node, 'g');
      if (my.space != 0 && x_ghost != 'y') {
         if (a_node->nchild > 0)  DRAW__radial_empty (a_node, 's');
      }
      if (a_style != 'w' && a_style != 'o') {
         DRAW__radial_text (a_node, a_style);
      }
   } glPopMatrix();
   /*---(complete)----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ draw a level of wedges ]]============[ ------ [ ------ ]=*/
DRAW_level         (
      /*---(formal parameters)+-------------+---------------------------------*/
      int        a_level      ,             /* recursion/hierarchy level      */
      tNODE     *a_first      ,             /* first sibling in list          */
      char       a_recurse    )             /* (y/-) recurse into children    */

{  /*---(local variables)--+-----------+-*/
   tNODE      *x_curr      = NULL;
   char        rce         =  -10;
   tNODE      *x_last      = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_value   ("a_level"   , a_level);
   /*---(defense)------------------------*/
   --rce;  if (a_first == NULL) {
      DEBUG_GRAF   yLOG_warn    ("a_first NULL"   ,  "can not process");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(process siblings)---------------*/
   x_curr = x_last = a_first;
   while (x_curr != NULL) {
      DEBUG_GRAF   yLOG_info    ("current"   , x_curr->name);
      if (a_recurse == 'y' && x_curr->nchild != 0) {
         DRAW_level (a_level + 1, x_curr->sib_head, a_recurse);
      }
      DRAW_node    (a_level, x_curr, '-');
      x_last = x_curr;
      x_curr = x_curr->sib_next;
   }
   /*---(check for empty space)----------*/
   /*---(complete)-------------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] draw the texture contents -----------------------*/
TEX_draw           (void)
{  /*---(locals)-----------+-----------+-*/
   float       x_width     = my.tex_w  / 2.0;
   float       x_height    = my.tex_h  / 2.0;
   tNODE      *x_base      = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(create objects)-----------------*/
   DEBUG_GRAF   yLOG_note    ("texture handling");
   TEX_free              ();
   TEX_create            ();
   /*---(setup)--------------------------*/
   DEBUG_GRAF   yLOG_note    ("set for texture drawing");
   glViewport            (0.0,  0.0, my.tex_w, my.tex_h);
   glMatrixMode          (GL_PROJECTION);
   glLoadIdentity        ();
   glOrtho               (  -x_width,   x_width,  -x_height,   x_height, -500.0,  500.0);
   glMatrixMode          (GL_MODELVIEW);
   glBindTexture         (GL_TEXTURE_2D, 0);
   glBindFramebufferEXT  (GL_FRAMEBUFFER_EXT,  s_fbo);
   /*---(draw)---------------------------*/
   glClear               (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   x_base = NODE_find_name ("/usr/lib64");
   if (x_base != NULL) {
      NODE_level      (0, x_base);
      NODE_size_purge ();
      NODE_resize     (0, x_base);
      DRAW_level      (0, x_base, 'y');
   }
   else                   DRAW_level  (0, h_node, 'y');
   DRAW_level  (0, h_node, 'y');
   /*---(mipmaps)------------------------*/
   DEBUG_GRAF   yLOG_note    ("set for normal drawing");
   glBindFramebufferEXT  (GL_FRAMEBUFFER_EXT, 0);
   glBindTexture         (GL_TEXTURE_2D, s_tex);
   glGenerateMipmapEXT   (GL_TEXTURE_2D);
   glBindTexture         (GL_TEXTURE_2D, 0);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DRAW_resize        (uint a_w, uint a_h)
{
   /*---(locals)-----------+-----------+-*/
   float       x_width     = my.w_wide / 2.0;
   float       x_height    = my.w_tall / 2.0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   if (a_h == 0)  a_h = 1;
   /*---(settings)-----------------------*/
   glViewport            (0,  0, my.w_wide, my.w_tall);
   /*> glViewport            (-x_width,  -x_height, my.w_wide, my.w_tall);              <*/
   glMatrixMode          (GL_PROJECTION);
   glLoadIdentity        ();
   glOrtho               (  -x_width,   x_width,  -x_height,   x_height, -1500.0,  1500.0);
   /*> gluPerspective        (45.0f, (GLfloat) my.w_wide / (GLfloat) my.w_tall, 0.1f, 10000.0f);   <*/
   glMatrixMode          (GL_MODELVIEW);
   glLoadIdentity        ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
TEX_show           (void)
{
   /*---(locals)-----------+-----------+-*/
   float       x_width     = my.w_wide / 2.0;
   float       x_height    = my.w_tall / 2.0;
   char        t           [100];
   float w = 0;
   int   x, y, z;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(clear and prepare)--------------*/
   glClear         (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity  ();
   /*---(title)-----------------------------*/
   glPushMatrix(); {
      DRAW__color_fore ();
      glTranslatef(-345.0,  348.0,  200.0);
      yFONT_print (txf_bg, 14, YF_TOPLEF, "hyleoroi (forest watchers)");
      glTranslatef(   0.0,  -18.0,    0);
      yFONT_print (txf_bg, 10, YF_TOPLEF, "tree structure visualization");
      glTranslatef(  30.0,  -14.0,    0);
      sprintf (t, "[%s]", VER_NUM);
      yFONT_print (txf_bg, 10, YF_TOPLEF, t);
      glTranslatef( -30.0,    0.0,    0);
      glRotatef(-90.0, 0.0, 0.0, 1.0);
      glTranslatef(   2.0,   10.0,    0);
      yFONT_print (txf_bg, 10, YF_TOPLEF, my.tdesc);
      glTranslatef(   0.0,   18.0,    0);
      yFONT_print (txf_bg, 14, YF_TOPLEF, my.fdesc);
   } glPopMatrix();
   glPushMatrix(); {
      DRAW__color_fore ();
      glTranslatef(-345.0, -335.0,  200.0);
      sprintf (t, "%d color max-diff palette", n_all_color);
      yFONT_print (txf_bg, 10, YF_TOPLEF, t);
      glTranslatef(   0.0,   15.0,    0.0);
      sprintf (t, "using %d colors"          , g_ncolor);
      yFONT_print (txf_bg, 10, YF_TOPLEF, t);
      glTranslatef(   0.0,   15.0,    0.0);
      sprintf (t, "start color %d", my.color_start);
      yFONT_print (txf_bg, 10, YF_TOPLEF, t);
      glTranslatef(   0.0,   15.0,    0.0);
      sprintf (t, "%s", (my.chaos == 'y') ? "chaos" : "normal");
      yFONT_print (txf_bg, 10, YF_TOPLEF, t);
   } glPopMatrix();
   glPushMatrix(); {
      DRAW__color_fore ();
      glTranslatef( 345.0, -335.0,  200.0);
      if (my.noempty == 'y')  yFONT_print (txf_bg, 10, YF_TOPRIG, "no empty");
      else                    yFONT_print (txf_bg, 10, YF_TOPRIG, "show empty");
      glTranslatef(   0.0,   15.0,    0.0);
      if (my.ghost   == 'y')  yFONT_print (txf_bg, 10, YF_TOPRIG, "show ghosts");
      else                    yFONT_print (txf_bg, 10, YF_TOPRIG, "no ghosts");
   } glPopMatrix();
   glPushMatrix(); {
      DRAW__color_fore ();
      glTranslatef( 345.0,  348.0,  200.0);
      yFONT_print (txf_bg, 10, YF_TOPRIG, my.report);
      glTranslatef(   0.0,  -12.0,    0.0);
      yFONT_print (txf_bg, 14, YF_TOPRIG, my.source);
      glTranslatef(   0.0,  -18.0,    0.0);
      sprintf (t, "total nodes %d", n_node);
      yFONT_print (txf_bg, 10, YF_TOPRIG, t);
      glTranslatef(   0.0,  -14.0,    0.0);
      sprintf (t, "max depth %d", my.max_depth);
      yFONT_print (txf_bg, 10, YF_TOPRIG, t);
   } glPopMatrix();
   /*---(graph)-----------------------------*/
   glTranslatef    ( my.xdist,  my.ydist,   0.0);
   glBindTexture   (GL_TEXTURE_2D, s_tex);
   glPushMatrix(); {
      /*> glTranslatef(   0.0,    0.0,  100.0f);                                      <*/
      glRotatef(my.angle, 0.0, 0.0, 1.0);
      /*> glColor4f (1.0f, 1.0f, 1.0f, 1.0f);                                         <*/
      glBegin      (GL_POLYGON);
      glTexCoord2f ( 0.00, 1.00);
      glVertex3f   ( -x_width,  x_height, 0.0);
      glTexCoord2f ( 1.00, 1.00);
      glVertex3f   (  x_width,  x_height, 0.0);
      glTexCoord2f ( 1.00, 0.00);
      glVertex3f   (  x_width, -x_height, 0.0);
      glTexCoord2f ( 0.00, 0.00);
      glVertex3f   ( -x_width, -x_height, 0.0);
      glEnd();
   } glPopMatrix();
   glBindTexture   (GL_TEXTURE_2D, 0);
   /*---(force the redraw)-----------------*/
   glXSwapBuffers(DISP, BASE);
   glFlush();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        event handling                        ----===*/
/*====================------------------------------------====================*/
static void      o___EVENTS__________________o (void) {;}

char         /*===[[ process xwindows event stream ]]=====[ ------ [ ------ ]=*/
PROG_event         (void)
{  /*---(local variables)--+-----------+-*/
   XKeyEvent  *x_keyevent  = NULL;          /* returned xwindows key event    */
   char        x_keys      [5];             /* acutal keys pressed            */
   int         rci         =    0;          /* return code as integer         */
   int         x_updates   =    0;          /* screen update count            */
   long        x_beg       =    0;          /* update beg time                */
   long        x_end       =    0;          /* update end time                */
   long        x_dur       =    0;          /* update duration                */
   char        x_quit      =  '-';          /* flag to quit                   */
   char        x_active    =  'y';          /* flag if visual moving/active   */
   /*---(main loop)----------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   TEX_show    ();
   /*---(processing loop)----------------*/
   while (x_quit == '-') {
      while (XPending(DISP)) {
         XNextEvent(DISP, &EVNT);
         /*---(start)----------------------------*/
         switch(EVNT.type) {
         case Expose:
            DEBUG_LOOP   yLOG_note    ("expose event");
            break;

         case ConfigureNotify:
            DEBUG_LOOP   yLOG_note    ("configure event");
            break;

         case KeyPress:
            DEBUG_LOOP   yLOG_note    ("keypress event");
            x_keyevent = (XKeyEvent *) &EVNT;
            rci = XLookupString ((XKeyEvent *) &EVNT, x_keys, 5, NULL, NULL);
            if (rci < 1) break;
            switch (x_keys [0]) {
            case 'Q': x_quit = 'y';                                 break;
            case '[': my.inc     = STOP;      my.angle  =   0.0;    break;
            case '{': my.inc     = STOP;      my.angle +=  90.0;    break;
            case '(': my.inc     = STOP;      my.angle +=  20.0;    break;
            case '-': my.inc    -= INC_SPEED;                       break;
            case '<': my.inc     = STOP;      my.angle += my.single;   break;
            case '.': my.inc     = STOP;      x_active = '-';       break;
            case ',': my.inc     = PLAY;                            break;
            case '>': my.inc     = STOP;      my.angle -= my.single;   break;
            case '+': my.inc    += INC_SPEED;                       break;
            case ')': my.inc     = STOP;      my.angle -=  20.0;    break;
            case '}': my.inc     = STOP;      my.angle -=  90.0;    break;
            case ']': my.inc     = STOP;      my.angle  =   0.0;    break;
            case 'i':                         my.zdist -=  20.0;    break;
            case 'I':                         my.zdist -= 100.0;    break;
            case 'o':                         my.zdist +=  20.0;    break;
            case 'O':                         my.zdist += 100.0;    break;
            case 'k':                         my.ydist -=   5.0;    break;
            case 'K':                         my.ydist -=  20.0;    break;
            case 'j':                         my.ydist +=   5.0;    break;
            case 'J':                         my.ydist +=  20.0;    break;
            case 'l':                         my.xdist -=   5.0;    break;
            case 'L':                         my.xdist -=  20.0;    break;
            case 'h':                         my.xdist +=   5.0;    break;
            case 'H':                         my.xdist +=  20.0;    break;
                                              /*> case '0': my.xdist = 0.0; my.ydist = 0.0; my.zdist =  980.0;  mask_small(); break;    <* 
                                               *> case '1': my.xdist = 0.0; my.ydist = 0.0; my.zdist =  550.0;  mask_small(); break;    <* 
                                               *> case '2': my.xdist = 0.0; my.ydist = 0.0; my.zdist =  660.0;  mask_med();    break;   <* 
                                               *> case '3': my.xdist = 0.0; my.ydist = 0.0; my.zdist =  330.0;  mask_med();    break;   <* 
                                               *> case '4': my.xdist = 0.0; my.ydist = 0.0; my.zdist =  660.0;  mask_big();    break;   <* 
                                               *> case '5': my.xdist = 0.0; my.ydist = 0.0; my.zdist =  330.0;  mask_big();    break;   <*/
            case 'r': my.inc     = STOP;      my.angle -=   1.0;    break;
            case 't': my.inc     = STOP;      my.angle +=   1.0;    break;
            default :                                            break;
            }
            if (my.zdist     <   200.0   )  my.zdist     =  200.0;
            if (my.zdist     >  1400.0   )  my.zdist     = 1400.0;
            if (my.inc    >  MAX_SPEED)  my.inc    =  MAX_SPEED;
            if (my.inc    < -MAX_SPEED)  my.inc    = -MAX_SPEED;
            x_active = '-';
            if (my.inc != 0.0)  x_active  = 'y';
            break;

         default          :
            DEBUG_LOOP   yLOG_note    ("other event");
            break;
         }
      }
      /*---(timer)-----------------------*/
      my.angle -= my.inc;
      if (my.angle > 360.0) my.angle  = my.angle - 360.0 + my.inc;
      if (my.angle <   0.0) my.angle  = my.angle + 360.0 - my.inc;
      /*---(update)----------------------*/
      x_beg = TIME_stamp();
      TEX_show    ();
      /*> DRAW_direct ();                                                             <*/
      x_end  = TIME_stamp();
      ++x_updates;
      x_dur = x_end - x_beg;
      /*---(sleep)-----------------------*/
      usleep(20000);
   }  /*---(done)------------------------*/
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   if (x_quit == 'y')  return -1;
   return 0;
}

char
DRAW_ring_set      (void)
{
   return 0;
}




/*> char                                                                                                <* 
 *> mask_big   (void)                                                                                   <* 
 *> {                                                                                                   <* 
 *>    Pixmap    bounds    = XCreatePixmap(DISP, BASE, my.w_wide, my.w_tall, 1);                                <* 
 *>    GC        gc        = XCreateGC(DISP, bounds, 0, NULL);                                          <* 
 *>    XSetForeground(DISP, gc, 0);                                                                     <* 
 *>    XFillRectangle(DISP, bounds, gc, 0, 0, my.w_wide, my.w_tall);                                            <* 
 *>    XSetForeground(DISP, gc, 1);                                                                     <* 
 *>    /+> XFillArc(DISP, bounds, gc, my.w_wide / 2, my.w_tall / 2, my.w_wide / 2, my.w_tall / 2, 0, 360 * 64);   <+/   <* 
 *>    /+> XFillArc(DISP, bounds, gc, 0, 0,1000,1000, 0, 360 * 64);                       <*            <* 
 *>     *> XShapeCombineMask(DISP, BASE, ShapeBounding, 0, 0, bounds, ShapeSet);          <+/           <* 
 *>    /+---(complete)-----------------------+/                                                         <* 
 *>    XFreePixmap(DISP, bounds);                                                                       <* 
 *>    return 0;                                                                                        <* 
 *> }                                                                                                   <*/

/*> char                                                                                                <* 
 *> mask_med   (void)                                                                                   <* 
 *> {                                                                                                   <* 
 *>    Pixmap    bounds    = XCreatePixmap(DISP, BASE, my.w_wide, my.w_tall, 1);                                <* 
 *>    GC        gc        = XCreateGC(DISP, bounds, 0, NULL);                                          <* 
 *>    XSetForeground(DISP, gc, 0);                                                                     <* 
 *>    XFillRectangle(DISP, bounds, gc, 0, 0, my.w_wide, my.w_tall);                                            <* 
 *>    XSetForeground(DISP, gc, 1);                                                                     <* 
 *>    /+> XFillArc(DISP, bounds, gc, w_wide / 2, my.w_tall / 2, w_wide / 2, my.w_tall / 2, 0, 360 * 64);   <+/   <* 
 *>    XFillArc(DISP, bounds, gc, 0, 0,   600,   600, 0, 360 * 64);                                     <* 
 *>    XShapeCombineMask(DISP, BASE, ShapeBounding, 0, 0, bounds, ShapeSet);                            <* 
 *>    /+---(complete)-----------------------+/                                                         <* 
 *>    XFreePixmap(DISP, bounds);                                                                       <* 
 *>    return 0;                                                                                        <* 
 *> }                                                                                                   <*/

/*> char                                                                                                <* 
 *> mask_small (void)                                                                                   <* 
 *> {                                                                                                   <* 
 *>    Pixmap    bounds    = XCreatePixmap(DISP, BASE, my.w_wide, my.w_tall, 1);                                <* 
 *>    GC        gc        = XCreateGC(DISP, bounds, 0, NULL);                                          <* 
 *>    XSetForeground(DISP, gc, 0);                                                                     <* 
 *>    XFillRectangle(DISP, bounds, gc, 0, 0, my.w_wide, my.w_tall);                                            <* 
 *>    XSetForeground(DISP, gc, 1);                                                                     <* 
 *>    /+> XFillArc(DISP, bounds, gc, w_wide / 2, my.w_tall / 2, w_wide / 2, my.w_tall / 2, 0, 360 * 64);   <+/   <* 
 *>    XFillArc(DISP, bounds, gc, 100, 100, 400, 400, 0, 360 * 64);                                     <* 
 *>    XShapeCombineMask(DISP, BASE, ShapeBounding, 0, 0, bounds, ShapeSet);                            <* 
 *>    /+---(complete)-----------------------+/                                                         <* 
 *>    XFreePixmap(DISP, bounds);                                                                       <* 
 *>    return 0;                                                                                        <* 
 *> }                                                                                                   <*/



/*===============================[[ end-code ]]===============================*/
