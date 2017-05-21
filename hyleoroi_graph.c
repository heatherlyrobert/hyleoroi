/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



/*---(opengl objects)--------------------*/
uint        s_tex       =     0;            /* texture for image              */
uint        s_fbo       =     0;            /* framebuffer                    */
uint        s_depth     =     0;            /* depth buffer                   */


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
      COLOR_back ();
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
   COLOR_node  (a_node);
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
      COLOR_label   (a_node, a_style);
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
   g_bnode = NODE_find_name ("/usr/lib64");
   if (g_bnode != NULL) {
      NODE_level      (0, g_bnode);
      NODE_size_purge ();
      NODE_resize     (0, g_bnode);
      DRAW_level      (0, g_bnode, 'y');
   }
   else  g_bnode = g_hnode;
   DRAW_level  (0, g_bnode, 'y');
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
TEX_show           (void)
{
   /*---(locals)-----------+-----------+-*/
   float       x_width     = my.m_wide / 2.0;
   float       x_height    = my.m_tall / 2.0;
   char        t           [100];
   float w = 0;
   int   x, y, z;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(clear and prepare)--------------*/
   /*> glClear         (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                   <* 
    *> glLoadIdentity  ();                                                            <*/
   /*---(title)-----------------------------*/
   glPushMatrix(); {
      COLOR_fore ();
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
      COLOR_fore ();
      glTranslatef(-345.0, -335.0,  200.0);
      sprintf (t, "%d color max-diff palette", g_acolor);
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
      COLOR_fore ();
      glTranslatef( 345.0, -335.0,  200.0);
      if (my.noempty == 'y')  yFONT_print (txf_bg, 10, YF_TOPRIG, "no empty");
      else                    yFONT_print (txf_bg, 10, YF_TOPRIG, "show empty");
      glTranslatef(   0.0,   15.0,    0.0);
      if (my.ghost   == 'y')  yFONT_print (txf_bg, 10, YF_TOPRIG, "show ghosts");
      else                    yFONT_print (txf_bg, 10, YF_TOPRIG, "no ghosts");
   } glPopMatrix();
   glPushMatrix(); {
      COLOR_fore ();
      glTranslatef( 345.0,  348.0,  200.0);
      yFONT_print (txf_bg, 10, YF_TOPRIG, my.report);
      glTranslatef(   0.0,  -12.0,    0.0);
      yFONT_print (txf_bg, 14, YF_TOPRIG, my.source);
      glTranslatef(   0.0,  -18.0,    0.0);
      sprintf (t, "total nodes %d", g_nnode);
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
   /*> glXSwapBuffers(DISP, BASE);                                                    <* 
    *> glFlush();                                                                     <*/
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
GRAPH_show         (void)
{
   float       x_width     = my.m_wide  / 2.0;
   float       x_height    = my.m_tall  / 2.0;
   /*---(setup view)---------------------*/
   glViewport      (my.m_left, my.m_bott, my.m_wide, my.m_tall);
   glMatrixMode    (GL_PROJECTION);
   glLoadIdentity  ();
   glOrtho         (  -x_width,   x_width,  -x_height,   x_height, -500.0,  500.0);
   glMatrixMode    (GL_MODELVIEW);
   TEX_show ();
   return 0;
}





/*===============================[[ end-code ]]===============================*/
