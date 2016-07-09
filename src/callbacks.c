#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <time.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "main.h"
#include "libdatetime.h"

gboolean realised;
gboolean time_changed;
gboolean ntp_changed;
gboolean utc_changed;
tz_struct *nearest_timezone;
tz_struct *selected_timezone;

void
on_helpbutton1_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_cancelbutton1_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	quit_conf();
}


void
on_okbutton1_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *ntpcheck = lookup_widget(MainWindow,"checkbutton1");
	GtkWidget *utccheck = lookup_widget(MainWindow,"checkbutton2");
	GtkWidget *combo = lookup_widget(MainWindow,"combo1");

	struct tm dt = get_date_time();

	if (time_changed == TRUE) {
		debug("Time has changed, setting and syncing hardware clock\n");
		write_date_time(&dt);
		sync_hardware_clock(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(utccheck)));

	}
	if (utc_changed == TRUE) {
		debug("UTC has been changed, writing to bootscript defaults\n");		sync_hardware_clock(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(utccheck)));
		set_system_utc(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(utccheck)));
	}
	if (ntp_changed == TRUE && check_ntp_installed() == TRUE) {
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ntpcheck))) {
			set_ntp_server(gtk_entry_get_text(GTK_ENTRY((GTK_COMBO(combo))->entry)));
			restart_ntp_client();
		}
		else {
			disable_ntp_servers();
		}
	}

	if (selected_timezone != NULL) {
		write_timezone(selected_timezone);
	}
	quit_conf();
}



gboolean
on_MainWindow_close                    (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	quit_conf();

  return FALSE;
}

gboolean
on_drawingarea1_motion_notify_event    (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data)
{
	gint x_mouse = event->x;
	gint y_mouse = event->y;
	gint lat = canvas2map_lat(y_mouse,MAP_HEIGHT);
	gint lon = canvas2map_lon(x_mouse,MAP_WIDTH);
	nearest_timezone = find_nearest_entry(lat,lon);
//	debug("nearest timezone lat: %d lon: %d\n",lat,lon);
// 	debug("current coords x: %d y: %d\n",x_mouse,y_mouse);
	return FALSE;
}


gboolean
on_drawingarea1_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	if (event->button == 1) {
		set_current_tz(nearest_timezone);
	}
	return FALSE;
}


gboolean
on_drawingarea1_leave_notify_event     (GtkWidget       *widget,
                                        GdkEventCrossing *event,
                                        gpointer         user_data)
{

  return FALSE;
}


gboolean
on_drawingarea1_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	gint y_cross; 
	gint x_cross; 
	if (!setup_timezone_map()) {
		debug("Map failed!\n");
	}
	if (!draw_city_dots_timezone_map()) {
		debug("Dots failed!\n");
	}
	if (nearest_timezone != NULL) {
		y_cross = map2canvas_lat(nearest_timezone->lat,MAP_HEIGHT);
		x_cross = map2canvas_lon(nearest_timezone->lon,MAP_WIDTH);
//		debug("drawing cross with lat: %d lon: %d\n",nearest_timezone->lat,nearest_timezone->lon);
//		debug("on coords x: %d, y: %d\n",x_cross,y_cross);
		if (!draw_cross(x_cross,y_cross)) {
			debug("Cross failed!\n");
		}
	}
	if (selected_timezone != NULL) {
		y_cross = map2canvas_lat(selected_timezone->lat,MAP_HEIGHT);
		x_cross = map2canvas_lon(selected_timezone->lon,MAP_WIDTH);
		if (!draw_red_cross(x_cross,y_cross)) {
			debug("Red cross failed!\n");
		}
	}
	return FALSE;
}

void set_time_changed() {
	if (realised == TRUE) {
		debug("Time has been changed\n");
		time_changed = TRUE;
	}
}
void set_ntp_changed() {
	if (realised == TRUE) {
		debug("NTP has been changed\n");
		ntp_changed = TRUE;
	}
}

void set_utc_changed() {
	if (realised == TRUE) {
		debug("UTC has been changed\n");
		utc_changed = TRUE;
	}
}

void
on_calendar1_day_selected              (GtkCalendar     *calendar,
                                        gpointer         user_data)
{
	set_time_changed();
}


void
on_calendar1_month_changed             (GtkCalendar     *calendar,
                                        gpointer         user_data)
{
	set_time_changed();
}


void
on_spinbutton1_value_changed           (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	set_time_changed();
}


void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	set_ntp_changed();
}


void
on_combo_entry1_changed                (GtkEditable     *editable,
                                        gpointer         user_data)
{
	set_ntp_changed();
}


void
on_spinbutton1_changed                 (GtkEditable     *editable,
                                        gpointer         user_data)
{
	set_time_changed();
}


void
on_spinbutton2_changed                 (GtkEditable     *editable,
                                        gpointer         user_data)
{
	set_time_changed();
}


void
on_spinbutton3_changed                 (GtkEditable     *editable,
                                        gpointer         user_data)
{
	set_time_changed();
}


void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	set_utc_changed();
}


gboolean
on_treeview1_select_cursor_row         (GtkTreeView     *treeview,
                                        gboolean         start_editing,
                                        gpointer         user_data)
{
  return FALSE;
}


void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	debug("Selected row!\n");

}

