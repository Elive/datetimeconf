#include <gtk/gtk.h>


void
on_helpbutton1_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelbutton1_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_okbutton1_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_MainWindow_close                    (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_drawingarea1_motion_notify_event    (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data);

gboolean
on_drawingarea1_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_drawingarea1_leave_notify_event     (GtkWidget       *widget,
                                        GdkEventCrossing *event,
                                        gpointer         user_data);

gboolean
on_drawingarea1_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_calendar1_day_selected              (GtkCalendar     *calendar,
                                        gpointer         user_data);

void
on_calendar1_month_changed             (GtkCalendar     *calendar,
                                        gpointer         user_data);

void
on_spinbutton1_value_changed           (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_combo_entry1_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_spinbutton1_changed                 (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_spinbutton2_changed                 (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_spinbutton3_changed                 (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

gboolean
on_treeview1_select_cursor_row         (GtkTreeView     *treeview,
                                        gboolean         start_editing,
                                        gpointer         user_data);

void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);
