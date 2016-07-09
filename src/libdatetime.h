#ifndef LIBDATETIME_H
#define LIBDATETIME_H

#include <gtk/gtk.h>

#define ZONETAB "/usr/share/zoneinfo/zone.tab"
#define NTPCONF "/etc/ntp.conf"
#define TIMEZONE_FILE "/etc/timezone"
#define BOOT_SCRIPT_DEFAULTS "/etc/default/rcS"

#define DEBUG

#ifdef DEBUG
#define debug printf
#else
#define debug (void)
#endif

struct timezone{
	gchar code[3];
	gint lat;
	gint lon;
	gchar tz[64];
	gchar comment[256];
} *timezones;

typedef struct timezone tz_struct;

gint timezones_count;
gchar read_tz[64];

/*
  returns the ntp server from disk
*/

gchar * get_ntp_server();

/*
  writes the ntp configuration to disk
*/

gboolean set_ntp_server(gchar *ntp_ptr);

/*
  disables ntp servers on disk
*/

gboolean disable_ntp_servers();

/*
  checks if the ntp package is installed (well, sortof)
*/

gboolean check_ntp_installed();

/*
  reads all available timezones
*/

gboolean read_zone_info();

/*
  frees all timezone info
*/

gboolean free_zone_info();

/*
  find the nearest timezone using latitude/longitude
*/

tz_struct * find_nearest_entry(int lat, int lon);

/*
  write the date/time to disk/bios?
*/

gboolean write_date_time(struct tm *dm);

/*
  returns the current date/time
*/

struct tm* get_current_date_time();

/*
  if the hwclock is to be set to UTC
*/

gboolean sync_hardware_clock(gboolean utc);

/*
  if the systemtime is to be set to UTC
*/

gboolean set_system_utc(gboolean utc);

/*
  restart the ntp client, re-reading it's configuration info
*/

void restart_ntp_client();

/*
  read the current timezone from disk
*/

gboolean read_current_timezone();

/*
  find the timezone entry for a name of a timezone
*/

tz_struct * find_timezone_entry(gchar *timezone);

/*
  functions for converting coordinates from/to latitude/longitude
*/

int map2canvas_lat(int lat, int map_height);
int map2canvas_lon(int lon, int map_width);

int canvas2map_lat(int y, int map_height);
int canvas2map_lon(int x, int map_width);
int convert_coord_lat(gchar *lat);
int convert_coord_lon(gchar *lon);

#endif
