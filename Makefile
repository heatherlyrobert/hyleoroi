#================================[[ beg-code ]]================================#



#===(user defined)=========================================#
# basename of executable, header, and all code files
NAME_BASE  = hyleoroi
# additional standard and outside libraries
LIB_STD    = -lX11 -lGL -lGLU -lm -lXext
# all heatherly libraries used, debug versions whenever available
LIB_MINE   = -lyX11 -lySTR_debug -lyFONT_debug -lyGLTEX_debug -lyCOLOR_debug
# directory for production code, no trailing slash
INST_DIR   = /usr/local/bin



#===(post-processing)======================================#
# create a rule for...
#    install_prep       :
#    remove_prep        :


#===(master template)======================================#
include /usr/local/sbin/make_program



#===(post-processing)======================================#
# create a rule for...
#    install_post       :
#    remove_post        :



#================================[[ end-code ]]================================#
