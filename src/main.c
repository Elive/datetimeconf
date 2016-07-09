/* Copyright (C) 2003 Alex de Landgraaf <alextreme@xs4all.nl>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <time.h>
#include <stdio.h>

#include "interface.h"
#include "support.h"
#include "libdatetime.h"
#include "main.h"

extern gboolean realised;
extern gboolean ntp_changed;
extern gboolean time_changed;
extern gboolean utc_changed;
extern tz_struct *nearest_timezone;
extern tz_struct *selected_timezone;

GtkTreeSelection *selector;

void tree_selection_changed_cb (GtkTreeSelection *selection, gpointer data) {
	GtkTreeIter iter;
	GtkTreeModel *model;
	gchar *tz;
	
	if (gtk_tree_selection_get_selected(selection,&model,&iter)) {
		gtk_tree_model_get(model,&iter,	TIMEZONE_COL, &tz, -1);
		
		selected_timezone = find_timezone_entry(tz);
		//g_free(tz);
	}
}

void set_time(struct tm dt) {
	GtkWidget *curr_time = lookup_widget(MainWindow,"label7");
	gchar string[9];
	sprintf(string,"%02d:%02d:%02d",dt.tm_hour,dt.tm_min,dt.tm_sec);
	gtk_label_set_text(GTK_LABEL(curr_time),string);
}

gboolean sec_timeout(gpointer data) {
	struct tm *dt = get_current_date_time();
	set_time(*dt);
	return TRUE;
}

void init_dtconf() {
	GtkWidget *drawarea = lookup_widget(MainWindow,"drawingarea1");
	GtkWidget *ntplabel = lookup_widget(MainWindow,"label11");
	GtkWidget *ntpcheckbutton = lookup_widget(MainWindow,"checkbutton1");
	GtkWidget *ntpcombo = lookup_widget(MainWindow,"combo1");
	gtk_widget_set_events(drawarea, GDK_BUTTON_PRESS_MASK |
			      GDK_POINTER_MOTION_MASK);
	nearest_timezone = NULL;
	selected_timezone = NULL;
	time_changed = FALSE;
	ntp_changed = FALSE;
	utc_changed = FALSE;
	timezone_map_loc = NULL;
	cross_green_loc = NULL;
	cross_red_loc = NULL;

	gint length = strlen(PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps/map480.png");
	timezone_map_loc = (gchar *)malloc(length + 1);
	strcpy(timezone_map_loc,PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps/map480.png");
	length = strlen(PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps/cross-green.png");
	cross_green_loc = (gchar *)malloc(length +1);
	strcpy(cross_green_loc,PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps/cross-green.png");

	length = strlen(PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps/cross-red.png");
	cross_red_loc = (gchar *)malloc(length +1);
	strcpy(cross_red_loc,PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps/cross-red.png");
	if (timezone_map_loc == NULL ||
	    cross_green_loc == NULL ||
	    cross_red_loc == NULL) {
		debug("Can't find pixmaps in %s\n",PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");
		exit(1);
	}
	if (check_ntp_installed() == FALSE) {
		gtk_widget_set_sensitive(ntpcheckbutton,FALSE);
		gtk_widget_set_sensitive(ntpcombo,FALSE);
		gtk_label_set_text(GTK_LABEL(ntplabel),"Your computer doesn't have an Network Time Protocol client installed. Please install the ntpdate package");
	}

	debug("Location map: %s\nLocation green cross: %s\nLocation red cross: %s\n",timezone_map_loc,cross_green_loc,cross_red_loc);

}

void setup_dtconf() {
	GtkWidget *utccheckbutton = lookup_widget(MainWindow,"checkbutton2");

	if (!read_zone_info()) {
		debug("Error: Can't read zone info, exitting\n");
		exit(1);
	}
	struct tm *dt = get_current_date_time();
	set_date_time(*dt);	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(utccheckbutton),check_system_utc());
	debug("Set date/time\n");
	set_ntp_server_list();
	do_ntp_server();
	setup_timezone_list();
	read_current_timezone();
	if (read_tz != NULL) {
		set_readin_tz();
	}
	setup_timezone_list_cb();

	debug("Set up ntp\n");
	realised = TRUE;
	g_timeout_add(1000,sec_timeout,NULL);
}

gchar *build_cmdline(int argc, char **argv) {
        int i;
        if (argv == NULL || argc < 0) {
                return NULL;
        }
        gchar *cmdline = g_strdup(argv[0]);
        for (i = 1; i < argc; i++) {
                gchar *tmp = g_strdup_printf("%s %s",cmdline,argv[i]);
                g_free(cmdline);
                cmdline = tmp;
        }
        return cmdline;
}

int
main (int argc, char *argv[])
{
	if (geteuid() != 0) {
                //gksu_init(argc,argv);
                //gchar *cmdline = build_cmdline(argc,argv);
                //gksu_run(cmdline);
                //g_free(cmdline);
		fprintf(stderr,"Sorry, you need to be root to run this program\n");
                return 1;
	}
#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif
	
	gtk_set_locale ();
	gtk_init (&argc, &argv);
	
	add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");

	MainWindow = create_MainWindow ();
	init_dtconf();
	gtk_widget_show (MainWindow);
	setup_dtconf();
	
	gtk_main ();
	return 0;
}

int quit_conf() {
	free_zone_info();
	free(timezone_map_loc);
	free(cross_green_loc);
	free(cross_red_loc);
	exit(0);
}

void do_ntp_server() {
	GtkWidget *ntpcombo = lookup_widget(MainWindow,"combo1");
	GtkWidget *ntpcheckbutton = lookup_widget(MainWindow,"checkbutton1");
	
	gchar *ntpstr = get_ntp_server();
	if (ntpstr == NULL) {
		debug("No NTP server\n");
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ntpcheckbutton),FALSE);
	}
	else {
		GList *items = NULL;
		items = g_list_append(items,ntpstr);
		gtk_combo_set_popdown_strings(GTK_COMBO(ntpcombo),items);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ntpcheckbutton),TRUE);
	}
				
}

void set_ntp_server_list() {
	GtkWidget *combo = lookup_widget(MainWindow,"combo1");
	GList *list = NULL;
	list = g_list_append(list,"time.nist.gov");
	gtk_combo_set_popdown_strings(GTK_COMBO(combo),list);
}
struct tm get_date_time() {
	struct tm dt;
	
	GtkWidget *calendar = lookup_widget(MainWindow,"calendar1");
	GtkWidget *hour = lookup_widget(MainWindow,"spinbutton1");
	GtkWidget *minute = lookup_widget(MainWindow,"spinbutton2");
	GtkWidget *second = lookup_widget(MainWindow,"spinbutton3");
	
	gtk_calendar_get_date(GTK_CALENDAR(calendar),
			      &dt.tm_year, &dt.tm_mon, &dt.tm_mday);
	dt.tm_year - 1900;
	dt.tm_hour = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(hour));
	dt.tm_min  = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(minute));
	dt.tm_sec  = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(second));

	return dt;
}

void set_date_time(struct tm dt) {
	GtkWidget *calendar = lookup_widget(MainWindow,"calendar1");
	GtkWidget *hour = lookup_widget(MainWindow,"spinbutton1");
	GtkWidget *minute = lookup_widget(MainWindow,"spinbutton2");
	GtkWidget *second = lookup_widget(MainWindow,"spinbutton3");
	
	set_time(dt);
	
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(hour),(gdouble) dt.tm_hour);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(minute),(gdouble) dt.tm_min);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(second),(gdouble) dt.tm_sec);
	
	gtk_calendar_select_month(GTK_CALENDAR(calendar),
				  dt.tm_mon,dt.tm_year + 1900);
	gtk_calendar_select_day(GTK_CALENDAR(calendar),
				dt.tm_mday);
}


void setup_timezone_list_cb() {
	GtkWidget *treeview = lookup_widget(MainWindow,"treeview1");

	selector = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	gtk_tree_selection_set_mode(selector, GTK_SELECTION_SINGLE);
	g_signal_connect(G_OBJECT(selector),"changed",
			 G_CALLBACK(tree_selection_changed_cb),
			 NULL);
}

void setup_timezone_list() {
	GtkWidget *treeview = lookup_widget(MainWindow,"treeview1");
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeStore *store = gtk_tree_store_new(N_COLUMNS,
						 G_TYPE_STRING, // code
						 G_TYPE_STRING, // timezone
						 G_TYPE_STRING);// comment
	int i;
	


	for (i = 0; i < timezones_count; i++) {
		GtkTreeIter iter;
		gtk_tree_store_append(store,&iter,NULL);
		gtk_tree_store_set(store,&iter,
				   CODE_COL, timezones[i].code,
				   TIMEZONE_COL, timezones[i].tz,
				   COMMENT_COL, timezones[i].comment,
				   -1);
		
	}
	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(store));

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes ("Code",
							   renderer,
							   "text", CODE_COL,
							   NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes ("Timezone",
							   renderer,
							   "text", TIMEZONE_COL,
							   NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),column);
	
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes ("Comment",
							   renderer,
							   "text", COMMENT_COL,
							   NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),column);

}

gboolean setup_timezone_map() {
	GError *err = NULL;
	GtkWidget *drawarea = lookup_widget(MainWindow,"drawingarea1");
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(timezone_map_loc,&err);

	if (pixbuf == NULL) {
		return FALSE;
	}
	gtk_widget_show_all(drawarea);
	gdk_draw_pixbuf(drawarea->window,
			NULL,
			pixbuf,
			0,0,
			0,0,
			-1,-1,
			GDK_RGB_DITHER_NORMAL,
			0,0);
	g_object_unref(pixbuf);
	return TRUE;
}

void change_timezone_label() {
	// change the label to green-crossed/nearest_timezone
	GtkWidget *label = lookup_widget(MainWindow,"label14");
	gtk_label_set_text(GTK_LABEL(label),nearest_timezone->tz);
}

gboolean draw_cross(int x, int y) {
	GtkWidget *drawarea = lookup_widget(MainWindow,"drawingarea1");
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(cross_green_loc,NULL);
	if (pixbuf == NULL) {
		return FALSE;
	}
	gdk_draw_pixbuf(drawarea->window,
			NULL,
			pixbuf,
			0,0,
			x-6,y-6,
			-1,-1,
			GDK_RGB_DITHER_NORMAL,
			0,0);
	change_timezone_label();
	g_object_unref(pixbuf);
	return TRUE;
}

gboolean draw_red_cross(int x, int y) {
	GtkWidget *drawarea = lookup_widget(MainWindow,"drawingarea1");
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(cross_red_loc,NULL);
	if (pixbuf == NULL) {
		return FALSE;
	}
	gdk_draw_pixbuf(drawarea->window,
			NULL,
			pixbuf,
			0,0,
			x-6,y-6,
			-1,-1,
			GDK_RGB_DITHER_NORMAL,
			0,0);
	change_timezone_label();
	g_object_unref(pixbuf);
	return TRUE;
}

void set_readin_tz() {
	set_tz_from_string(read_tz);
}
	

void set_current_tz(tz_struct *tz) {
	selected_timezone = tz;
	set_tz_from_string(tz->tz);
}

gboolean set_tz_from_string(gchar *string) {
	gint i;	
	GtkTreeIter iter;
	gboolean valid;
	GtkTreePath *path = NULL;
	GtkWidget *treeview = lookup_widget(MainWindow,"treeview1");
	GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
	
	if (string == NULL) {
		return FALSE;
	}
	valid = gtk_tree_model_get_iter_first(model,&iter);
	for (i = 0; i < timezones_count && valid == TRUE; i++) {
		if (strcmp(timezones[i].tz,string) == 0) {
			path = gtk_tree_model_get_path(model,&iter);
			gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(treeview),
						     path,
						     NULL,
						     TRUE,
						     0.5,0.0);
			gtk_tree_selection_select_iter(selection,&iter);
			break;
		}
		valid = gtk_tree_model_iter_next(model,&iter);
	}
	return TRUE;
 }


gboolean draw_city_dots_timezone_map() {
	int i;
	GtkWidget *drawarea = lookup_widget(MainWindow,"drawingarea1");
	GdkGC *gc = gdk_gc_new(drawarea->window);
	GdkColor color;
	gdk_color_parse("yellow",&color);
	gdk_colormap_alloc_color(gdk_colormap_get_system(),&color,TRUE,TRUE);
	gtk_widget_modify_fg(drawarea,GTK_STATE_NORMAL,&color);
	
	gdk_gc_set_foreground(gc,&color);
	for (i = 0; i < timezones_count; i++) {
//		debug("Drawing point %d %d of %s\n",
//		      map2canvas_lon(timezones[i].lon,MAP_WIDTH),
//		      map2canvas_lat(timezones[i].lat,MAP_HEIGHT),
//		      timezones[i].tz);
		gdk_draw_point(drawarea->window,gc,
			       map2canvas_lon(timezones[i].lon,MAP_WIDTH),
			       map2canvas_lat(timezones[i].lat,MAP_HEIGHT));
	}
	g_object_unref(gc);
	return TRUE;
}
					      
			       
