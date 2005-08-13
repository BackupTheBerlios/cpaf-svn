#!/bin/sh
g++ -DCPAF_GTK2 -D_DEBUG -I ../../include -L ../../lib -lcpaf_gui_gtk2d -Wl,-rpath,../../lib -ggdb main.cpp -o proof
