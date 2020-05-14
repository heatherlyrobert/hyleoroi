/*===============================[[ beg-code ]]===============================*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "VS (visualization)"
#define     P_NICHE     "ds (data structures)"
#define     P_PURPOSE   "provide visualization and navigation of tree structures"

#define     P_NAMESAKE  "hyleoroi"
#define     P_HERITAGE  "warrior nymphs, watchers of the woods and trees"
#define     P_IMAGERY   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2014-01"
#define     P_DEPENDS   "none"

#define     P_VERMAJOR  "0.--, pre-production"
#define     P_VERMINOR  "0.7-, building up to production use"
#define     P_VERNUM    "0.7b"
#define     P_VERTXT    "restructured and unit tested node file/interface"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"



/*===[[ HEADER ]]=============================================================*/
/*
 *   focus         : visualization
 *   niche         : data structures
 *   heritage      : hyleoroi (warrior nymphs, watchers of the woods and trees)
 *   purpose       : provide visualization and navigation of tree structures
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : ansi-c      (wicked, limitless, universal, and everlasting)
 *   dependencies  : none
 *   size          : small       (approximately 1,000 slocL)
 * 
 *   author        : heatherly
 *   created       : 2014-01
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, portable
 */

/*===[[ GREEK HERITAGE ]]=====================================================*/
/*
 *   dyades are the beautiful nymphs of the trees, groves, woods, and mountain
 *   forests.  They were ladies of the oaks and pines, poplar and ash, apple
 *   and laurel.  the numbers of dyades are infinite.  unlike other dyades,
 *   hyleoroi are warrior nymphs that patrol and protect the woodlands and are
 *   not beholden to a particular type of tree or area.
 */

/*===[[ REASONING ]]==========================================================*/
/*
 *
 *   problem statement (p) ---------------------------------
 *
 *   there are a number of tools that visualize various forms of hierarchies,
 *   which are forms of trees, but each is typically specialized, has its own
 *   interface, and collects its own data.  many application use trees and
 *   many logical arrangements are hierarchies.  the issue is a visualization
 *   method must be found or built for each instance to do any analysis.
 */
/*
 *   requirement and reward (rr)---------------------------
 *
 *   hierachical and tree structures follow a number of very clear rules which
 *   make them very regular.  the requirement is to create a visualization and
 *   navagation tool that can show trees in a number of representations and
 *   allow the user to navagate through the structure easily.
 *
 *      -- more quickly identify incorrect links and patterns
 *      -- tremendously speed debugging by having a ready-made tool
 *      -- find issues sooner in development and collection
 *      -- improve analysis and conclusions on datasets
 */
/*
 *   objectives (o) ---------------------------------------
 *
 *   objectives and ideas have been collected by reviewing tools that normally
 *   fit into the same functional area, including, baobab, filesight, kdirstat,
 *   and xdiskusage.
 *
 *   hyleoroi will provide the following types of visualization methods...
 *
 *   1) node-link diagram.
 *      -- each node is a small circle and each link is a stright line
 *      -- the root is placed at the top-center
 *      -- each layer of the tree is lined up horizontally for easy comparison
 *      -- nodes are typically labeled with vertical text below them
 *      -- makes for easy identification of imbalances and skewing
 *
 *   2) dentrogram/cluster diagram.
 *      -- each node is a small circle and each link is a stright line
 *      -- the root is placed in the very center
 *      -- the leaves/bottom nodes are arranged in an outside circle
 *      -- interviening nodes are centered over their leaves
 *      -- allows a far greater amount of information to fit in the same space
 *
 *   3) outline/indented diagrams.
 *      -- nodes are listed vertically with parents appearing before children
 *      -- vertical spacing is uniform, but nodes are indented for each level
 *      -- uses excessive vertical space, but useful for scanning
 *
 *   4) icicle adjacency diagram.
 *      -- nodes are equal-hieght rectangles that run top to bottom by layer
 *      -- the root node is on top and fills the entire left-to-right space
 *      -- each successive layer has nodes with width to cover all children
 *      -- each leaf node is either equal width or varies based on an attribute
 *      -- allows scaling factors to be used in reprensentation
 *    
 *   5) sunburst adjacency diagram.
 *      -- a radial/polor version of the icicle diagram
 *
 *
 *
 *
 *
 *
 *
 *      -- horizontal tree, which looks like a typical organization chart
 *      -- vertical tree, which runs from left to right
 *      -- radial tree, which organizes in rings from inside to out
 *
 *
 *
 *      -- search a database of files rather than the file system itself (speed)
 *      -- update the database in batch as most almost never change (efficiency)
 *      -- allow literal, gobbing, and regex searches
 *      -- only allow a user to see dirs and files to which they have access
 *      -- able to produce database statistics
 *      -- limit the number of entries found to stop early (for speed)
 *
 *   and, will add the following file location objectives...
 *      -- search for files below, near, or above a certain size
 *      -- search for files updated before, during, or after certain times
 *      -- limit to files of a certain owner or group
 *      -- limit search to certain directories and/or their subdirectories
 *      -- provide ability to merge databases across machines for network use
 *      -- provide directories, file types, and file masks to ignore/blackout
 *      -- audit the database to verify files are still there (full run)
 *      -- report on poorly named files using illegal characters
 *      -- add file types from the file command standard
 *      -- generate output files for various viewers
 *      -- also track directories in the same way as files (size, perms, ...)
 *
 *   but, will not...
*      -- update database with only new enteries (runs too fast anyway)
*      -- provide any scripting to process files specially
*      -- call any external programs directly
*      -- provide any graphical viewing directly (use external tools)
*
*   above all, it is all about...
*      -- learning the key niches in computer and system work
*      -- expanding my knowledge base in useful ways
*      -- becoming a more masterful and stronger system programmer
* 
*   as always, applications running on my systems must...
*      -- forgo sloppy, kitchen-sink languages, like python, java, or perl
*      -- stay focused, small, tight, reliable, and secure
*      -- only use human maintainable, 7-bit safe, ascii streams (not database)
*      -- have dedicated, maintained, automated unit testing
*      -- provide either detailed reporting or logging for debugging
*      -- use secure communications between systems where required
*      -- clean, clean code so i can maintain after long absences
*      -- no international, multi-language, multi-byte support (freaking ever)
*/







/*---[[ PURPOSE ]]------------------------------------------------------------*

 *   information graphics are consistent visual shorthand techniques used to
 *   communicate critical, complex, or unwieldy data in unique, stylized, and
 *   simplified ways allowing knowledge to be transferred and digested quickly
 *   and clearly.  these techniques can be separated into charts, diagrams,
 *   graphs, tables, maps, and lists.
 *
 *
 *
 *
 *
 *   rtree is a visualization tool for large tree structures which places them
 *   in a radial format for compact viewing and navigation.
 *
 *   variations...
 *      - vtree     : sideways, vertical tree
 *      - htree     : normal tree view
 *      - rtree     : radial tree
 *      - stree     : sunburst tree
 *      - itree     : icicle tree
 *      - ctree     : cone tree
 *      - dtree     : donut tree (two level radial)
 *
 *   rational limitations...
 *      - only handle 3 levels of tree at one time (rest are ignored)
 *      - only display the first 12 characters of names (visual consistency)
 *
 *   will not...
 *      - interactively build or edit them
 *
 *   input format...
 *      - pure and plain ascii text file
 *      - only name field or delimited by proper ascii field separator
 *      - blank lines allowed between root branches (none inside these branches)
 *      - first root branch format determines file layout (spaces, numbers, ...)
 *      - typically follows a three-space indent per level model
 *      - comments allowed if '#' in first column
 *
 *
 *   there are many, stable, accepted, existing programs and utilities have
 *   been built by better programmers and are likely superior in speed, size,
 *   capability, and reliability; BUT, i would not have learned nearly as much
 *   using them, so i follow the adage..
 *
 *   TO TRULY LEARN> do not seek to follow in the footsteps of the men of old;
 *   seek what they sought ~ Matsuo Basho
 *
 *   the underlying idea is to use this build process to learn new programming
 *   capabilities and put additional pressure on me to improve my standards,
 *   maintenance, and coding environment.  just using programs and ideas does
 *   not lead to understanding -- so get messy ;)
 *
 */
/*===((END DOC))==============================================================*/





/*===[[ NEXT STEPS ]]=========================================================*/
/*
 *
 *   colors ------------------------------------------------
 *
 *   -- mark 269 colors in scheme for dark or light backgrounds which might
 *      eliminate twenty or so in each case.  maybe i can automate that by
 *      color "closeness" to allow some variation from background
 *
 *   -- read colors from a color file so they can be shared with multiple
 *      programs
 *
 */




/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YHYLEOROI
#define YHYLEOROI loaded

/*---(heatherly libraries)-------------------------*/

/*---(X11/opengl libraries)------------------------*/
#include    <GL/gl.h>                  /* main header for opengl              */
#include    <GL/glx.h>                 /* for xlib/opengl integration         */
#include    <GL/glu.h>
#include    <X11/extensions/shape.h>   /* xwindows shape extension            */

/*---(big standards)------------*/
#include    <stdio.h>        /* C_ANSI : strcpy, strlen, strchr, strcmp, ...  */
#include    <string.h>       /* C_ANSI : printf, snprintf, fgets, fopen, ...  */
#include    <stdlib.h>       /* C_ANSI : exit, system, ...                    */

#include    <fcntl.h>             /* clibc standard file control              */
#include    <termios.h>           /* clibc standard terminal control          */

#include    <math.h>
#include    <sys/time.h>
#include    <unistd.h>
#include    <time.h>         /* C_ANSI : time, localtime                      */

/*===[[ CUSTOM LIBRARIES ]]===================================================*/
#include    <yLOG.h>         /* CUSTOM : heatherly program logging            */
#include    <yURG.h>         /* CUSTOM : heatherly urgent processing          */
#include    <ySTR.h>         /* CUSTOM : heatherly string handling            */
#include    <yCOLOR.h>       /* CUSTOM : heatherly color handling             */
#include    <yX11.h>         /* CUSTOM : heatherly xlib/glx setup             */
#include    <yFONT.h>        /* CUSTOM : heatherly opengl texture-map fonts   */
#include    <yGLTEX.h>       /* CUSTOM : heatherly opengl texture handling    */
#include    <errno.h>
#include    <error.h>


/* rapidly evolving version number to aid with visual change confirmation     */



#define     LEN_STR    100
#define     MAX_STR     50
#define     MAX_NAME   100
#define     MAX_RECD  2000
#define     MAX_DEPTH   20


#define     ROOT_DEF   "((root))"
typedef struct cNODE tNODE;
struct cNODE {
   /*---(basic)--------------------------*/
   int         level;                  /* level in hierarchy (was "l")        */
   char        label       [LEN_LABEL];/* short label                         */
   char        name        [LEN_DESC]; /* full name                           */
   double      size;                   /* relative size                       */
   double      count;                  /* relative count                      */
   char        desc        [LEN_DESC]; /* description                         */
   char        hint        [LEN_TERSE];/* two-letter hint for rapid access    */
   /*---(positioning)--------------------*/
   float       beg;                    /* start degree on radial tree         */
   float       pct;                    /* percent of parent size              */
   float       width;                  /* central angle or width              */
   float       end;                    /* end degree on radial tree           */
   int         color;                  /* color index                         */
   /*---(master list)--------------------*/
   tNODE      *m_prev;                 /* pointer to prev in overall list     */
   tNODE      *m_next;                 /* pointer to next in overall list     */
   /*---(parent)-------------------------*/
   tNODE      *parent;                 /* pointer to owning node              */
   tNODE      *s_prev;                 /* poinder to prev sibling             */
   tNODE      *s_next;                 /* poinder to next sibling             */
   /*---(children)-----------------------*/
   tNODE      *c_head;                 /* pointer to head of siblings         */
   tNODE      *c_tail;                 /* pointer to tail of siblings         */
   int         nchild;                 /* number of child nodes               */
   /*---(done)---------------------------*/
};
extern      tNODE      *g_hnode;
extern      tNODE      *g_tnode;
extern      int         g_nnode;
extern      tNODE      *g_bnode;




extern      int         txf_sm;
extern      int         txf_bg;



#define     MAX_RING    10
#define     MAX_FORMAT  100
typedef     struct      cLAYER       tLAYER;
struct cLAYER {
   /*---(names)-------------*/
   char        name        [10];            /* identification for finding     */
   char        desc        [50];            /* identification for finding     */
   /*---(characteristics)---*/
   float       radius;
   char        tool;
   char        label;
   /*---(done)--------------*/
};
extern      tLAYER      g_layers       [MAX_FORMAT];
extern      int         g_nlayer;


typedef     struct      cFORMAT      tFORMAT;
struct cFORMAT {
   /*---(names)-------------*/
   char        name        [10];            /* identification for finding     */
   char        formal      [20];            /* identification for finding     */
   /*---(descriptions)------*/
   char        format      [30];            /* identification for finding     */
   char        desc        [60];            /* identification for finding     */
   /*---(layers)------------*/
   char        layer_names [MAX_RING][15];
   /*---(working)-----------*/
   int         levels;
   int         layers      [MAX_RING];
   float       cums        [MAX_RING];
   char        labels      [MAX_RING];
   char        hole;                        /* centter is a hole only (y/n)   */
   char        valid;
   /*---(done)--------------*/
};
extern      tFORMAT     g_formats      [MAX_FORMAT];
extern      int         g_nformat;



float  ctrl[3][3];



#define     DEG2RAD  (3.1415927 / 180.0)
#define     RAD2DEG  (180.0 / 3.1415927)
extern      float       my_sin [4000];
extern      float       my_cos [4000];


typedef     struct     cGLOBAL      tGLOBAL;
struct cGLOBAL {
   /*===[[ ------- ]]=======================*/
   /*---(incomming context)--------------*/
   char        r_source    [LEN_HUND];      /* source program for data        */
   char        r_report    [LEN_HUND];      /* source report long name        */
   char        r_oneline   [LEN_HUND];      /* source report descrition       */
   char        r_option    [LEN_HUND];      /* source program option used     */
   char        r_timestamp [LEN_HUND];      /* source date of generation      */
   char        r_format    [LEN_HUND];      /* hyleoroi format requested      */
   /*---(window)-------------------------*/
   int         tex_h;                  /* texture height                      */
   int         tex_w;                  /* texture width                       */
   char        type;                   /* mime, dirtree, etc                  */
   char        format;                 /* radial, block, etc                  */
   double      full_size;              /* full size of graph (arc or length)  */
   char        fentry      [100];      /* format title                        */
   char        fdesc       [100];      /* format title                        */
   char        tdesc       [100];      /* type title                          */
   char        label       [ 10];      /* node title flags                    */
   char        ghost;                  /* show child wedges (y/n)             */
   char        radial;                 /* radial format                       */
   int         max_depth;              /* deepest part of tree in use         */
   /*===[[ windows ]]=======================*/
   /*---(window sizes)----*/
   char        w_title     [LEN_STR];       /* window title                   */
   int         w_wide;                      /* window width                   */
   int         w_tall;                      /* window heigth                  */
   /*---(main window)-----*/
   int         m_wide;                      /* width  of main window          */
   int         m_left;                      /* left   of main window        */
   int         m_tall;                      /* height of main window        */
   int         m_bott;                      /* bottom of main window        */
   /*---(tag window)------*/
   int         t_wide;                      /* width  of tag panel            */
   int         t_left;                      /* left   of tag panel            */
   int         t_tall;                      /* height of tag panel            */
   int         t_bott;                      /* bottom of tag panel            */
   int         t_curr;                      /* current topmost entry          */
   int         t_count;                     /* count of entries at level      */
   int         t_shown;                     /* count of shown entries         */
   /*---(command window)--*/
   int         c_wide;                      /* width  of command line         */
   int         c_left;                      /* left   of command line         */
   int         c_tall;                      /* height of command line         */
   int         c_bott;                      /* bottom of command line         */
   /*---(alt/detail)------*/
   int         a_wide;                      /* width  of alt/detail window    */
   int         a_left;                      /* left   of alt/detail window    */
   int         a_tall;                      /* height of alt/detail window    */
   int         a_bott;                      /* bottom of alt/detail window    */
   /*===[[ ------- ]]=======================*/
   /*---(reporting)----------------------*/
   char        node_dump;              /* dump full node table                */
   /*---(colors)-------------------------*/
   char        hole;
   int         color;                  /* next color to use in node           */
   uint        color_start;            /* initial color seed                  */
   uint        color_seed;             /* seed for random                     */
   float       cutoff;
   /*---(sizing)-------------------------*/
   int         ring;
   int         point;
   int         ring_thick  [MAX_RING];
   char        ring_label  [MAX_RING];
   /*---(action)-------------------------*/
   float       single;
   float       angle;
   float       inc;                    /* action update increment             */
   char        action;
   float       xdist;
   float       ydist;
   float       zdist;
   /*---(other)--------------------------*/
   char        hint_minor;
   char        hint_major;
   char        print;
   int         space;
   float       explode;
   tNODE      *focus;
   char        scheme;
   char        chaos;
   char        noempty;
   tNODE      *empty;
   char        hints;
   /*---(done)---------------------------*/
};
extern      tGLOBAL    my;
#define     PLAY       -0.2
#define     STOP        0.0
#define     INC_SPEED   0.1
#define     MAX_SPEED   0.5
#define     OPT_PRINT      if (my.print == 'y') 
#define     NODE_DUMP   if (my.node_dump == 'y')



/*> /+===[[ DEBUGGING SETUP ]]====================================================+/   <* 
 *> /+ this is my latest standard format, vars, and urgents                       +/   <* 
 *> /+ v3.0b : added signal handling                                (2014-feb-01) +/   <* 
 *> struct cDEBUG                                                                      <* 
 *> {                                                                                  <* 
 *>    /+---(handle)-------------------------+/                                        <* 
 *>    int         logger;                 /+ log file so that we don't close it  +/   <* 
 *>    /+---(overall)------------------------+/  /+ abcdefghi_klm_opq_stu__x__    +/   <* 
 *>    /+ f = full urgents turns on all standard urgents                          +/   <* 
 *>    /+ k = kitchen sink and turns everything, i mean everything on             +/   <* 
 *>    /+ q = quiet turns all urgents off including the log itself                +/   <* 
 *>    char        tops;                   /+ t) broad structure and context      +/   <* 
 *>    char        summ;                   /+ s) statistics and analytical output +/   <* 
 *>    /+---(startup/shutdown)---------------+/                                        <* 
 *>    char        args;                   /+ a) command line args and urgents    +/   <* 
 *>    char        conf;                   /+ c) configuration handling           +/   <* 
 *>    char        prog;                   /+ p) program setup and teardown       +/   <* 
 *>    /+---(file processing)----------------+/                                        <* 
 *>    char        inpt;                   /+ i) text/data file input             +/   <* 
 *>    char        inptM;                  /+ -) text/data file input   (mas/more)+/   <* 
 *>    char        outp;                   /+ o) text/data file output            +/   <* 
 *>    char        outpM;                  /+ -) text/data file output  (mas/more)+/   <* 
 *>    /+---(event handling)-----------------+/                                        <* 
 *>    char        loop;                   /+ l) main program event loop          +/   <* 
 *>    char        user;                   /+ u) user input and handling          +/   <* 
 *>    char        apis;                   /+ z) interprocess communication       +/   <* 
 *>    char        sign;                   /+ x) os signal handling               +/   <* 
 *>    char        scrp;                   /+ b) scripts and batch operations     +/   <* 
 *>    char        hist;                   /+ h) history, undo, redo              +/   <* 
 *>    /+---(program)------------------------+/                                        <* 
 *>    char        graf;                   /+ g) grahpics, drawing, and display   +/   <* 
 *>    char        data;                   /+ d) primary data structure handling  +/   <* 
 *>    char        envi;                   /+ e) environment processing           +/   <* 
 *>    char        enviM;                  /+ -) environment processing (mas/more)+/   <* 
 *>    char        mems;                   /+ m) memory usage                     +/   <* 
 *>    /+---(specific)-----------------------+/                                        <* 
 *>    char        color;                  /+ -) color choices                    +/   <* 
 *>    /+---(done)---------------------------+/                                        <* 
 *> };                                                                                 <* 
 *> typedef     struct      cDEBUG       tDEBUG;                                       <* 
 *> extern      tDEBUG      debug;                                                     <*/

/*> #define     DEBUG_TOPS          if (debug.tops      == 'y')                       <* 
 *> #define     DEBUG_SUMM          if (debug.summ      == 'y')                       <* 
 *> #define     DEBUG_ARGS          if (debug.args      == 'y')                       <* 
 *> #define     DEBUG_CONF          if (debug.conf      == 'y')                       <* 
 *> #define     DEBUG_PROG          if (debug.prog      == 'y')                       <* 
 *> #define     DEBUG_INPT          if (debug.inpt      == 'y')                       <* 
 *> #define     DEBUG_INPTM         if (debug.inptM     == 'y')                       <* 
 *> #define     DEBUG_OUTP          if (debug.outp      == 'y')                       <* 
 *> #define     DEBUG_OUTPM         if (debug.outpM     == 'y')                       <* 
 *> #define     DEBUG_LOOP          if (debug.loop      == 'y')                       <* 
 *> #define     DEBUG_USER          if (debug.user      == 'y')                       <* 
 *> #define     DEBUG_APIS          if (debug.apis      == 'y')                       <* 
 *> #define     DEBUG_SIGN          if (debug.sign      == 'y')                       <* 
 *> #define     DEBUG_SCRP          if (debug.scrp      == 'y')                       <* 
 *> #define     DEBUG_HIST          if (debug.hist      == 'y')                       <* 
 *> #define     DEBUG_GRAF          if (debug.graf      == 'y')                       <* 
 *> #define     DEBUG_DATA          if (debug.data      == 'y')                       <* 
 *> #define     DEBUG_ENVI          if (debug.envi      == 'y')                       <* 
 *> #define     DEBUG_ENVIM         if (debug.enviM     == 'y')                       <* 
 *> #define     DEBUG_MEMS          if (debug.mems      == 'y')                       <* 
 *> #define     DEBUG_COLOR         if (debug.color     == 'y')                       <*/





/*===[[ HYLEORI_MAIN.C ]]=====================================================*/
int         main               (int argc, char *argv[]);

/*===[[ HYLEORI_PROG.C ]]=====================================================*/
/*---(utility)--------------*/
long        TIME_stamp        (void);
char       *ySTR_trim          (char *a_source, char a_mode);
#define       ySTR_NONE      'n'
#define       ySTR_HEAD      'h'
#define       ySTR_TAIL      't'
#define       ySTR_BOTH      'b'
#define       ySTR_SINGLE    's'
#define       ySTR_EVERY     'e'
#define       ySTR_MAX       'm'
/*---(program)--------------*/
char        PROG_init               (void);
char        PROG_urgsmass           (char a_set, char a_extra);
char        PROG_urgs               (int argc, char *argv[]);
char        PROG_args               (int argc, char *argv[]);
char        PROG_begin              (void);
char        PROG_visual_beg         (void);
char        PROG_visual_end         (void);
char        PROG_end                (void);
/*---(testing)--------------*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        PROG__unit_quiet        (void);
char        PROG__unit_loud         (void);
char        PROG__unit_end          (void);

extern      char          unit_answer [LEN_FULL];


char        DRAW_window_sizes  (void);

char        DRAW_globals       (void);
char        DRAW_init          (void);
char        DRAW_main          (void);



char        PROG_event         (void);
char        DRAW__radial_empty (tNODE *a_node, char a_type);
char        DRAW__radial_full  (tNODE *a_curr, char a_hole);
char        DRAW_node          (int a_level, tNODE *a_curr, char a_style);
char        DRAW_level         (int a_level, tNODE *a_first, char a_recurse);
char        DRAW_resize        (uint a_w, uint a_h);
char        DRAW__radial_vals  (tNODE *a_node);
/*---(texture)-----------------*/
char        TEX_new            (uint *a_tex, uint *a_fbo, uint *a_depth, int a_wide, int a_tall);
char        TEX_free           (uint *a_tex, uint *a_fbo, uint *a_depth);

char        GRAPH_init         (void);
char        GRAPH_draw         (void);
char        GRAPH_show         (void);


char        TAGS_init          (void);
char        TAGS_wrap          (void);
char        TAGS_draw          (void);
char        TAGS_show          (void);



/*===[[ RTREE_GRAF.C ]]=======================================================*/
char        FONT_load          (void);
char        FONT_unload        (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        STDIN_init              (void);
char        STDIN_check             (void);
char        STDIN__getline          (void);
char        STDIN__parse            (void);
char        STDIN__verbs            (void);
char*       STDIN__unit             (char *a_question, int n);

char        FILE_main               (void);


/*---(program)--------------*/
char        NODE_init               (void);
char        NODE__purge             (void);
/*---(support)--------------*/
char        NODE__wipe              (tNODE *a_curr);
/*---(hooking)--------------*/
char        NODE__master_hook       (tNODE *a_new);
char        NODE__master_unhook     (tNODE *a_old);
char        NODE__parent_hook       (tNODE *a_new, tNODE *a_parent);
char        NODE__parent_unhook     (tNODE *a_old);
/*---(malloc)---------------*/
char        NODE__new               (tNODE **a_new);
char        NODE__free              (tNODE **a_old);
/*---(exist)----------------*/
char        NODE_create             (tNODE **a_new, tNODE *a_parent);
char        NODE_root               (void);
char        NODE_destroy            (tNODE **a_old);

char        NODE_read          (int a_level, tNODE *a_owner);
char        NODE_dump          (int a_level, tNODE *a_parent, char a_recurse );
char        NODE_reroot        (void);
tNODE*      NODE_find_name     (char *a_label);
/*---(unit_test)------------*/
char*       NODE__unit              (char *a_question, tNODE *a_focus, int n);


char        PREP_purge              (void);
char        PREP_resize             (int a_level, tNODE *a_parent);
char        PREP_process            (int a_level, tNODE *a_first);
char        PREP_level              (int a_level, tNODE *a_parent);
char        PREP_levelall           (void);

/*===[[ HYLEOROI_COLOR.C ]]===================================================*/
/*---(constants)--------------*/
#define     COLOR_BLACK        'b'
#define     COLOR_DARK         'd'
#define     COLOR_LIGHT        'l'
#define     COLOR_WHITE        'w'
/*---(program)----------------*/
char        COLOR_wrap         (void);
int         COLOR_count        (void);
/*---(filtering)--------------*/
/*---(setting)--------------*/
/*---(cursor)---------------*/



char        FORMAT_init        (void);
int         FORMAT_find_format (char *a_name);
int         FORMAT_find_layer  (char *a_name);
float       FORMAT_get_radius  (int   a_layer);
char        FORMAT_get_label   (int   a_layer);
char        FORMAT_dump_formats   (void);
char        FORMAT_set         (char *a_name);


#endif
