/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



tNODE      *h_node;
tNODE      *t_node;
int         n_node;



char         /*===[[ prepare for program ]]===============[ ------ [ ------ ]=*/
NODE_init          (void)
{
   h_node = NULL;
   t_node = NULL;
   n_node = 0;
   my.hint_major = 'a';
   my.hint_minor = 'a' - 1;
   NODE_append (NULL);
   strcpy (h_node->name, ROOT_DEF);
   return 0;
}

tNODE*       /*===[[ add a new node ]]====================[ ------ [ ------ ]=*/
NODE_append        (
      /*---(formal parameters)+-------------+---------------------------------*/
      tNODE      *a_owner     )             /* owner of new node              */
{  /*---(local variables)--+-----------+-*/
   tNODE      *x_new       = NULL;          /* pointer to appended node       */
   int         x_tries     = 3;             /* limiter on malloc attempts     */
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_point   ("a_owner"   , a_owner);
   /*---(defenses)-----------------------*/
   if (a_owner == NULL) {
      DEBUG_ENVI   yLOG_note    ("owning pointer NULL, so root");
   }
   /*---(create ptrs)--------------------*/
   DEBUG_DATA   yLOG_note    ("malloc new node");
   while (x_new == NULL) {
      if (--x_tries <= 0)  break;
      x_new = (tNODE*) malloc (sizeof (tNODE));
   }
   if (x_new == NULL) {
      DEBUG_DATA   yLOG_note    ("node malloc FAILED");
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return NULL;
   }
   DEBUG_DATA   yLOG_point   ("created"   , x_new);
   /*---(hook to overall list)-----------*/
   DEBUG_DATA   yLOG_note    ("hook to overall list");
   x_new->next = NULL;
   if (n_node == 0)  {
      h_node        = x_new;
      x_new->prev   = NULL;
   } else {
      t_node->next  = x_new;
      x_new->prev   = t_node;
   }
   t_node = x_new;
   ++n_node;
   /*---(initialize children)------------*/
   DEBUG_DATA   yLOG_note    ("initialize children");
   x_new->sib_head   = NULL;
   x_new->sib_tail   = NULL;
   x_new->nchild     = 0;
   x_new->sib_prev   = NULL;
   x_new->sib_next   = NULL;
   /*---(hook up to owner)---------------*/
   DEBUG_DATA   yLOG_note    ("hook to owning node");
   x_new->owner      = a_owner;
   if (a_owner != NULL) {
      if (a_owner->sib_head  == NULL) {
         a_owner->sib_head           = x_new;
         a_owner->sib_tail           = x_new;
      } else {
         x_new->sib_prev             = a_owner->sib_tail;
         a_owner->sib_tail->sib_next = x_new;
         a_owner->sib_tail           = x_new;
      }
      ++a_owner->nchild;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return x_new;
}

char         /*===[[ clean a node ]]======================[ ------ [ ------ ]=*/
NODE_wipe          (
      /*---(formal parameters)+-------------+---------------------------------*/
      tNODE      *a_node      )             /* node to clean                  */
{  /*---(local variables)--+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   DEBUG_DATA   yLOG_spoint  (a_node);
   /*---(defenses)-----------------------*/
   --rce;  if (a_node == NULL) {
      DEBUG_DATA   yLOG_snote   ("node pointer NULL, failed");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return rce;
   }
   /*---(basics)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("basics");
   a_node->level     =   -1;
   a_node->name [0]  = '\0';
   a_node->size      =  0.0;
   a_node->desc [0]  = '\0';
   a_node->hint [0]  = '\0';
   /*---(working)------------------------*/
   DEBUG_DATA   yLOG_snote   ("basics");
   a_node->pct       =  0.0;
   a_node->beg       =  0.0;
   a_node->width     =  0.0;
   /*> a_node->arc       =  0.0;                                                      <*/
   a_node->end       =  0.0;
   a_node->color     =    0;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}




static int         s_count     = 0;      /* count of listed nodes */

char         /*--: show a nodes details ------------------[ leaf   [ ------ ]-*/
NODE_show          (int a_level, tNODE *a_node)
{
   int         i           =    0;          /* generic iterator -- fields     */
   char        x_indent    [100] = "";
   char        x_print     [150] = "";
   if (a_node == NULL) return  -11;
   for (i = 0; i < a_level; ++i)  strcat (x_indent, "   ");
   if ((s_count %  5) == 0)  printf ("\n");
   if ((s_count % 25) == 0)  printf ("                                                                                  ---size-------  ---count------  ---beg-----  ---pct-----  ---width---  ---end-----\n\n");
   sprintf (x_print, "%02d.%02d.%s%s", a_level, a_node->level, x_indent, a_node->name);
   printf ("%-80.80s  %14.0lf  %14.0lf  %11.6f  %11.6f  %11.6f  %11.6f  %3d\n",
         x_print      ,
         a_node->size , a_node->size , a_node->beg  ,
         a_node->pct  , a_node->width, a_node->end  ,
         a_node->color);
   ++s_count;
   return 0;
}

char         /*-> fix level indicators on nodes ----------[ ------ [ ------ ]-*/
NODE_levelall      (void)
{
   NODE_level (0, h_node);
   return 0;
}

char         /*-> fix level indicators on nodes ----------[ leaf   [ ------ ]-*/
NODE_level         (int a_level, tNODE *a_parent)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   tNODE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_point   ("a_parent"  , a_parent);
   /*---(defense)------------------------*/
   --rce;  if (a_parent == NULL) {
      DEBUG_INPT   yLOG_warn    ("a_parent"       ,  "can not be NULL");
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
   x_curr = a_parent->sib_head;
   /*---(show children)------------------*/
   while (x_curr != NULL) {
      NODE_level (a_level + 1, x_curr);
      x_curr = x_curr->sib_next;
   }
   /*---(complete)-------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--: print a report of nodes ---------------[ leaf   [ ------ ]-*/
NODE_dump          (
      /*---(formal parameters)+-------------+---------------------------------*/
      int        a_level      ,
      tNODE     *a_parent     ,             /* parent node                    */
      char       a_recurse    )             /* should it recurse              */
{  /*---(local variables)--+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   tNODE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_point   ("a_parent"  , a_parent);
   /*---(defense)------------------------*/
   --rce;  if (a_parent == NULL) {
      DEBUG_INPT   yLOG_warn    ("a_parent"       ,  "can not be NULL");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*> a_parent->level = a_level;                                                     <*/
   --rce;  if (a_parent->nchild == 0) {
      DEBUG_INPT   yLOG_info    ("nchild"   ,  "no children to process");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   if (a_parent == h_node) NODE_show (a_level, a_parent);
   x_curr = a_parent->sib_head;
   /*---(show children)------------------*/
   while (x_curr != NULL) {
      NODE_show (a_level + 1, x_curr);
      if (a_recurse == 'y')  NODE_dump (a_level + 1, x_curr, a_recurse);
      x_curr = x_curr->sib_next;
   }
   /*---(complete)-------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--: put details into root -----------------[ leaf   [ ------ ]-*/
NODE_root          (tNODE *a_node)
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
   DEBUG_INPT   yLOG_spoint  (h_node);
   if (a_node != h_node) {
      DEBUG_INPT   yLOG_snote   ("does not match head");
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return  -12;
   }
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
NODE_process       (int a_level, tNODE *a_parent)
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
   if (a_parent == h_node)  NODE_root (a_parent);
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
   x_child = a_parent->sib_head;
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
      if (x_child->width >= 2.0) {
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
         NODE_process (a_level + 1, x_child);
      }
      /*---(next)------------------------*/
      x_child = x_child->sib_next;
      /*---(done)------------------------*/
   }
   /*---(check for empty space)------------*/
   if (x_beg < a_parent->end) {
      x_child = NODE_append (a_parent);
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

char         /*--: collapse redundant roots --------------[ leaf   [ ------ ]-*/
NODE_reroot        (void)
{  /*---(design notes)-------------------*/
   /*
    *  a root is created by default, before nodes are read from stdin
    *  if the tree is rooted in a single node, the default is removed
    *  if not, the default provides a single root as required.
    */
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   tNODE      *x_root      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_senter  (__FUNCTION__);
   DEBUG_INPT   yLOG_spoint  (h_node);
   /*---(defense)------------------------*/
   --rce;  if (h_node == NULL) {
      DEBUG_INPT   yLOG_snote   ("no tree to process");
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return rce;
   }
   DEBUG_INPT   yLOG_svalue  ("nchild"    , h_node->nchild);
   --rce;  if (h_node->nchild == 0) {
      DEBUG_INPT   yLOG_snote   ("hit bottom");
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return rce;
   }
   --rce;  if (h_node->nchild > 1) {
      DEBUG_INPT   yLOG_snote   ("already good");
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return rce;
   }
   /*---(identify)-----------------------*/
   --rce;  if (h_node->name != NULL) {
      DEBUG_INPT   yLOG_snote   (h_node->name);
      if (strcmp (h_node->name, ROOT_DEF) != 0) {
         DEBUG_INPT   yLOG_snote   ("already good");
         DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
         return rce;
      }
   }
   /*---(reroot)-------------------------*/
   DEBUG_INPT   yLOG_spoint  (h_node->sib_head);
   DEBUG_INPT   yLOG_spoint  (h_node->next);
   x_root = h_node->sib_head;
   --rce;  if (h_node->next != x_root) {
      DEBUG_INPT   yLOG_snote   ("not well formed");
      DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
      return rce;
   }
   /*---(finalize)-----------------------*/
   DEBUG_INPT   yLOG_snote   ("finalize");
   x_root->prev  == NULL;
   x_root->owner == NULL;
   --n_node;
   free (h_node);
   h_node = x_root;
   DEBUG_INPT   yLOG_spoint  (h_node);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*===============================[[ end-code ]]===============================*/
