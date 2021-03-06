/*===============================[[ beg-code ]]===============================*/
#include    "hyleoroi.h"     /* LOCAL  : main header                          */



#define     LEN_RECD    2000
#define     MAX_FIELD   20


char        s_format    =  '-';

char        s_recd      [LEN_RECD];         /* input record                   */
int         s_level     =    0;
char        s_verb      [LEN_HUND];  
int         s_all       =    0;             /* input line count (all lines)   */
int         s_lines     =    0;             /* input line count (data lines)  */

char        s_fields    [MAX_FIELD][LEN_HUND];
int         s_nfield    =    0;

char        s_proc      =  'y';             /* input processed flag           */

tNODE      *s_nodes     [MAX_DEPTH];


/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
STDIN_init              (void)
{
   strlcpy (my.r_source     , "", LEN_HUND);
   strlcpy (my.r_report     , "", LEN_HUND);
   strlcpy (my.r_oneline    , "", LEN_HUND);
   strlcpy (my.r_option     , "", LEN_HUND);
   strlcpy (my.r_timestamp  , "", LEN_HUND);
   strlcpy (my.r_format     , "", LEN_HUND);
   return 0;
}


/*====================------------------------------------====================*/
/*===----                        support functions                     ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char         /*===[[ read a node ]]=======================[ ------ [ ------ ]=*/
STDIN_check             (void)
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
   x_flags = fcntl (STDIN_FILENO, F_GETFL, 0);
   rc = fcntl (STDIN_FILENO,  F_SETFL, x_flags | O_NONBLOCK);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_value   ("errno"     , errno);
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_INPT   yLOG_note    ("success, non-blocking");
   }
   /*---(test stdin for input)-----------*/
   DEBUG_INPT   yLOG_note    ("test for input on stdin");
   x_ch = getc (stdin);
   ungetc (x_ch, stdin);
   /*---(put stdin back to normal)-------*/
   DEBUG_INPT   yLOG_note    ("put stdin back to blocking");
   rc = fcntl  (STDIN_FILENO, F_SETFL, x_flags);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_value   ("errno"     , errno);
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_INPT   yLOG_note    ("success, back to blocking");
   }
   /*---(test stdin for input)-----------*/
   DEBUG_INPT   yLOG_value   ("x_ch"      , x_ch);
   --rce;  if (x_ch == -1) {
      DEBUG_INPT   yLOG_note    ("no input available");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      DEBUG_INPT   yLOG_note    ("success, input found");
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
STDIN__field_clear       (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_FIELD; ++i) {
      strlcpy (s_fields [i], "", LEN_HUND);;
   }
   s_nfield = 0;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         getting lines                        ----===*/
/*====================------------------------------------====================*/
static void  o___GETTING_________o () { return; }

char
STDIN__getline          (void)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   char       *p           = NULL;
   int         x_len       =    0;
   int         c           =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   strlcpy (s_recd, ""    , LEN_RECD);
   /*---(read)---------------------------*/
   while (1) {
      /*---(read a line)--------------------*/
      ++s_all;
      DEBUG_INPT   yLOG_value   ("s_all"     , s_all);
      p = fgets (x_recd, LEN_RECD, stdin);
      DEBUG_INPT   yLOG_value   ("fgets"     , rc);
      DEBUG_INPT   yLOG_point   ("p"         , p);
      --rce;  if (feof (stdin)) {
         DEBUG_INPT   yLOG_note    ("end of file input");
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      --rce;  if (p == NULL) {
         DEBUG_INPT   yLOG_note    ("end of file input");
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(reformat)-----------------------*/
      x_len = strlen (x_recd);
      x_recd [--x_len] = '\0';
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      --rce;  if (x_len <= 0) {
         DEBUG_INPT   yLOG_note    ("empty line, skipping");
         continue;
      }
      /*---(filter)-------------------------*/
      strldecode (x_recd, LEN_RECD);
      DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
      --rce;  if (x_recd [0] == '#' ) {
         DEBUG_INPT   yLOG_note    ("comment line, skipping");
         continue;
      }
      /*---(delimiters)---------------------*/
      c = strldcnt (x_recd, '', LEN_RECD);
      if (c == 0)  c = strldcnt (x_recd, '�', LEN_RECD);
      if (c == 0)  c = strldcnt (x_recd, '|', LEN_RECD);
      DEBUG_INPT   yLOG_value   ("count"     , c);
      --rce;  if (c < 1) {
         DEBUG_INPT   yLOG_note    ("not enough delimiters");
         continue;
      }
      /*---(get level)----------------------*/
      c = 0;
      for (i = 0; i < x_len; ++i) {
         if (x_recd [i] != ' ')  break;
         ++c;
      }
      DEBUG_INPT   yLOG_value   ("indent"    , c);
      s_level = c / 3;
      /*---(update)-------------------------*/
      ++s_lines;
      DEBUG_INPT   yLOG_value   ("s_lines"   , s_lines);
      break;
      /*---(done)---------------------------*/
   }
   /*---(save back)----------------------*/
   strlcpy (s_recd, x_recd, LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
STDIN__parse            (void)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         x_len       =    0;
   char       *p           = NULL;
   char       *q           = "|�";
   char       *r           = NULL;
   char        x_recd      [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(clear)--------------------------*/
   STDIN__field_clear ();
   /*---(parse)--------------------------*/
   strlcpy (x_recd, s_recd, LEN_RECD);
   s_nfield = 0;
   p = strtok_r  (x_recd, q, &r);
   while (p != NULL) {
      if (s_nfield >= MAX_FIELD)   break;
      if (p == NULL)               break;
      DEBUG_INPT   yLOG_complex ("content"   , "%2d, %s", s_nfield, p);
      strltrim (p, ySTR_BOTH, LEN_HUND);
      strlcpy (s_fields [s_nfield], p, LEN_HUND);
      ++s_nfield;
      p = strtok_r  (NULL  , q, &r);
   }
   DEBUG_INPT   yLOG_value   ("s_nfield"  , s_nfield);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     specific handlers                        ----===*/
/*====================------------------------------------====================*/
static void  o___HANDLERS________o () { return; }

char
STDIN__verbs            (void)
{
   /*---(local variables)--+-----------+-*/
   char        rce         =  -10;          /* return code for errors         */
   /*---(quick-out)----------------------*/
   if (s_fields [0][0] != '>')  return 0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(formatting)---------------------*/
   if (strcmp (s_fields [0], ">format"     ) == 0) {
      DEBUG_INPT   yLOG_note    ("display format");
      strlcpy (my.r_format   , s_fields [1], LEN_HUND);
      FORMAT_set     (s_fields [1]);
   }
   /*---(text labels)--------------------*/
   else if (strcmp (s_fields [0], ">source"     ) == 0) {
      DEBUG_INPT   yLOG_note    ("source program name");
      strlcpy (my.r_source  , s_fields [1], LEN_HUND);
   }
   else if (strcmp (s_fields [0], ">report"     ) == 0) {
      DEBUG_INPT   yLOG_note    ("source program report name");
      strlcpy (my.r_report  , s_fields [1], LEN_HUND);
   }
   else if (strcmp (s_fields [0], ">option"     ) == 0) {
      DEBUG_INPT   yLOG_note    ("source program option used");
      strlcpy (my.r_option  , s_fields [1], LEN_HUND);
   }
   else if (strcmp (s_fields [0], ">one-line"   ) == 0) {
      DEBUG_INPT   yLOG_note    ("source program report description");
      strlcpy (my.r_oneline , s_fields [1], LEN_HUND);
   }
   else if (strcmp (s_fields [0], ">timestamp"  ) == 0) {
      DEBUG_INPT   yLOG_note    ("date data generated");
      strlcpy (my.r_timestamp, s_fields [1], LEN_HUND);
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
STDIN__node        (int a_level, char *a_name, long a_value, int a_count, char *a_desc)
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
   NODE_create (&x_curr, s_nodes [a_level - 1]);
   /*---(add values)---------------------*/
   strlcpy (x_curr->label, a_name,  12);
   strlcpy (x_curr->name , a_name,  50);
   x_curr->size  = a_value;
   x_curr->count = a_count;
   strlcpy (x_curr->desc , a_desc, 200);
   /*---(assign color)----------------*/
   x_curr->level    = a_level;
   x_curr->color = yCOLOR_diff_next ();
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
FILE__line              (void)
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
   for (i = 0; i < MAX_FIELD; ++i)  strlcpy (s_fields [i], "", LEN_HUND);
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
   /*---(parse)--------------------------*/
   strlcpy (x_recd, s_recd, LEN_RECD);
   s_nfield = 0;
   p = strtok_r  (x_recd, q, &r);
   while (p != NULL) {
      if (s_nfield >= MAX_FIELD)   break;
      if (p == NULL)               break;
      DEBUG_INPT   yLOG_complex ("content"   , "%2d, %s", s_nfield, p);
      strlcpy (s_fields [s_nfield], p, LEN_HUND);
      ++s_nfield;
      p = strtok_r  (NULL  , q, &r);
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
   char       *x_metas     = "  source  label  format  ";
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
   strlcpy  (s_verb, s_fields [0], LEN_HUND);
   strltrim (s_verb, ySTR_BOTH, LEN_HUND);
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
      strltrim (s_fields [1], ySTR_BOTH, LEN_HUND);
      DEBUG_INPT   yLOG_info    ("s_fields 1", s_fields [1]);
      switch (s_verb [0]) {
      case 's' :
         DEBUG_INPT   yLOG_note    ("source program name");
         strlcpy (my.r_source, s_fields [1], LEN_HUND);
         break;
      case 'l' :
         DEBUG_INPT   yLOG_note    ("source program report/label");
         strlcpy (my.r_report, s_fields [1], LEN_HUND);
         break;
      case 'f' :
         DEBUG_INPT   yLOG_note    ("display format");
         FORMAT_set     (s_fields [1]);
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
   NODE_create (&x_curr, s_nodes [a_level - 1]);
   /*---(add values)---------------------*/
   strlcpy (x_curr->label, a_name,  12);
   strlcpy (x_curr->name , a_name,  50);
   x_curr->size  = a_value;
   x_curr->count = a_count;
   strlcpy (x_curr->desc , a_desc, 200);
   /*---(assign color)----------------*/
   x_curr->level    = a_level;
   x_curr->color = yCOLOR_diff_next ();
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
   char        x_name      [LEN_HUND];
   char        x_desc      [LEN_HUND];
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
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
      rc = FILE__line ();
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
         strlcpy  (x_name, s_fields [2], LEN_HUND);
         strltrim (x_name, ySTR_BOTH, 200);
         x_value = atol (s_fields [3]);
         x_count = atoi (s_fields [4]);
         strlcpy  (x_desc, s_fields [5], LEN_HUND);
         strltrim (x_desc, ySTR_BOTH, 200);
         FILE_node (x_level, x_name, x_value, x_count, x_desc);
         break;
      case 'S' :
         strlcpy  (x_name, s_fields [0], LEN_HUND);
         strltrim (x_name, ySTR_TAIL, 200);
         x_len = strlen (x_name);
         strltrim (x_name, ySTR_HEAD, 200);
         x_level = 1 + (x_len - strlen (x_name)) / 3;
         x_value = atol (s_fields [1]);
         x_count = atoi (s_fields [2]);
         strlcpy  (x_desc, s_fields [3], LEN_HUND);
         strltrim (x_desc, ySTR_BOTH, 200);
         FILE_node (x_level, x_name, x_value, x_count, x_desc);
         break;
      default  :
         strlcpy  (x_name, s_fields [0], LEN_HUND);
         strltrim (x_name, ySTR_TAIL, 200);
         x_len = strlen (x_name);
         strltrim (x_name, ySTR_HEAD, 200);
         x_level = 1 + (x_len - strlen (x_name)) / 3;
         x_value = atol (s_fields [1]);
         x_count = atoi (s_fields [2]);
         strlcpy  (x_desc, s_fields [3], LEN_HUND);
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
            DEBUG_INPT   yLOG_info    ("x_curr is NULL" ,  "double jump detected, abort");
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
      NODE_create (&x_curr, a_owner);
      if (x_curr == NULL) {
         DEBUG_INPT   yLOG_info    ("x_curr is NULL" ,  "could not create a new node");
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
      x_curr->color = yCOLOR_diff_next ();
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



/*====================------------------------------------====================*/
/*===----                      unit testing                            ----===*/
/*====================------------------------------------====================*/
static void  o___UNIT_TEST_______o () { return; }

char*        /*-> unit test accessor -----------------[ light  [us.B60.2A3.F2]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
STDIN__unit             (char *a_question, int n)
{
   /*---(locals)-------------------------*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF   yLOG_enter   (__FUNCTION__);
   /*---(parse location)-----------------*/
   strcpy  (unit_answer, "STDIN            : question not understood");
   /*---(overall)------------------------*/
   if      (strcmp (a_question, "s_recd"        ) == 0) {
      strlencode (s_recd, ySTR_NORM, LEN_RECD);
      snprintf (unit_answer, LEN_FULL, "STDIN s_recd     : %2d %2d[%.79s]", s_level, strlen (s_recd), s_recd);
   }
   else if (strcmp (a_question, "field"         ) == 0) {
      snprintf (unit_answer, LEN_FULL, "STDIN field (%2d) : %2d[%.50s]", n, strlen (s_fields [n]), s_fields [n]);
   }
   else if (strcmp (a_question, "source"        ) == 0) {
      snprintf (unit_answer, LEN_FULL, "STDIN source     : [%.79s]", my.r_source);
   }
   else if (strcmp (a_question, "report"        ) == 0) {
      snprintf (unit_answer, LEN_FULL, "STDIN report     : [%.79s]", my.r_report);
   }
   else if (strcmp (a_question, "one-line"      ) == 0) {
      snprintf (unit_answer, LEN_FULL, "STDIN one-line   : [%.79s]", my.r_oneline);
   }
   else if (strcmp (a_question, "option"        ) == 0) {
      snprintf (unit_answer, LEN_FULL, "STDIN option     : [%.79s]", my.r_option);
   }
   else if (strcmp (a_question, "timestamp"     ) == 0) {
      snprintf (unit_answer, LEN_FULL, "STDIN timestamp  : [%.79s]", my.r_timestamp);
   }
   else if (strcmp (a_question, "format"        ) == 0) {
      snprintf (unit_answer, LEN_FULL, "STDIN format     : [%.79s]", my.r_format);
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF   yLOG_exit    (__FUNCTION__);
   return unit_answer;
}

