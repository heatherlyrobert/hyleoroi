/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */




char         /*--: process nodes -------------------------[ leaf   [ ------ ]-*/
PREP__wipe           (tNODE *a_node)
{
   a_node->beg   = 0.0;
   a_node->pct   = 0.0;
   a_node->width = 0.0;
   a_node->end   = 0.0;
   return 0;
}

char         /*--: process nodes -------------------------[ leaf   [ ------ ]-*/
PREP__purge     (int a_level, tNODE *a_parent)
{
   /*---(local variables)--+-----------+-*/
   tNODE      *x_child     = NULL;
   char        rce         =  -10;          /* return code for errors         */
   /*---(defense)------------------------*/
   --rce;  if (a_parent == NULL)  return rce;
   /*---(check root)---------------------*/
   if (a_level == 0)  NODE__wipe (a_parent);
   /*---(process siblings)---------------*/
   x_child = a_parent->c_head;
   while (x_child != NULL) {
      if (x_child->level > my.max_depth)  my.max_depth = x_child->level;
      PREP__wipe (x_child);
      if (x_child->nchild > 0) PREP__purge  (a_level + 1, x_child);
      x_child = x_child->s_next;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--: process nodes -------------------------[ leaf   [ ------ ]-*/
PREP_purge           (void)
{
   PREP__purge  (0, g_hnode);
   return 0;
}

char         /*--: put details into root -----------------[ leaf   [ ------ ]-*/
PREP__root          (tNODE *a_node)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_senter  (__FUNCTION__);
   DEBUG_INPT   yLOG_spoint  (a_node);
   /*---(defense)------------------------*/
   if (a_node == NULL  ) {
      DEBUG_INPT   yLOG_snote   ("can not be NULL");
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return  -11;
   }
   /*> DEBUG_INPT   yLOG_spoint  (g_hnode);                                            <*/
   /*> if (a_node != g_hnode) {                                                        <* 
    *>    DEBUG_INPT   yLOG_snote   ("does not match head");                          <* 
    *>    DEBUG_INPT   yLOG_sexit   (__FUNCTION__);                                   <* 
    *>    return  -12;                                                                <* 
    *> }                                                                              <*/
   /*---(initialize)---------------------*/
   DEBUG_INPT   yLOG_snote   ("initialize to whole");
   a_node->beg    = 0.0;
   a_node->pct    = 100.0;
   a_node->width  = my.full_size;
   a_node->end    = my.full_size;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*--: process nodes -------------------------[ leaf   [ ------ ]-*/
PREP_resize        (int a_level, tNODE *a_parent)
{
   /*---(local variables)--+-----------+-*/
   tNODE      *x_child     = NULL;
   char        rce         =  -10;          /* return code for errors         */
   int         i           =    0;          /* generic iterator -- fields     */
   char        x_print     [150] = "";
   double      x_size      =  0.0;
   double      x_total     =  0.0;
   double      x_beg       =  0.0;
   double      x_width     =  0.0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_point   ("a_parent"  , a_parent);
   /*---(defense)------------------------*/
   --rce;  if (a_parent == NULL) {
      DEBUG_INPT   yLOG_note    ("can not process NULL");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   if (a_parent->name != NULL) {
      DEBUG_INPT   yLOG_info    ("name"      , a_parent->name);
   } else {
      DEBUG_INPT   yLOG_info    ("name"      , "((null))");
   }
   /*---(check root)---------------------*/
   if (a_level == 0)  PREP__root (a_parent);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_double  ("size"      , a_parent->size);
   if (a_parent->size <= 0.0) {
      DEBUG_INPT   yLOG_note    ("can not process zero or less");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_INPT   yLOG_note    ("prepare");
   x_size   = a_parent->size;
   x_beg    = a_parent->beg;
   x_width  = a_parent->width;
   DEBUG_INPT   yLOG_value   ("nchild"    , a_parent->nchild);
   /*---(process siblings)---------------*/
   x_child = a_parent->c_head;
   while (x_child != NULL) {
      if (x_child->level > my.max_depth)  my.max_depth = x_child->level;
      /*---(prepare)---------------------*/
      ++c;
      DEBUG_INPT   yLOG_value   ("count"     , c);
      if (x_child->name != NULL) {
         DEBUG_INPT   yLOG_info    ("name"      , x_child->name);
      } else {
         DEBUG_INPT   yLOG_info    ("name"      , "((null))");
      }
      /*---(calculate)-------------------*/
      x_child->beg   = x_beg;
      x_child->pct   = x_child->size / x_size;
      x_child->width = x_child->pct  * x_width;
      x_child->end   = x_beg + x_child->width;
      x_beg          = x_child->end;
      x_total       += x_child->size;
      DEBUG_INPT   yLOG_double  ("beg"       , x_child->beg);
      DEBUG_INPT   yLOG_double  ("pct"       , x_child->pct);
      DEBUG_INPT   yLOG_double  ("width"     , x_child->width);
      DEBUG_INPT   yLOG_double  ("end"       , x_child->end);
      /*---(dive in)---------------------*/
      if (x_child->nchild > 0) {
         PREP_resize  (a_level + 1, x_child);
      }
      /*---(next)------------------------*/
      x_child = x_child->s_next;
      /*---(done)------------------------*/
   }
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--: process nodes -------------------------[ leaf   [ ------ ]-*/
PREP_process       (int a_level, tNODE *a_parent)
{  /*---(local variables)--+-----------+-*/
   tNODE      *x_child     = NULL;
   char        rce         =  -10;          /* return code for errors         */
   int         i           =    0;          /* generic iterator -- fields     */
   char        x_print     [150] = "";
   double      x_size      =  0.0;
   double      x_total     =  0.0;
   double      x_beg       =  0.0;
   double      x_width     =  0.0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_point   ("a_parent"  , a_parent);
   /*---(defense)------------------------*/
   --rce;  if (a_parent == NULL) {
      DEBUG_INPT   yLOG_note    ("can not process NULL");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   if (a_parent->name != NULL) {
      DEBUG_INPT   yLOG_info    ("name"      , a_parent->name);
   } else {
      DEBUG_INPT   yLOG_info    ("name"      , "((null))");
   }
   /*---(check root)---------------------*/
   if (a_parent == g_hnode)  PREP__root (a_parent);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_double  ("size"      , a_parent->size);
   if (a_parent->size <= 0.0) {
      DEBUG_INPT   yLOG_note    ("can not process zero or less");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_INPT   yLOG_note    ("prepare");
   x_size   = a_parent->size;
   x_beg    = a_parent->beg;
   x_width  = a_parent->width;
   DEBUG_INPT   yLOG_value   ("nchild"    , a_parent->nchild);
   /*---(process siblings)---------------*/
   x_child = a_parent->c_head;
   while (x_child != NULL) {
      if (x_child->level > my.max_depth)  my.max_depth = x_child->level;
      /*---(prepare)---------------------*/
      ++c;
      DEBUG_INPT   yLOG_value   ("count"     , c);
      if (x_child->name != NULL) {
         DEBUG_INPT   yLOG_info    ("name"      , x_child->name);
      } else {
         DEBUG_INPT   yLOG_info    ("name"      , "((null))");
      }
      /*---(calculate)-------------------*/
      x_child->beg   = x_beg;
      x_child->pct   = x_child->size / x_size;
      x_child->width = x_child->pct  * x_width;
      x_child->end   = x_beg + x_child->width;
      x_beg          = x_child->end;
      x_total       += x_child->size;
      /*---(add hint)--------------------*/
      if (x_child->hint [0] == '\0') {
         if (++(my.hint_minor) > 'z') {
            my.hint_minor = 'a';
            ++(my.hint_major);
         }
         if (my.hint_major > 'z') {
            my.hint_minor = '{';
            my.hint_major = '}';
         }
         x_child->hint [0] = my.hint_major;
         x_child->hint [1] = my.hint_minor;
         x_child->hint [2] = '\0';
      }
      /*---(dive in)---------------------*/
      if (x_child->nchild > 0) {
         PREP_process (a_level + 1, x_child);
      }
      /*---(next)------------------------*/
      x_child = x_child->s_next;
      /*---(done)------------------------*/
   }
   /*---(check for empty space)------------*/
   if (x_beg < a_parent->end) {
      NODE_create (&x_child, a_parent);
      x_child->level = a_level + 1;
      strcpy (x_child->label, "-");
      strcpy (x_child->name , "-");
      strcpy (x_child->desc , "-");
      x_child->size  = x_size - x_total;
      x_child->count = 0.0;
      x_child->beg   = x_beg;
      x_child->end   = a_parent->end;
      x_child->width = x_child->end - x_child->beg;
      x_child->pct   = x_child->size / x_size;
      x_child->color = -1;
   }
   /*---(complete)-------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> fix level indicators on nodes ----------[ ------ [ ------ ]-*/
PREP_levelall      (void)
{
   PREP_level (0, g_hnode);
   return 0;
}

char         /*-> fix level indicators on nodes ----------[ leaf   [ ------ ]-*/
PREP_level         (int a_level, tNODE *a_parent)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   tNODE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_point   ("a_parent"  , a_parent);
   /*---(defense)------------------------*/
   --rce;  if (a_parent == NULL) {
      DEBUG_INPT   yLOG_info    ("a_parent"       ,  "can not be NULL");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(level)--------------------------*/
   a_parent->level = a_level;
   /*---(prepare)------------------------*/
   --rce;  if (a_parent->nchild == 0) {
      DEBUG_INPT   yLOG_info    ("nchild"   ,  "no children to process");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   x_curr = a_parent->c_head;
   /*---(show children)------------------*/
   while (x_curr != NULL) {
      PREP_level (a_level + 1, x_curr);
      x_curr = x_curr->s_next;
   }
   /*---(complete)-------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}
