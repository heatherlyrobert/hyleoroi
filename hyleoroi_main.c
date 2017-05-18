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
   /*---(startup)------------------------*/
   if (rc == 0)   rc = PROG_urgs    (argc, argv);
   if (rc == 0)   rc = PROG_init    ();
   if (rc == 0)   rc = PROG_args    (argc, argv);
   if (rc == 0)   rc = PROG_begin   ();
   if (rc != 0) {
      PROG_end     ();
      return -1;
   }
   /*---(node setup)---------------------*/
   /*> rc = NODE_read    (0, h_node);                                                 <*/
   rc = FILE_main    ();
   if (rc < 0) return rc;

   /*> return 0;                                                                      <*/


   NODE_reroot  ();
   if (my.noempty == 'y' && my.empty != NULL) {
      h_node->size   -= my.empty->size;
      my.empty->size  = 0;
   }
   NODE_process (0, h_node);
   OPT_PRINT  NODE_list    (h_node, 'y');
   /*---(drawing setup)------------------*/
   TEX_draw     ();
   DRAW_resize  (my.win_w, my.win_h);
   /*---(main)---------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   while (rc >= 0) {
      rc = PROG_event ();
      /*> if (rc >  1) format_change (rc);                                            <*/
   }
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   /*---(complete)-----------------------*/
   PROG_end     ();
   return 0;
}





/*============================----(source-end)----============================*/
