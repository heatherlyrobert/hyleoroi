/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



/*---(window)----------------------------*/

/*---(sizes)-----------------------------*/

/*---(fonts)--------------------------*/
char       *face_sm     = "verdana_sm";
char       *face_bg     = "verdana";
int         txf_sm;
int         txf_bg;

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
   my.t_wide       =  300;     /* 225 */
   my.m_wide       =  700;
   my.a_wide       =    0;     /* 200 */
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
   my.c_tall       =    0;   /* 20 */
   my.a_tall       = my.m_tall;
   my.w_tall       = my.t_tall = my.m_tall + my.c_tall;
   /*---(bottoms)------------------------*/
   DEBUG_TOPS   yLOG_note    ("set window/panel bottom positions");
   my.t_bott       = my.c_bott =   0;  
   my.m_bott       = my.a_bott = my.c_tall;
   /*---(output)----------------------*/
   /*> printf ("tags    : %4dx %4dy, %4dw %4dh\n", my.t_left, my.t_bott, my.t_wide, my.t_tall);   <* 
    *> printf ("main    : %4dx %4dy, %4dw %4dh\n", my.m_left, my.m_bott, my.m_wide, my.m_tall);   <* 
    *> printf ("cmds    : %4dx %4dy, %4dw %4dh\n", my.c_left, my.c_bott, my.c_wide, my.c_tall);   <* 
    *> printf ("alts    : %4dx %4dy, %4dw %4dh\n", my.a_left, my.a_bott, my.a_wide, my.a_tall);   <* 
    *> printf ("full    : %4dx %4dy, %4dw %4dh\n", 0        , 0        , my.w_wide, my.w_tall);   <*/
   /*---(complete)--------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                       graphics preparation                   ----===*/
/*====================------------------------------------====================*/
static void      o___ONE_TIME________________o (void) {;}

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
   COLOR_back  ();
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
   DRAW_main   ();
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
      DRAW_main   ();
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

char
DRAW_alts          (void)
{
   /*---(setup view)---------------------*/
   glViewport      ( my.a_left, my.a_bott, my.a_wide, my.a_tall);
   glMatrixMode    (GL_PROJECTION);
   glLoadIdentity  ();
   glOrtho         ( 0.0f, my.a_wide, 0.0f, my.a_tall,  -500.0,   500.0);
   glMatrixMode    (GL_MODELVIEW);
   /*---(background)---------------------*/
   glPushMatrix    (); {
      glColor4f    (0.00f, 0.25f, 0.00f, 1.0f);
      glBegin         (GL_POLYGON); {
         glVertex3f  (0.0f     , my.a_tall,  0.0f);
         glVertex3f  (my.a_wide, my.a_tall,  0.0f);
         glVertex3f  (my.a_wide, 0.0f      ,  0.0f);
         glVertex3f  (0.0f     , 0.0f      ,  0.0f);
      } glEnd   ();
   } glPopMatrix   ();
   /*---(complete)-----------------------*/
   return;
}

char
DRAW_command       (void)
{
   /*---(setup view)---------------------*/
   glViewport      ( my.c_left, my.c_bott, my.c_wide, my.c_tall);
   glMatrixMode    (GL_PROJECTION);
   glLoadIdentity  ();
   glOrtho         ( 0.0f, my.c_wide, 0.0f, my.c_tall,  -500.0,   500.0);
   glMatrixMode    (GL_MODELVIEW);
   /*---(background)---------------------*/
   glPushMatrix    (); {
      glColor4f    (0.00f, 0.00f, 0.15f, 1.0f);
      glBegin         (GL_POLYGON); {
         glVertex3f  (0.0f     , my.c_tall,  0.0f);
         glVertex3f  (my.c_wide, my.c_tall,  0.0f);
         glVertex3f  (my.c_wide, 0.0f     ,  0.0f);
         glVertex3f  (0.0f     , 0.0f     ,  0.0f);
      } glEnd   ();
   } glPopMatrix   ();
   /*---(text)---------------------------*/
   /*> glPushMatrix    (); {                                                          <* 
    *>    glTranslatef (    2.0f,    2.0f,    0.0f);                                  <* 
    *>    glColor4f    (1.00f, 1.00f, 1.00f, 1.00f);                                  <* 
    *>    yFONT_print  (my.font_fixed,  12, YF_BOTLEF, my.message);                   <* 
    *> } glPopMatrix   ();                                                            <*/
   /*---(complete)-----------------------*/
   return;
}

char
DRAW_main          (void)
{
   /*---(prepare)------------------------*/
   glClear         (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   /*---(normal)-------------------------*/
   GRAPH_show      ();
   TAGS_show       ();
   DRAW_command    ();
   DRAW_alts       ();
   /*---(send for processing)------------*/
   glXSwapBuffers  (DISP, BASE);
   glFlush         ();
   /*---(complete)-----------------------*/
   return 0;
}



/*===============================[[ end-code ]]===============================*/
