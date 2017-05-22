/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



#define     LEN_RECD    2000
#define     MAX_FIELD   20
#define     LEN_FIELD   200


char        s_format    =  '-';

char        s_recd      [LEN_RECD];         /* input record                   */
char        s_verb      [LEN_FIELD];
int         s_all       =    0;             /* input line count (all lines)   */
int         s_lines     =    0;             /* input line count (data lines)  */

char        s_fields    [MAX_FIELD][LEN_FIELD];
int         s_nfield    =    0;

char        s_proc      =  'y';             /* input processed flag           */

tNODE      *s_nodes     [MAX_DEPTH];
int         s_level     =    0;


char         /*===[[ read a node ]]=======================[ ------ [ ------ ]=*/
FILE_check         (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;
   int         x_flags     =    0;
   int         x_ch        =  ' ';
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(set stdin to non-blocking)------*/
   DEBUG_INPT   yLOG_note    ("make stdin non-blocking");
   x_flags = fcntl(0, F_GETFL, 0);
   rc = fcntl (stdin, F_SETFL, x_flags | O_NONBLOCK);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   /*> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_INPT   yLOG_note    ("can not set to non-blocking");                  <* 
    *>    DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(test stdin for input)-----------*/
   DEBUG_INPT   yLOG_note    ("test for input on stdin");
   x_ch = getc (stdin);
   DEBUG_INPT   yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch == -1) {
      DEBUG_INPT   yLOG_note    ("no input available");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(put stdin back to normal)-------*/
   DEBUG_INPT   yLOG_note    ("put stdin back to normal");
   ungetc (x_ch, stdin);
   rc = fcntl  (0, F_SETFL, x_flags);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   /*> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_INPT   yLOG_note    ("can not set to back to normal");                <* 
    *>    DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ read a node ]]=======================[ ------ [ ------ ]=*/
FILE_line          (void)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   int         i           =    0;
   int         x_len       =    0;          /* input record length            */
   char       *p           = NULL;          /* strtok_r current pointer       */
   char       *q           = "|";         /* strtok_r delimeters            */
   char       *r           = NULL;          /* strtok_r context variable      */
   char        x_recd      [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   for (i = 0; i < MAX_FIELD; ++i)  strlcpy (s_fields [i], "", LEN_FIELD);
   /*---(read a line)--------------------*/
   ++s_all;
   DEBUG_INPT   yLOG_value   ("s_all"     , s_all);
   fgets (s_recd, LEN_RECD, stdin);
   --rce;  if (feof (stdin)) {
      DEBUG_INPT   yLOG_note    ("end of file input");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(reformat)-----------------------*/
   x_len = strlen (s_recd);
   s_recd [--x_len] = '\0';
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len <= 0) {
      DEBUG_INPT   yLOG_note    ("empty line, skipping");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, -(rce));
      return -(rce);
   }
   /*---(filter)-------------------------*/
   DEBUG_INPT   yLOG_info    ("s_recd"    , s_recd);
   --rce;  if (s_recd [0] == '#' ) {
      DEBUG_INPT   yLOG_note    ("comment line, skipping");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, -(rce));
      return -(rce);
   }
   ++s_lines;
   DEBUG_INPT   yLOG_value   ("s_lines"   , s_lines);
   /*---(parse first)--------------------*/
   strlcpy (x_recd, s_recd, LEN_RECD);
   p = strtok_r  (x_recd, q, &r);
   --rce;  if (p == NULL) {
      DEBUG_INPT   yLOG_note    ("no data on line");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, -(rce));
      return -(rce);
   }
   s_nfield = 1;
   strlcpy (s_fields, p, LEN_FIELD);
   /*---(parse rest)---------------------*/
   for (i = 1; i < MAX_FIELD; ++i) {
      p = strtok_r  (NULL  , q, &r);
      if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("fields done");
         break;
      }
      DEBUG_INPT   yLOG_value   ("field"     , i);
      DEBUG_INPT   yLOG_info    ("content"   , p);
      strlcpy (s_fields [i], p, LEN_FIELD);
      ++s_nfield;
   }
   DEBUG_INPT   yLOG_value   ("s_nfield"  , s_nfield);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ read a node ]]=======================[ ------ [ ------ ]=*/
FILE_verb          (void)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   char       *x_formats   = "  FULL  FULL-FORMAT  SIMPLE  SIMPLE-FORMAT  ";
   char       *x_metas     = "  source  label  display  rings  ";
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_info    ("s_fields 0", s_fields [0]);
   --rce;  if (s_fields [0][0] == ' ') {
      DEBUG_INPT   yLOG_note    ("initial space, so no verb");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(isolate verb)-------------------*/
   strlcpy  (s_verb, s_fields [0], LEN_FIELD);
   strltrim (s_verb, ySTR_BOTH, LEN_FIELD);
   DEBUG_INPT   yLOG_info    ("s_verb"    , s_verb);
   /*---(format styles)------------------*/
   --rce;  if (strstr (x_formats, s_verb) != NULL) {
      switch (s_verb [0]) {
      case 'F' :
         DEBUG_INPT   yLOG_note    ("full/verb format file");
         s_format = 'F';
         break;
      case 'S' :
         DEBUG_INPT   yLOG_note    ("simple/indented format file");
         s_format = 'S';
         break;
      }
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, -(rce));
      return -(rce);
   }
   /*---(meta-data)----------------------*/
   --rce;  if (strstr (x_metas   , s_verb) != NULL) {
      DEBUG_INPT   yLOG_value   ("s_nfield"  , s_nfield);
      --rce;  if (s_nfield <  2) {
         DEBUG_INPT   yLOG_note    ("not the right number of fields for a meta");
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      strltrim (s_fields [1], ySTR_BOTH, LEN_FIELD);
      DEBUG_INPT   yLOG_info    ("s_fields 1", s_fields [1]);
      switch (s_verb [0]) {
      case 's' :
         DEBUG_INPT   yLOG_note    ("source program name");
         strlcpy (my.source, s_fields [1], LEN_FIELD);
         break;
      case 'l' :
         DEBUG_INPT   yLOG_note    ("source program report/label");
         strlcpy (my.report, s_fields [1], LEN_FIELD);
         break;
      }
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, -(rce));
      return -(rce);
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FILE_node          (int a_level, char *a_name, long a_value, int a_count, char *a_desc)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   tNODE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_value   ("a_level"   , a_level);
   --rce;  if (a_level < 1) {
      DEBUG_INPT   yLOG_note    ("can not add another root");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("s_level"   , s_level);
   --rce;  if (a_level > s_level + 1) {
      DEBUG_INPT   yLOG_note    ("can not double jump");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_INPT   yLOG_note    ("name must have a value");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(append)-------------------------*/
   x_curr = NODE_append (s_nodes [a_level - 1]);
   /*---(add values)---------------------*/
   strlcpy (x_curr->label, a_name,  12);
   strlcpy (x_curr->name , a_name,  50);
   x_curr->size  = a_value;
   x_curr->count = a_count;
   strlcpy (x_curr->desc , a_name, 200);
   /*---(assign color)----------------*/
   x_curr->level    = a_level;
   if (my.chaos == 'y')   x_curr->color = rand_r (&(my.color_seed)) % g_ncolor;
   else {
      if (my.color >= g_ncolor)  my.color -= g_ncolor;
      x_curr->color    = my.color;
      ++my.color;
   }
   /*> printf ("%2d.%-40.40s  %3d\n", x_curr->level, x_curr->label, x_curr->color);   <*/
   /*---(assign hint)-----------------*/
   if (++(my.hint_minor) > 'z') {
      my.hint_minor = 'a';
      ++(my.hint_major);
   }
   if (my.hint_major > 'z') {
      my.hint_minor = '{';
      my.hint_major = '}';
   }
   x_curr->hint [0] = my.hint_major;
   x_curr->hint [1] = my.hint_minor;
   x_curr->hint [2] = '\0';
   /*---(put into order)--------------*/
   s_nodes [a_level] = x_curr;
   s_level           = a_level;
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ read a node ]]=======================[ ------ [ ------ ]=*/
FILE_main          (void)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* return code for character      */
   int         x_len       =    0;          /* input record length            */
   int         i           =    0;
   int         x_level     =    0;          /* node level                     */
   long        x_value     =    0;          /* node level                     */
   int         x_count     =    0;          /* node level                     */
   char        x_name      [LEN_FIELD];
   char        x_desc      [LEN_FIELD];
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(check for input)----------------*/
   rc = FILE_check ();
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      printf ("warning.  nothing to do.  can not find any input on stdin.  done.\n");
      return rce;
   }
   /*---(prepare)------------------------*/
   s_nodes [0] = g_hnode;
   for (i = 1; i < MAX_DEPTH; ++i) {
      s_nodes [i] = NULL;
      s_level = 1;
   }
   /*---(process file)-------------------*/
   DEBUG_INPT   yLOG_note    ("start reading file");
   while (1) {
      /*---(take in a line)--------------*/
      rc = FILE_line ();
      if (rc > 0) continue;  /* filtered line     */
      if (rc < 0) break;     /* end-of-input      */
      /*---(check mode)------------------*/
      rc = FILE_verb ();
      if (rc > 0) continue;  /* handled correctly */
      if (rc < 0) continue;  /* badly formatted   */
      /*---(check nodes)-----------------*/
      x_level = 0;
      switch (s_format) {
      case 'F' :
         DEBUG_INPT   yLOG_info    ("s_verb"    , s_verb);
         if (strcmp ("node", s_verb) != 0) {
            DEBUG_INPT   yLOG_note    ("full format node not a verb match");
            continue;
         }
         DEBUG_INPT   yLOG_value   ("s_nfield"  , s_nfield);
         if (s_nfield <  4)  {
            DEBUG_INPT   yLOG_note    ("full format node does not have at least four fields");
            continue;
         }
         x_level = atoi (s_fields [1]);
         strlcpy  (x_name, s_fields [2], LEN_FIELD);
         strltrim (x_name, ySTR_BOTH, 200);
         x_value = atol (s_fields [3]);
         x_count = atoi (s_fields [4]);
         strlcpy  (x_desc, s_fields [5], LEN_FIELD);
         strltrim (x_desc, ySTR_BOTH, 200);
         FILE_node (x_level, x_name, x_value, x_count, x_desc);
         break;
      case 'S' :
         strlcpy  (x_name, s_fields [0], LEN_FIELD);
         strltrim (x_name, ySTR_TAIL, 200);
         x_len = strlen (x_name);
         strltrim (x_name, ySTR_HEAD, 200);
         x_level = 1 + (x_len - strlen (x_name)) / 3;
         x_value = atol (s_fields [1]);
         x_count = atoi (s_fields [2]);
         strlcpy  (x_desc, s_fields [3], LEN_FIELD);
         strltrim (x_desc, ySTR_BOTH, 200);
         FILE_node (x_level, x_name, x_value, x_count, x_desc);
         break;
      default  :
         strlcpy  (x_name, s_fields [0], LEN_FIELD);
         strltrim (x_name, ySTR_TAIL, 200);
         x_len = strlen (x_name);
         strltrim (x_name, ySTR_HEAD, 200);
         x_level = 1 + (x_len - strlen (x_name)) / 3;
         x_value = atol (s_fields [1]);
         x_count = atoi (s_fields [2]);
         strlcpy  (x_desc, s_fields [3], LEN_FIELD);
         strltrim (x_desc, ySTR_BOTH, 200);
         FILE_node (x_level, x_name, x_value, x_count, x_desc);
         break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*===[[ read a node ]]=======================[ ------ [ ------ ]=*/
FILE_read          (
      /*---(formal parameters)+-------------+---------------------------------*/
      int        a_level      ,             /* recursion/hierarchy level      */
      tNODE     *a_owner      )             /* owner for this level           */
{  /*---(local variables)--+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   char        rc          =    0;          /* return code for character      */
   char       *rcs         = NULL;          /* return code for c-string       */
   int         x_len       =    0;          /* input record length            */
   char       *p           = NULL;          /* strtok pointer                 */
   char       *q           = "|";         /* strtok delimeters              */
   int         i           =    0;          /* generic iterator -- fields     */
   int         x_indent    =    0;          /* indent level                   */
   tNODE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_value   ("a_level"   , a_level);
   DEBUG_INPT   yLOG_point   ("a_owner"   , a_owner);
   /*---(defense)------------------------*/
   --rce;  if (a_owner == NULL) {
      DEBUG_INPT   yLOG_note    ("level owner NULL, failed");
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(read lines)---------------------*/
   while (1) {
      if (s_proc == 'y') {
         /*---(read and clean)--------------*/
         DEBUG_INPT   yLOG_note    ("read a new record");
         s_proc = '-';
         ++s_lines;
         DEBUG_INPT   yLOG_value   ("line"      , s_lines);
         rcs    = fgets (s_recd, LEN_RECD, stdin);
         if (rcs == NULL) {
            DEBUG_INPT   yLOG_note    ("fgets read NULL, finished");
            DEBUG_INPT   yLOG_exit    (__FUNCTION__);
            return  -1;
         }
         x_len = strlen (s_recd);
         if (x_len <= 0) {
            DEBUG_INPT   yLOG_note    ("blank line, filtered");
            s_proc = 'y';
            continue;
         }
         s_recd [--x_len] = '\0';
         DEBUG_INPT   yLOG_info    ("fixed"     , s_recd);
         /*---(filter)----------------------*/
         if (s_recd [0] == '#' || s_recd [0] == '\0') {
            DEBUG_INPT   yLOG_note    ("comment/spacer, filtered");
            s_proc = 'y';
            continue;
         }
      } else {
         DEBUG_INPT   yLOG_note    ("continue using existing record");
      }
      /*---(level)-----------------------*/
      x_indent = 0;
      for (i = 0; i < 100; ++i) {
         if (s_recd [i] != ' ')   break;
         if ((i % 3) == 2)        ++x_indent;
      }
      if (x_indent < a_level) {
         DEBUG_INPT   yLOG_note    ("indent level decreased, level done");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      if (x_indent > a_level) {
         DEBUG_INPT   yLOG_note    ("indent level increased, new level");
         if (x_curr == NULL) {
            DEBUG_INPT   yLOG_warn    ("x_curr is NULL" ,  "double jump detected, abort");
            DEBUG_INPT   yLOG_exit    (__FUNCTION__);
            return -2;
         }
         rc = FILE_read (a_level + 1, x_curr);
         if (rc < 0) {
            DEBUG_INPT   yLOG_exit    (__FUNCTION__);
            return rc;
         }
         continue;
      }
      /*---(create node)-----------------*/
      x_curr = NODE_append (a_owner);
      if (x_curr == NULL) {
         DEBUG_INPT   yLOG_warn    ("x_curr is NULL" ,  "could not create a new node");
         DEBUG_INPT   yLOG_exit    (__FUNCTION__);
         return rce + 1;
      }
      /*---(get fields)------------------*/
      s_proc = 'y';
      p = strtok (s_recd, q);
      for (i = 0; i < 5; ++i) {
         if (p == NULL)                               break;
         strltrim (p, ySTR_BOTH, 200);
         switch (i) {
         case  0 : strncpy (x_curr->label, p,  12);
                   strncpy (x_curr->name , p,  50);   break;
         case  1 : x_curr->size  = atof (p);          break;
         case  2 : x_curr->count = atof (p);          break;
         case  3 : strncpy (x_curr->desc , p, 200);   break;
         default : break;
         }
         p = strtok (NULL  , q);
      }
      if (a_level == 1 && strcmp (x_curr->label, "((empty))") == 0)  my.empty = x_curr;
      if (a_level == 1 && strcmp (x_curr->label, "empty"    ) == 0)  my.empty = x_curr;
      /*---(assign system gen)-----------*/
      x_curr->level    = a_level;
      if (my.chaos == 'y')   x_curr->color = rand() % g_ncolor;
      else {
         if (my.color >= g_ncolor)  my.color -= g_ncolor;
         x_curr->color    = my.color;
         ++my.color;
      }
      if (++(my.hint_minor) > 'z') {
         my.hint_minor = 'a';
         ++(my.hint_major);
      }
      if (my.hint_major > 'z') {
         my.hint_minor = '{';
         my.hint_major = '}';
      }
      x_curr->hint [0] = my.hint_major;
      x_curr->hint [1] = my.hint_minor;
      x_curr->hint [2] = '\0';
      /*---(done)------------------------*/
   }
   /*---(complete)-------------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}
