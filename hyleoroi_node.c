/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



tNODE      *g_hnode  = NULL;
tNODE      *g_tnode  = NULL;
int         g_nnode  = 0;
tNODE      *g_bnode  = NULL;

static int  s_count  = 0;




/*====================------------------------------------====================*/
/*===----                     program/system level                     ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char             /*=[ prepare for program use ]===========[ ------ [ ------ ]=*/
NODE_init          (void)
{
   /*---(header)-------------------------*/
   DEBUG_NODE   yLOG_enter   (__FUNCTION__);
   g_hnode = NULL;
   g_tnode = NULL;
   g_nnode = 0;
   s_count = 0;
   my.hint_major = 'a';
   my.hint_minor = 'a' - 1;
   /*---(complete)-----------------------*/
   DEBUG_NODE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /*=[ prepare for program use ]===========[ ------ [ ------ ]=*/
NODE_wrap          (void)
{
   /*---(header)-------------------------*/
   DEBUG_NODE   yLOG_enter   (__FUNCTION__);
   /*---(complete)-----------------------*/
   DEBUG_NODE   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         support                              ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;}

char
NODE__wipe              (tNODE *a_curr)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_DATA   yLOG_spoint  (a_curr);
   --rce;  if (a_curr == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(basics)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("basics");
   a_curr->level     =   -1;
   strlcpy (a_curr->label, "-" , LEN_LABEL);
   strlcpy (a_curr->name , "-" , LEN_DESC);
   a_curr->size      =  0.0;
   a_curr->count     =  0.0;
   strlcpy (a_curr->desc , "-" , LEN_DESC);
   strlcpy (a_curr->hint , "--", LEN_TERSE);
   /*---(positioning)--------------------*/
   DEBUG_DATA   yLOG_snote   ("working");
   a_curr->beg       =  0.0;
   a_curr->pct       =  0.0;
   a_curr->width     =  0.0;
   a_curr->end       =  0.0;
   a_curr->color     =    0;
   /*---(master)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("ground master");
   a_curr->m_next    = NULL;
   a_curr->m_prev    = NULL;
   /*---(parent)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("ground parent");
   a_curr->parent    = NULL;
   a_curr->s_prev    = NULL;
   a_curr->s_next    = NULL;
   /*---(children)-----------------------*/
   DEBUG_DATA   yLOG_snote   ("ground children");
   a_curr->c_head    = NULL;
   a_curr->c_tail    = NULL;
   a_curr->nchild    = 0;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
NODE_master_purge       (void)
{
   tNODE      *x_curr      = NULL;
   x_curr = g_hnode;
   while (x_curr != NULL) {
      NODE__master_unhook (x_curr);
      NODE__free          (&x_curr);
      x_curr = g_hnode;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       linking and hooking                    ----===*/
/*====================------------------------------------====================*/
static void      o___HOOKING_________________o (void) {;}

char
NODE__master_find       (tNODE *a_node)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tNODE      *x_curr      = NULL;
   --rce;  if (a_node == NULL) {
      return rce;
   }
   /*---(look)---------------------------*/
   x_curr = g_hnode;
   while (x_curr != NULL) {
      if (x_curr == a_node) {
         return 1;
      }
      x_curr = x_curr->m_next;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
NODE__master_hook       (tNODE *a_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_DATA   yLOG_spoint  (a_new);
   --rce;  if (a_new == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check)--------------------------*/
   rc = NODE__master_find (a_new);
   if (rc == 1) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(first)--------------------------*/
   if (g_hnode == NULL) {
      DEBUG_DATA   yLOG_snote   ("first node");
      g_hnode         = a_new;
      g_tnode         = a_new;
   }
   /*---(additional)---------------------*/
   else {
      DEBUG_DATA   yLOG_snote   ("append node");
      g_tnode->m_next = a_new;
      a_new->m_prev   = g_tnode;
      g_tnode         = a_new;
   }
   /*---(counters)-----------------------*/
   ++g_nnode;
   DEBUG_DATA   yLOG_sint    (g_nnode);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
NODE__master_unhook     (tNODE *a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_DATA   yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check)--------------------------*/
   rc = NODE__master_find (a_old);
   if (rc != 1) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("remove");
   if (a_old->m_next != NULL)    a_old->m_next->m_prev = a_old->m_prev;
   else                          g_tnode               = a_old->m_prev;
   if (a_old->m_prev != NULL)    a_old->m_prev->m_next = a_old->m_next;
   else                          g_hnode               = a_old->m_next;
   /*---(ground)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("ground/safety");
   a_old->m_next = NULL;
   a_old->m_prev = NULL;
   /*---(counters)-----------------------*/
   --g_nnode;
   DEBUG_ENVI   yLOG_complex ("global"   , "%3d, head=%p, tail=%p", g_nnode, g_hnode, g_tnode);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
NODE__parent_find       (tNODE *a_node, tNODE *a_parent)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tNODE      *x_curr      = NULL;
   /*---(defenses)-----------------------*/
   --rce;  if (a_node == NULL) {
      return rce;
   }
   --rce;  if (a_parent == NULL) {
      return rce;
   }
   /*---(look)---------------------------*/
   x_curr = a_parent->c_head;
   while (x_curr != NULL) {
      if (x_curr == a_node) {
         return 1;
      }
      x_curr = x_curr->s_next;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
NODE__parent_hook       (tNODE *a_new, tNODE *a_parent)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_DATA   yLOG_spoint  (a_new);
   --rce;  if (a_new == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_new->parent);
   --rce;  if (a_new->parent != NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_parent);
   /*---(root)---------------------------*/
   if (a_parent == NULL) {
      DEBUG_DATA   yLOG_snote   ("no parent, root");
      DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(check)--------------------------*/
   rc = NODE__parent_find (a_new, a_parent);
   if (rc == 1) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(hook to parent)-----------------*/
   else {
      if (a_parent->c_head  == NULL) {
         DEBUG_DATA   yLOG_snote   ("first child");
         a_parent->c_head         = a_new;
         a_parent->c_tail         = a_new;
      } else {
         DEBUG_DATA   yLOG_snote   ("append child");
         a_new->s_prev            = a_parent->c_tail;
         a_parent->c_tail->s_next = a_new;
         a_parent->c_tail         = a_new;
      }
      ++a_parent->nchild;
      a_new->parent = a_parent;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
NODE__parent_unhook     (tNODE *a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         = NULL;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_DATA   yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ENVI   yLOG_spoint  (a_old->parent);
   --rce;  if (a_old->parent == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check)--------------------------*/
   rc = NODE__parent_find (a_old, a_old->parent);
   if (rc != 1) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("forward");
   if (a_old->s_next != NULL)   a_old->s_next->s_prev = a_old->s_prev;
   else                         a_old->parent->c_tail = a_old->s_prev;
   DEBUG_DATA   yLOG_snote   ("backward");
   if (a_old->s_prev != NULL)   a_old->s_prev->s_next = a_old->s_next;
   else                         a_old->parent->c_head = a_old->s_next;
   /*---(counters)-----------------------*/
   --(a_old->parent->nchild);
   DEBUG_DATA   yLOG_sint    (a_old->parent->nchild);
   /*---(ground)-------------------------*/
   DEBUG_DATA   yLOG_snote   ("ground/safety");
   a_old->parent = NULL;
   a_old->s_next = NULL;
   a_old->s_prev = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      memory allocation                       ----===*/
/*====================------------------------------------====================*/
static void      o___MALLOC__________________o (void) {;}

char
NODE__new          (tNODE **a_new)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_new       = NULL;
   int         x_tries     =    3;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_point   ("a_new"      , a_new);
   /*---(defense)------------------------*/
   DEBUG_ENVI   yLOG_point   ("a_new"     , a_new);
   --rce;  if (a_new == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ENVI   yLOG_point   ("*a_new"    , *a_new);
   --rce;  if (*a_new != NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create ptrs)--------------------*/
   DEBUG_DATA   yLOG_note    ("malloc new node");
   while (x_new == NULL) {
      if (--x_tries <= 0)  break;
      x_new = (tNODE*) malloc (sizeof (tNODE));
   }
   DEBUG_DATA   yLOG_value   ("x_tries"    , x_tries);
   DEBUG_DATA   yLOG_point   ("x_new"      , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_note    ("malloc FAILED");
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   rc = NODE__wipe          (x_new);
   DEBUG_DATA   yLOG_point   ("wipe"       , rc);
   --rce;  if (rc < 0) {
      NODE__free (a_new);
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(counter)------------------------*/
   ++s_count;
   /*---(save back)----------------------*/
   if (a_new != NULL)  *a_new = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
NODE__free              (tNODE **a_old)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_child     = NULL;
   tNODE      *x_next      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_point   ("a_old"      , a_old);
   /*---(defense)------------------------*/
   DEBUG_ENVI   yLOG_point   ("a_old"     , a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ENVI   yLOG_point   ("*a_old"    , *a_old);
   --rce;  if (*a_old == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear)--------------------------*/
   rc = NODE__wipe          (*a_old);
   DEBUG_DATA   yLOG_point   ("wipe"       , rc);
   --rce;  if (rc < 0) {
      NODE__free (*a_old);
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free)---------------------------*/
   DEBUG_DATA   yLOG_note    ("free and ground node");
   free (*a_old);
   *a_old = NULL;
   /*---(counter)------------------------*/
   --s_count;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     creation/destruction                     ----===*/
/*====================------------------------------------====================*/
static void      o___EXIST___________________o (void) {;}

char
NODE_create        (tNODE **a_new, tNODE *a_parent)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   DEBUG_DATA   yLOG_point   ("a_new"      , a_new);
   DEBUG_DATA   yLOG_point   ("a_parent"   , a_parent);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("g_hnode"    , g_hnode);
   --rce;  if (a_parent == NULL && g_hnode != NULL) {
      DEBUG_DATA   yLOG_note    ("already have a root assigned");
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_parent != NULL && g_hnode == NULL) {
      DEBUG_DATA   yLOG_note    ("must create root first");
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(make)---------------------------*/
   rc = NODE__new           (a_new);
   DEBUG_DATA   yLOG_point   ("new"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(hook it up)---------------------*/
   rc = NODE__master_hook   (*a_new);
   DEBUG_DATA   yLOG_point   ("master"     , rc);
   --rce;  if (rc < 0) {
      NODE__free (a_new);
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = NODE__parent_hook   (*a_new, a_parent);
   DEBUG_DATA   yLOG_point   ("parent"     , rc);
   --rce;  if (rc < 0) {
      NODE__master_unhook (*a_new);
      NODE__free          (a_new);
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
NODE_destroy            (tNODE **a_old)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_child     = NULL;
   tNODE      *x_next      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_ENVI   yLOG_point   ("a_old"     , a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ENVI   yLOG_point   ("*a_old"    , *a_old);
   --rce;  if (*a_old == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook it)----------------------*/
   if ((*a_old)->parent != NULL) {
      rc = NODE__parent_unhook (*a_old);
      DEBUG_DATA   yLOG_point   ("parent"     , rc);
      --rce;  if (rc < 0) {
         NODE__free (a_old);
         DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   rc = NODE__master_unhook (*a_old);
   DEBUG_DATA   yLOG_point   ("master"     , rc);
   --rce;  if (rc < 0) {
      NODE__free (a_old);
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = NODE__free (a_old);
   DEBUG_DATA   yLOG_point   ("free"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         rooting tree                         ----===*/
/*====================------------------------------------====================*/
static void      o___ROOTING_________________o (void) {;}

char
NODE_root          (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("g_hnode"   , g_hnode);
   --rce;  if (g_hnode != NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create)-------------------------*/
   rc = NODE_create  (&x_new, NULL);
   DEBUG_INPT   yLOG_value   ("create"    , rc);
   DEBUG_INPT   yLOG_point   ("g_hnode"   , g_hnode);
   --rce;  if (rc < 0 || g_hnode == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(label)--------------------------*/
   strlcpy (g_hnode->label, "ROOT"  , LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*--: collapse redundant roots --------------[ leaf   [ ------ ]-*/
NODE_reroot        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_old       = NULL;
   tNODE      *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_point   ("g_hnode"   , g_hnode);
   --rce;  if (g_hnode == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("nchild"    , g_hnode->nchild);
   if (g_hnode->nchild > 1) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   --rce;  if (g_hnode->nchild == 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save new and old)---------------*/
   DEBUG_INPT   yLOG_note    ("save old and new");
   x_old  = g_hnode;
   x_new  = g_hnode->c_head;
   /*---(unhook from old root)-----------*/
   rc = NODE__parent_unhook (x_new);
   DEBUG_INPT   yLOG_value   ("unhook"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook from old root)-----------*/
   rc = NODE_destroy (&x_old);
   DEBUG_INPT   yLOG_value   ("destroy"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(put new into head)--------------*/
   DEBUG_INPT   yLOG_note    ("save new into head");
   x_new->parent = NULL;
   g_hnode       = x_new;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 1;
}




/*====================------------------------------------====================*/
/*===----                       linking and hooking                    ----===*/
/*====================------------------------------------====================*/
static void      o___OTHER___________________o (void) {;}

char         /*--: show a nodes details ------------------[ leaf   [ ------ ]-*/
NODE_show          (int a_level, tNODE *a_node)
{
   int         i           =    0;          /* generic iterator -- fields     */
   char        x_indent    [100] = "";
   char        x_print     [150] = "";
   if (a_node == NULL) return  -11;
   for (i = 0; i < a_level; ++i)  strcat (x_indent, "   ");
   /*> if ((s_count %  5) == 0)  printf ("\n");                                       <*/
   /*> if ((s_count % 25) == 0)  printf ("                                                                                  ---size-------  ---count------  ---beg-----  ---pct-----  ---width---  ---end-----\n\n");   <*/
   if ((s_count %  5) == 0)  printf ("                                                                                  ---size-------  ---count------  ---beg-----  ---pct-----  ---width---  ---end-----\n");
   sprintf (x_print, "%02d.%02d.%s%s", a_level, a_node->level, x_indent, a_node->name);
   printf ("%-80.80s  %14.0lf  %14.0lf  %11.6f  %11.6f  %11.6f  %11.6f  %3d  %2s\n",
         x_print      ,
         a_node->size , a_node->size , a_node->beg  ,
         a_node->pct  , a_node->width, a_node->end  ,
         a_node->color, a_node->hint);
   ++s_count;
   return 0;
}

tNODE*       /*-> find a node by name/label --------------[ ------ [ ------ ]-*/
NODE_find_name     (char *a_label)
{
   tNODE      *x_curr      = NULL;
   if (a_label == NULL)  return NULL;
   x_curr = g_hnode;
   while (x_curr != NULL) {
      if (x_curr->label != NULL) {
         if (x_curr->label [0] == a_label [0]) {
            if (strcmp (x_curr->label, a_label) == 0)  return x_curr;
         }
      }
      x_curr = x_curr->m_next;
   }
   return NULL;
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
      DEBUG_INPT   yLOG_info    ("a_parent"       ,  "can not be NULL");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*> a_parent->level = a_level;                                                     <*/
   --rce;  if (a_parent->nchild == 0) {
      DEBUG_INPT   yLOG_info    ("nchild"   ,  "no children to process");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(titles)-------------------------*/
   if (a_level == 0) {
      s_count = 0;
      printf ("\n\n");
      printf ("HYLEOROI (forest watchers) tree structure visualization [%s]\n", P_VERNUM);
      printf ("\n");
   }
   /*---(prepare)------------------------*/
   if (a_parent == g_hnode) NODE_show (a_level, a_parent);
   x_curr = a_parent->c_head;
   /*---(show children)------------------*/
   while (x_curr != NULL) {
      NODE_show (a_level + 1, x_curr);
      if (a_recurse == 'y')  NODE_dump (a_level + 1, x_curr, a_recurse);
      x_curr = x_curr->s_next;
   }
   /*---(complete)-------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      unit testing                            ----===*/
/*====================------------------------------------====================*/
static void  o___UNIT_TEST_______o () { return; }

char*        /*-> unit test accessor -----------------[ light  [us.B60.2A3.F2]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
NODE__unit              (char *a_question, tNODE *a_focus, int n)
{
   /*---(locals)-------------------------*/
   char        rc          =    0;
   tNODE      *x_curr      = NULL;
   short       x_fore      =    0;
   short       x_back      =    0;
   char        x_prev      [LEN_LABEL];
   char        x_next      [LEN_LABEL];
   char        t           [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(parse location)-----------------*/
   strcpy  (unit_answer, "NODE             : question not understood");
   /*---(overall)------------------------*/
   if      (strcmp (a_question, "count"         ) == 0) {
      x_curr = g_hnode; while (x_curr != NULL) { ++x_fore; x_curr = x_curr->m_next; }
      x_curr = g_tnode; while (x_curr != NULL) { ++x_back; x_curr = x_curr->m_prev; }
      if (g_hnode == NULL) {
         snprintf (unit_answer, LEN_FULL, "NODE count       : %3dc, %3dn, %3df, %3db    [%-20s] [%-20s]", s_count, g_nnode, x_fore, x_back, "-", "-");
      } else {
         snprintf (unit_answer, LEN_FULL, "NODE count       : %3dc, %3dn, %3df, %3db    [%-20s] [%-20s]", s_count, g_nnode, x_fore, x_back, g_hnode->label, g_tnode->label);
      }
   }
   else if (strcmp (a_question, "nchild"        ) == 0) {
      x_curr = a_focus->c_head; while (x_curr != NULL) { ++x_fore; x_curr = x_curr->s_next; }
      x_curr = a_focus->c_tail; while (x_curr != NULL) { ++x_back; x_curr = x_curr->s_prev; }
      if (a_focus->nchild == 0) {
         snprintf (unit_answer, LEN_FULL, "NODE nchild      : %3dn, %3df, %3db    [%-20s] [%-20s]", a_focus->nchild, x_fore, x_back, "-", "-");
      } else {
         snprintf (unit_answer, LEN_FULL, "NODE nchild      : %3dn, %3df, %3db    [%-20s] [%-20s]", a_focus->nchild, x_fore, x_back, a_focus->c_head->label, a_focus->c_tail->label);
      }
   }
   else if (strcmp (a_question, "exact"         ) == 0) {
      if (a_focus != NULL)  snprintf (unit_answer, LEN_FULL, "NODE exact       : %2d [%-10.10s] [%-15.15s] %10.0lf %6.0lf [%-15.15s] [%-2.2s]", a_focus->level, a_focus->label, a_focus->name, a_focus->size, a_focus->count, a_focus->desc, a_focus->hint);
      else                  snprintf (unit_answer, LEN_FULL, "NODE exact       : -- [- - - - - ] [- - - - - - - -]  - - - - -  - - - [- - - - - - - -] [--]");
   }
   else if (strcmp (a_question, "pointer"       ) == 0) {
      if (a_focus == NULL) {
         strlcpy (unit_answer, "NODE pointer     : [----------] [----------]    [----------]    [----------] [----------]    [----------] [----------] ---", LEN_FULL);
      } else {
         strlcpy (unit_answer, "NODE pointer     : ", LEN_FULL);
         /*---(master)---------*/
         strlcpy (x_prev, "- - - - - ", LEN_LABEL);
         strlcpy (x_next, "- - - - - ", LEN_LABEL);
         if  (a_focus->m_prev != NULL)  sprintf (x_prev, "%-10.10s", a_focus->m_prev->label);
         if  (a_focus->m_next != NULL)  sprintf (x_next, "%-10.10s", a_focus->m_next->label);
         sprintf (t, "[%-10.10s] [%-10.10s]", x_prev, x_next);
         strlcat (unit_answer, t, LEN_FULL);
         /*---(parent)---------*/
         strlcpy (x_prev, "- - - - - ", LEN_LABEL);
         if  (a_focus->parent != NULL)  sprintf (x_prev, "%-10.10s", a_focus->parent->label);
         sprintf (t, "    [%-10.10s]", x_prev);
         strlcat (unit_answer, t, LEN_FULL);
         /*---(siblings)-------*/
         strlcpy (x_prev, "- - - - - ", LEN_LABEL);
         strlcpy (x_next, "- - - - - ", LEN_LABEL);
         if  (a_focus->s_prev != NULL)  sprintf (x_prev, "%-10.10s", a_focus->s_prev->label);
         if  (a_focus->s_next != NULL)  sprintf (x_next, "%-10.10s", a_focus->s_next->label);
         sprintf (t, "    [%-10.10s] [%-10.10s]", x_prev, x_next);
         strlcat (unit_answer, t, LEN_FULL);
         /*---(children)-------*/
         strlcpy (x_prev, "- - - - - ", LEN_LABEL);
         strlcpy (x_next, "- - - - - ", LEN_LABEL);
         if  (a_focus->c_head != NULL)  sprintf (x_prev, "%-10.10s", a_focus->c_head->label);
         if  (a_focus->c_tail != NULL)  sprintf (x_next, "%-10.10s", a_focus->c_tail->label);
         sprintf (t, "    [%-10.10s] [%-10.10s] %3d", x_prev, x_next, a_focus->nchild);
         strlcat (unit_answer, t, LEN_FULL);
         /*---(done)-----------*/
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return unit_answer;
}



/*===============================[[ end-code ]]===============================*/
