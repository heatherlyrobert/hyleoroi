/*============================---(source-start)---============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



/*---(fonts)-----------------------------*/
/*> char  *face_sm  = "verdana_sm";                                                   <* 
 *> char  *face_bg  = "verdana";                                                      <* 
 *> int    txf_sm;                                                                    <* 
 *> int    txf_bg;                                                                    <*/



tNODE    *root      = NULL;       /* root node                                */
int       spaces    = 0;          /* number of radial spaces required         */


long      gpu_mem_bef = 0;
long      gpu_mem_aft = 0;

#define   MAXLINE   500

#define   DEBUG_M    if (debug_mem   == 'y')
char      debug_mem   = 'n';
#define   DEBUG_I    if (debug_input == 'y')
char      debug_input = 'n';

char      file_format = 'f';




/*====================------------------------------------====================*/
/*===----                            main                              ----===*/
/*====================------------------------------------====================*/
static void      o___MAIN____________________o (void) {;}

int          /*===[[ main driver ]]=======================[ ------ [ ------ ]=*/
main               (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         rc          = 0;
   long        x_count     = 0;
   /*---(initialize)---------------------*/
   if (rc >= 0)   rc = yURG_logger  (argc, argv);
   if (rc >= 0)   rc = PROG_init    ();
   if (rc >= 0)   rc = yURG_urgs    (argc, argv);
   if (rc >= 0)   rc = PROG_args    (argc, argv);
   if (rc >= 0)   rc = PROG_begin   ();
   if (rc <  0)  {
      PROG_end     ();
      exit (-1);
   }
   rc = PROG_visual_beg ();
   if (rc < 0) return rc;
   NODE_root      ();
   rc = FILE_main    ();
   if (rc < 0) return rc;

   /*> return 0;                                                                      <*/


   NODE_reroot  ();


   if (my.noempty == 'y' && my.empty != NULL) {
      g_hnode->size   -= my.empty->size;
      my.empty->size  = 0;
   }
   PREP_levelall ();
   PREP_process  (0, g_hnode);
   NODE_DUMP   NODE_dump  (0, g_hnode, 'y');

   /*---(drawing setup)------------------*/
   GRAPH_init   ();
   GRAPH_draw   ();
   TAGS_init    ();
   TAGS_draw    ();
   NODE_DUMP   NODE_dump  (0, g_hnode, 'y');
   DRAW_resize  (my.w_wide, my.w_tall);
   /*---(main)---------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   while (rc >= 0) {
      rc = PROG_event ();
      /*> if (rc >  1) format_change (rc);                                            <*/
   }
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   /*---(complete)-----------------------*/
   PROG_visual_end ();
   PROG_end        ();
   return 0;
}





/*============================----(source-end)----============================*/
