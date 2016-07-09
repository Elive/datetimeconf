#ifndef MAIN_DT_H
#define MAIN_DT_H

#include <gtk/gtk.h>
#include <time.h>
#include "libdatetime.h"

#define MAP_HEIGHT 240
#define MAP_WIDTH  480
/*
#define TIMEZONE_MAP "../pixmaps/map480.png"
#define TIMEZONE_MAP_2 "/usr/share/datetimeconf/pixmaps/map480.png"

#define CROSS_GREEN "../pixmaps/cross-green.png"
#define CROSS_GREEN_2 "/usr/share/datetimeconf/pixmaps/cross-green.png"

#define CROSS_RED "../pixmaps/cross-red.png"
#define CROSS_RED_2 "/usr/share/datetimeconf/pixmaps/cross-red.png"
*/
#define DEBUG

#ifdef DEBUG
#define debug printf
#else
#define debug (void)
#endif

gchar *timezone_map_loc;
gchar *cross_green_loc;
gchar *cross_red_loc;

enum {
	CODE_COL,
	TIMEZONE_COL,
	COMMENT_COL,
	N_COLUMNS
};

GtkWidget *MainWindow;
int quit_conf();
void do_ntp_server();
struct tm get_date_time();
void set_date_time(struct tm dt);
void setup_timezone_list();
gboolean setup_timezone_map();
gboolean draw_cross(int x, int y);
void set_readin_tz();	
void set_ntp_server_list();
void set_current_tz(tz_struct *tz);
gboolean set_tz_from_string(gchar *string);
void setup_timezone_list_cb();
#endif
