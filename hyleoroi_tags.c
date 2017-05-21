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
   s_tall         = 4000;   /* max allowed single dimension */
   s_wide         =  400;   /* wide enough for clever bits  */
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
   float       x_tall      = 10.0;
   float       x_margin    =  5.0;
   float       x_spacer    =  2.0;
   float       x_top       =  0.0;
   float       x_bot       =  0.0;
   float       x_lef       =  0.0;
   float       x_rig       =  0.0;
   float       x_text      =  0.0;
   char        x_name      [LEN_STR];
   /*---(position)-----------------------*/
   x_top  = x_margin + a_seq * (x_tall + x_spacer);
   x_bot  = x_top + x_tall;
   x_lef  = x_margin;
   x_rig  = my.t_wide - x_margin;
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
   COLOR_label (a_node, '-');
   glPushMatrix    (); {
      glTranslatef(x_lef + x_margin, -x_text,  20.0);
      yFONT_print (txf_bg,  7, YF_MIDLEF, x_name);
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
DRAW_tags          (void)
{
   /*---(setup view)---------------------*/
   glViewport      ( my.t_left, my.t_bott, my.t_wide, my.t_tall);
   glMatrixMode    (GL_PROJECTION);
   glLoadIdentity  ();
   glOrtho         ( 0.0f, my.t_wide, -my.t_tall, 0.0,  -500.0,   500.0);
   glMatrixMode    (GL_MODELVIEW);
   /*---(background)---------------------*/
   COLOR_back ();
   glPushMatrix    (); {
      glBegin         (GL_POLYGON); {
         glVertex3f  (0.0f     , my.t_tall,  -20.0f);
         glVertex3f  (my.t_wide, my.t_tall,  -20.0f);
         glVertex3f  (my.t_wide, 0.0f     ,  -20.0f);
         glVertex3f  (0.0f     , 0.0f     ,  -20.0f);
      } glEnd   ();
   } glPopMatrix   ();
   /*---(tags)---------------------------*/
   DRAW__list   (g_bnode);
   /*---(complete)-----------------------*/
   return;
}


/*===============================[[ end-code ]]===============================*/
