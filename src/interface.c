/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget*
create_MainWindow (void)
{
  GtkWidget *MainWindow;
  GtkWidget *dialog_vbox1;
  GtkWidget *notebook1;
  GtkWidget *vbox1;
  GtkWidget *hbox1;
  GtkWidget *frame1;
  GtkWidget *calendar1;
  GtkWidget *label3;
  GtkWidget *frame2;
  GtkWidget *table1;
  GtkWidget *label6;
  GtkWidget *label7;
  GtkWidget *label8;
  GtkWidget *label9;
  GtkWidget *label10;
  GtkObject *spinbutton1_adj;
  GtkWidget *spinbutton1;
  GtkObject *spinbutton2_adj;
  GtkWidget *spinbutton2;
  GtkObject *spinbutton3_adj;
  GtkWidget *spinbutton3;
  GtkWidget *label4;
  GtkWidget *frame3;
  GtkWidget *vbox2;
  GtkWidget *label11;
  GtkWidget *checkbutton1;
  GtkWidget *hbox2;
  GtkWidget *label12;
  GtkWidget *combo1;
  GtkWidget *combo_entry1;
  GtkWidget *label5;
  GtkWidget *label1;
  GtkWidget *vbox3;
  GtkWidget *label13;
  GtkWidget *drawingarea1;
  GtkWidget *label14;
  GtkWidget *hseparator1;
  GtkWidget *scrolledwindow1;
  GtkWidget *treeview1;
  GtkWidget *checkbutton2;
  GtkWidget *label2;
  GtkWidget *dialog_action_area1;
  GtkWidget *helpbutton1;
  GtkWidget *cancelbutton1;
  GtkWidget *okbutton1;

  MainWindow = gtk_dialog_new ();
  gtk_widget_set_size_request (MainWindow, 500, 650);
  gtk_window_set_title (GTK_WINDOW (MainWindow), _("Date / Time Properties"));
  gtk_window_set_position (GTK_WINDOW (MainWindow), GTK_WIN_POS_CENTER);

  dialog_vbox1 = GTK_DIALOG (MainWindow)->vbox;
  gtk_widget_show (dialog_vbox1);

  notebook1 = gtk_notebook_new ();
  gtk_widget_show (notebook1);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), notebook1, TRUE, TRUE, 0);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (notebook1), vbox1);

  hbox1 = gtk_hbox_new (TRUE, 0);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, TRUE, TRUE, 0);

  frame1 = gtk_frame_new (NULL);
  gtk_widget_show (frame1);
  gtk_box_pack_start (GTK_BOX (hbox1), frame1, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame1), 8);

  calendar1 = gtk_calendar_new ();
  gtk_widget_show (calendar1);
  gtk_container_add (GTK_CONTAINER (frame1), calendar1);
  gtk_calendar_display_options (GTK_CALENDAR (calendar1),
                                GTK_CALENDAR_SHOW_HEADING
                                | GTK_CALENDAR_SHOW_DAY_NAMES);

  label3 = gtk_label_new (_("Date"));
  gtk_widget_show (label3);
  gtk_frame_set_label_widget (GTK_FRAME (frame1), label3);
  gtk_label_set_justify (GTK_LABEL (label3), GTK_JUSTIFY_LEFT);

  frame2 = gtk_frame_new (NULL);
  gtk_widget_show (frame2);
  gtk_box_pack_start (GTK_BOX (hbox1), frame2, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame2), 8);

  table1 = gtk_table_new (4, 2, TRUE);
  gtk_widget_show (table1);
  gtk_container_add (GTK_CONTAINER (frame2), table1);

  label6 = gtk_label_new (_("Current Time:"));
  gtk_widget_show (label6);
  gtk_table_attach (GTK_TABLE (table1), label6, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_justify (GTK_LABEL (label6), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (label6), 0, 0.5);

  label7 = gtk_label_new (_("00:00:00"));
  gtk_widget_show (label7);
  gtk_table_attach (GTK_TABLE (table1), label7, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_justify (GTK_LABEL (label7), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (label7), 0, 0.5);

  label8 = gtk_label_new (_("Hour:"));
  gtk_widget_show (label8);
  gtk_table_attach (GTK_TABLE (table1), label8, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_justify (GTK_LABEL (label8), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (label8), 0, 0.5);

  label9 = gtk_label_new (_("Minute:"));
  gtk_widget_show (label9);
  gtk_table_attach (GTK_TABLE (table1), label9, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_justify (GTK_LABEL (label9), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (label9), 0, 0.5);

  label10 = gtk_label_new (_("Second:"));
  gtk_widget_show (label10);
  gtk_table_attach (GTK_TABLE (table1), label10, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_justify (GTK_LABEL (label10), GTK_JUSTIFY_RIGHT);
  gtk_misc_set_alignment (GTK_MISC (label10), 0, 0.5);

  spinbutton1_adj = gtk_adjustment_new (22, 0, 23, 1, 10, 10);
  spinbutton1 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton1_adj), 1, 0);
  gtk_widget_show (spinbutton1);
  gtk_table_attach (GTK_TABLE (table1), spinbutton1, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (spinbutton1), TRUE);
  gtk_spin_button_set_snap_to_ticks (GTK_SPIN_BUTTON (spinbutton1), TRUE);
  gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinbutton1), TRUE);

  spinbutton2_adj = gtk_adjustment_new (0, 0, 59, 1, 10, 10);
  spinbutton2 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton2_adj), 1, 0);
  gtk_widget_show (spinbutton2);
  gtk_table_attach (GTK_TABLE (table1), spinbutton2, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (spinbutton2), TRUE);
  gtk_spin_button_set_snap_to_ticks (GTK_SPIN_BUTTON (spinbutton2), TRUE);
  gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinbutton2), TRUE);

  spinbutton3_adj = gtk_adjustment_new (0, 0, 59, 1, 10, 10);
  spinbutton3 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton3_adj), 1, 0);
  gtk_widget_show (spinbutton3);
  gtk_table_attach (GTK_TABLE (table1), spinbutton3, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (spinbutton3), TRUE);
  gtk_spin_button_set_snap_to_ticks (GTK_SPIN_BUTTON (spinbutton3), TRUE);
  gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (spinbutton3), TRUE);

  label4 = gtk_label_new (_("Time"));
  gtk_widget_show (label4);
  gtk_frame_set_label_widget (GTK_FRAME (frame2), label4);
  gtk_label_set_justify (GTK_LABEL (label4), GTK_JUSTIFY_LEFT);

  frame3 = gtk_frame_new (NULL);
  gtk_widget_show (frame3);
  gtk_box_pack_start (GTK_BOX (vbox1), frame3, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame3), 8);

  vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox2);
  gtk_container_add (GTK_CONTAINER (frame3), vbox2);

  label11 = gtk_label_new (_("Your computer can synchronize its clock with a remote time server using the Network Time Protocol"));
  gtk_widget_show (label11);
  gtk_box_pack_start (GTK_BOX (vbox2), label11, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (label11), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label11), TRUE);

  checkbutton1 = gtk_check_button_new_with_mnemonic (_("_Enable Network Time Protocol"));
  gtk_widget_show (checkbutton1);
  gtk_box_pack_start (GTK_BOX (vbox2), checkbutton1, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (checkbutton1), 8);

  hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox2);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox2, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox2), 8);

  label12 = gtk_label_new (_("Server: "));
  gtk_widget_show (label12);
  gtk_box_pack_start (GTK_BOX (hbox2), label12, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (label12), GTK_JUSTIFY_LEFT);

  combo1 = gtk_combo_new ();
  g_object_set_data (G_OBJECT (GTK_COMBO (combo1)->popwin),
                     "GladeParentKey", combo1);
  gtk_widget_show (combo1);
  gtk_box_pack_start (GTK_BOX (hbox2), combo1, TRUE, TRUE, 0);

  combo_entry1 = GTK_COMBO (combo1)->entry;
  gtk_widget_show (combo_entry1);

  label5 = gtk_label_new (_("Network Time Protocol"));
  gtk_widget_show (label5);
  gtk_frame_set_label_widget (GTK_FRAME (frame3), label5);
  gtk_label_set_justify (GTK_LABEL (label5), GTK_JUSTIFY_LEFT);

  label1 = gtk_label_new (_("Date & Time"));
  gtk_widget_show (label1);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 0), label1);
  gtk_label_set_justify (GTK_LABEL (label1), GTK_JUSTIFY_LEFT);

  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox3);
  gtk_container_add (GTK_CONTAINER (notebook1), vbox3);

  label13 = gtk_label_new (_("Please select the nearest city in your timezone:"));
  gtk_widget_show (label13);
  gtk_box_pack_start (GTK_BOX (vbox3), label13, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (label13), GTK_JUSTIFY_LEFT);

  drawingarea1 = gtk_drawing_area_new ();
  gtk_widget_show (drawingarea1);
  gtk_box_pack_start (GTK_BOX (vbox3), drawingarea1, FALSE, TRUE, 0);
  gtk_widget_set_size_request (drawingarea1, 480, 240);

  label14 = gtk_label_new ("");
  gtk_widget_show (label14);
  gtk_box_pack_start (GTK_BOX (vbox3), label14, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (label14), GTK_JUSTIFY_LEFT);

  hseparator1 = gtk_hseparator_new ();
  gtk_widget_show (hseparator1);
  gtk_box_pack_start (GTK_BOX (vbox3), hseparator1, FALSE, FALSE, 8);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox3), scrolledwindow1, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (scrolledwindow1), 8);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  treeview1 = gtk_tree_view_new ();
  gtk_widget_show (treeview1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), treeview1);
  gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (treeview1), FALSE);

  checkbutton2 = gtk_check_button_new_with_mnemonic (_("_System clock uses UTC"));
  gtk_widget_show (checkbutton2);
  gtk_box_pack_start (GTK_BOX (vbox3), checkbutton2, FALSE, FALSE, 0);

  label2 = gtk_label_new (_("Timezone"));
  gtk_widget_show (label2);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 1), label2);
  gtk_label_set_justify (GTK_LABEL (label2), GTK_JUSTIFY_LEFT);

  dialog_action_area1 = GTK_DIALOG (MainWindow)->action_area;
  gtk_widget_show (dialog_action_area1);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);

  helpbutton1 = gtk_button_new_from_stock ("gtk-help");
  gtk_widget_show (helpbutton1);
  gtk_dialog_add_action_widget (GTK_DIALOG (MainWindow), helpbutton1, GTK_RESPONSE_HELP);
  GTK_WIDGET_SET_FLAGS (helpbutton1, GTK_CAN_DEFAULT);

  cancelbutton1 = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (cancelbutton1);
  gtk_dialog_add_action_widget (GTK_DIALOG (MainWindow), cancelbutton1, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (cancelbutton1, GTK_CAN_DEFAULT);

  okbutton1 = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (okbutton1);
  gtk_dialog_add_action_widget (GTK_DIALOG (MainWindow), okbutton1, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (okbutton1, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) MainWindow, "delete_event",
                    G_CALLBACK (on_MainWindow_close),
                    NULL);
  g_signal_connect ((gpointer) calendar1, "day_selected",
                    G_CALLBACK (on_calendar1_day_selected),
                    NULL);
  g_signal_connect ((gpointer) calendar1, "month_changed",
                    G_CALLBACK (on_calendar1_month_changed),
                    NULL);
  g_signal_connect ((gpointer) spinbutton1, "changed",
                    G_CALLBACK (on_spinbutton1_changed),
                    NULL);
  g_signal_connect ((gpointer) spinbutton2, "changed",
                    G_CALLBACK (on_spinbutton2_changed),
                    NULL);
  g_signal_connect ((gpointer) spinbutton3, "changed",
                    G_CALLBACK (on_spinbutton3_changed),
                    NULL);
  g_signal_connect ((gpointer) checkbutton1, "toggled",
                    G_CALLBACK (on_checkbutton1_toggled),
                    NULL);
  g_signal_connect ((gpointer) combo_entry1, "changed",
                    G_CALLBACK (on_combo_entry1_changed),
                    NULL);
  g_signal_connect ((gpointer) drawingarea1, "motion_notify_event",
                    G_CALLBACK (on_drawingarea1_motion_notify_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea1, "button_press_event",
                    G_CALLBACK (on_drawingarea1_button_press_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea1, "leave_notify_event",
                    G_CALLBACK (on_drawingarea1_leave_notify_event),
                    NULL);
  g_signal_connect ((gpointer) drawingarea1, "expose_event",
                    G_CALLBACK (on_drawingarea1_expose_event),
                    NULL);
  g_signal_connect ((gpointer) treeview1, "row_activated",
                    G_CALLBACK (on_treeview1_row_activated),
                    NULL);
  g_signal_connect ((gpointer) checkbutton2, "toggled",
                    G_CALLBACK (on_checkbutton2_toggled),
                    NULL);
  g_signal_connect ((gpointer) helpbutton1, "clicked",
                    G_CALLBACK (on_helpbutton1_clicked),
                    NULL);
  g_signal_connect ((gpointer) cancelbutton1, "clicked",
                    G_CALLBACK (on_cancelbutton1_clicked),
                    NULL);
  g_signal_connect ((gpointer) okbutton1, "clicked",
                    G_CALLBACK (on_okbutton1_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (MainWindow, MainWindow, "MainWindow");
  GLADE_HOOKUP_OBJECT_NO_REF (MainWindow, dialog_vbox1, "dialog_vbox1");
  GLADE_HOOKUP_OBJECT (MainWindow, notebook1, "notebook1");
  GLADE_HOOKUP_OBJECT (MainWindow, vbox1, "vbox1");
  GLADE_HOOKUP_OBJECT (MainWindow, hbox1, "hbox1");
  GLADE_HOOKUP_OBJECT (MainWindow, frame1, "frame1");
  GLADE_HOOKUP_OBJECT (MainWindow, calendar1, "calendar1");
  GLADE_HOOKUP_OBJECT (MainWindow, label3, "label3");
  GLADE_HOOKUP_OBJECT (MainWindow, frame2, "frame2");
  GLADE_HOOKUP_OBJECT (MainWindow, table1, "table1");
  GLADE_HOOKUP_OBJECT (MainWindow, label6, "label6");
  GLADE_HOOKUP_OBJECT (MainWindow, label7, "label7");
  GLADE_HOOKUP_OBJECT (MainWindow, label8, "label8");
  GLADE_HOOKUP_OBJECT (MainWindow, label9, "label9");
  GLADE_HOOKUP_OBJECT (MainWindow, label10, "label10");
  GLADE_HOOKUP_OBJECT (MainWindow, spinbutton1, "spinbutton1");
  GLADE_HOOKUP_OBJECT (MainWindow, spinbutton2, "spinbutton2");
  GLADE_HOOKUP_OBJECT (MainWindow, spinbutton3, "spinbutton3");
  GLADE_HOOKUP_OBJECT (MainWindow, label4, "label4");
  GLADE_HOOKUP_OBJECT (MainWindow, frame3, "frame3");
  GLADE_HOOKUP_OBJECT (MainWindow, vbox2, "vbox2");
  GLADE_HOOKUP_OBJECT (MainWindow, label11, "label11");
  GLADE_HOOKUP_OBJECT (MainWindow, checkbutton1, "checkbutton1");
  GLADE_HOOKUP_OBJECT (MainWindow, hbox2, "hbox2");
  GLADE_HOOKUP_OBJECT (MainWindow, label12, "label12");
  GLADE_HOOKUP_OBJECT (MainWindow, combo1, "combo1");
  GLADE_HOOKUP_OBJECT (MainWindow, combo_entry1, "combo_entry1");
  GLADE_HOOKUP_OBJECT (MainWindow, label5, "label5");
  GLADE_HOOKUP_OBJECT (MainWindow, label1, "label1");
  GLADE_HOOKUP_OBJECT (MainWindow, vbox3, "vbox3");
  GLADE_HOOKUP_OBJECT (MainWindow, label13, "label13");
  GLADE_HOOKUP_OBJECT (MainWindow, drawingarea1, "drawingarea1");
  GLADE_HOOKUP_OBJECT (MainWindow, label14, "label14");
  GLADE_HOOKUP_OBJECT (MainWindow, hseparator1, "hseparator1");
  GLADE_HOOKUP_OBJECT (MainWindow, scrolledwindow1, "scrolledwindow1");
  GLADE_HOOKUP_OBJECT (MainWindow, treeview1, "treeview1");
  GLADE_HOOKUP_OBJECT (MainWindow, checkbutton2, "checkbutton2");
  GLADE_HOOKUP_OBJECT (MainWindow, label2, "label2");
  GLADE_HOOKUP_OBJECT_NO_REF (MainWindow, dialog_action_area1, "dialog_action_area1");
  GLADE_HOOKUP_OBJECT (MainWindow, helpbutton1, "helpbutton1");
  GLADE_HOOKUP_OBJECT (MainWindow, cancelbutton1, "cancelbutton1");
  GLADE_HOOKUP_OBJECT (MainWindow, okbutton1, "okbutton1");

  return MainWindow;
}
