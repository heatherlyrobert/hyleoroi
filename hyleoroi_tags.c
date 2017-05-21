/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



/*---(texture variables)-----------------*/
static int  s_tall      =  4000;            /* texture height                 */
static int  s_wide      =   400;            /* texture width                  */
static uint s_tex       =     0;            /* texture identifier             */
static uint s_fbo       =     0;            /* framebuffer                    */
static uint s_depth     =     0;            /* depth buffer                   */



/*====================------------------------------------====================*/
/*===----                         program level                        ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char         /*--> set values for progress ticker --------[ ------ [ ------ ]-*/
TAGS_init          (void)
{
   int         i           = 0;
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(sizes)--------------------------*/
   DEBUG_GRAF   yLOG_note    ("setting sizes (widths and heights)");
   s_wide         = my.t_wide * 2;  /* wide enough for clever bits  */
   s_tall         = my.t_tall * 4;  /* max allowed single dimension */
   /*---(working)------------------------*/
   DEBUG_GRAF   yLOG_note    ("initializing working variables");
   /*---(generate)-----------------------*/
   DEBUG_GRAF   yLOG_note    ("create a new texture");
   yGLTEX_new  (&s_tex, &s_fbo, &s_depth, s_wide, s_tall);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--> set values for progress ticker --------[ ------ [ ------ ]-*/
TAGS_wrap          (void)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(clear texture)------------------*/
   DEBUG_GRAF   yLOG_note    ("free up texture");
   yGLTEX_free (&s_tex, &s_fbo, &s_depth);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       tag window/panel                       ----===*/
/*====================------------------------------------====================*/
static void      o___TAGS____________________o (void) {;}

char         /*===[[ draw a level of wedges ]]============[ ------ [ ------ ]=*/
DRAW__show         (int a_seq, tNODE *a_node)
{
   /*---(locals)-----------+-----------+-*/
   float       x_tall      = 22.0;
   float       x_margin    = 10.0;
   float       x_spacer    =  5.0;
   float       x_hints     = 40.0;
   float       x_top       =  0.0;
   float       x_bot       =  0.0;
   float       x_lef       =  0.0;
   float       x_rig       =  0.0;
   float       x_text      =  0.0;
   char        x_name      [LEN_STR];
   /*---(position)-----------------------*/
   x_top  = x_margin + a_seq * (x_tall + x_spacer);
   x_bot  = x_top + x_tall;
   x_lef  = x_margin + x_hints;
   x_rig  = s_wide    - x_margin;
   x_text = x_top + (x_tall / 2.0);
   /*---(draw node)----------------------*/
   COLOR_node (a_node);
   glPushMatrix    (); {
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_lef, -x_top    ,  0.0f);
         glVertex3f  (x_rig, -x_top    ,  0.0f);
         glVertex3f  (x_rig, -x_bot    ,  0.0f);
         glVertex3f  (x_lef, -x_bot    ,  0.0f);
      } glEnd   ();
   } glPopMatrix   ();
   /*---(draw text)----------------------*/
   if (a_node->label != NULL)  strlcpy (x_name, a_node->name , LEN_STR);
   else                        strlcpy (x_name, "((-----))"  , LEN_STR);
   glPushMatrix    (); {
      glColor4f   (0.0, 0.0, 0.0, 1.0);
      glTranslatef(x_lef - x_margin, -x_text,  20.0);
      yFONT_print (txf_bg, 16, YF_MIDRIG, a_node->hint);
      COLOR_label (a_node, '-');
      glTranslatef(x_margin * 2.0  ,  0.0   ,  20.0);
      yFONT_print (txf_bg, 16, YF_MIDLEF, x_name);
   } glPopMatrix   ();
   /*---(complete)-----------------------*/
   return 0;
}

char         /*===[[ draw a level of wedges ]]============[ ------ [ ------ ]=*/
DRAW__list         (tNODE *a_base)
{  /*---(local variables)--+-----------+-*/
   char        rce         =  -10;
   tNODE      *x_curr      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_base == NULL) {
      DEBUG_GRAF   yLOG_warn    ("a_base NULL"   ,  "can not process");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(process siblings)---------------*/
   x_curr = a_base->sib_head;
   while (x_curr != NULL) {
      DEBUG_GRAF   yLOG_info    ("current"   , x_curr->name);
      DRAW__show  (c, x_curr);
      x_curr = x_curr->sib_next;
      ++c;
   }
   /*---(complete)-------------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
TAGS_draw          (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(setup)--------------------------*/
   rc = yGLTEX_draw_start   (s_fbo, YGLTEX_TOPLEF, s_wide, s_tall);
   /*---(background)---------------------*/
   COLOR_back ();
   glPushMatrix    (); {
      glBegin         (GL_POLYGON); {
         glVertex3f  (0.0f     , 0.0       ,  -20.0f);
         glVertex3f  (s_wide   , 0.0       ,  -20.0f);
         glVertex3f  (s_wide   , -s_tall   ,  -20.0f);
         glVertex3f  (0.0f     , -s_tall   ,  -20.0f);
      } glEnd   ();
   } glPopMatrix   ();
   /*---(draw)---------------------------*/
   rc = DRAW__list          (g_bnode);
   /*---(mipmaps)------------------------*/
   rc = yGLTEX_draw_end     (s_tex);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
TAGS_show          (void)
{
   /*---(setup view)---------------------*/
   glViewport      (my.t_left, my.t_bott, my.t_wide, my.t_tall);
   glMatrixMode    (GL_PROJECTION);
   glLoadIdentity  ();
   glOrtho         ( 0.0 , my.t_wide, -my.t_tall, 0.0, -500.0,  500.0);
   glMatrixMode    (GL_MODELVIEW);
   /*---(graph)-----------------------------*/
   glBindTexture   (GL_TEXTURE_2D, s_tex);
   glPushMatrix(); {
      glBegin      (GL_POLYGON);
      glTexCoord2f ( 0.00, 1.00);
      glVertex3f   (0.0       ,  0.0         , 0.0);
      glTexCoord2f ( 1.00, 1.00);
      glVertex3f   (my.t_wide ,  0.0         , 0.0);
      glTexCoord2f ( 1.00, 0.50);
      glVertex3f   (my.t_wide , -my.t_tall   , 0.0);
      glTexCoord2f ( 0.00, 0.50);
      glVertex3f   (0.0       , -my.t_tall   , 0.0);
      glEnd();
   } glPopMatrix();
   glBindTexture   (GL_TEXTURE_2D, 0);
   /*---(complete)-----------------------*/
   return 0;
}



/*===============================[[ end-code ]]===============================*/
