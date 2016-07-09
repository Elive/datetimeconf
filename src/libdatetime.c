/* 
	backend to datetimeconf
   
Copyright (C) 2003 Alex de Landgraaf <alextreme@xs4all.nl>

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
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. 


   inspired by dateBackend.py in the Fedora config tools/redhat-config-date
     Copyright (C) 2001, 2002 Red Hat, Inc.
     Copyright (C) 2001, 2002 Brent Fox <bfox@redhat.com>
                              Tammy Fox <tfox@redhat.com>

*/

#include <gtk/gtk.h>
#include "libdatetime.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

gboolean exec_command (gchar *command) {
	gchar *outbuffer;
	gchar cmdline[256];
	gint exitstatus;

	debug("Exec: %s\n",command);
	if (g_spawn_command_line_sync(command,&outbuffer,NULL,&exitstatus,NULL) == FALSE) {
		debug("Error occured executing command\n");
		return FALSE;
	}
	free(outbuffer);
	return TRUE;
}

gboolean check_ntp_installed() {
	FILE *fp = fopen("/etc/init.d/ntp","r");
	if (fp == NULL) {
		return NULL;
	}
	fclose(fp);
	return TRUE;
}

/*
  probes /etc/ntp.conf for a server line
  if it can't find one, return NULL */

gchar * get_ntp_server() {
	gchar **ntp_array = NULL;
	gchar *ntpline = NULL;
	gint ntp_len, i, ret;
	gchar *ntp_ptr = NULL;

	if (!g_file_get_contents(NTPCONF,&ntpline,&ntp_len,NULL)) {
		return NULL;
	}
	
	ntp_array = g_strsplit(ntpline,"\n",0);
	if (ntp_array == NULL) {
		free(ntpline);
		return NULL;
	}
	for (i = 0; ntp_array[i] != NULL; i++) {
		gchar ntp_serv[128];
		ret = sscanf(ntp_array[i],"server %127s",ntp_serv);
		if (ret != 1) {
			continue;
		}
		ntp_ptr = (gchar *) strdup(ntp_serv);
		break;
	}
	g_strfreev(ntp_array);
	free(ntpline);
	return ntp_ptr;
}

gboolean disable_ntp_servers() {
	gchar **ntp_array = NULL;
	gchar *ntpline = NULL;
	gint ntp_len, i, ret;
	FILE *fp = NULL;
	if (!g_file_get_contents(NTPCONF,&ntpline,&ntp_len,NULL)) {
		return TRUE;
	}
	
	ntp_array = g_strsplit(ntpline,"\n",0);
	if (ntp_array == NULL) {
		free(ntpline);
		return FALSE;
	}
	fp = fopen(NTPCONF,"w");
	if (fp == NULL) {
			debug("Error: Can't open /etc/ntp.conf, aborting\n");
			return FALSE;
	}
	for (i = 0; ntp_array[i] != NULL; i++) {
		gchar ntpserver[126];
		ret = sscanf(ntp_array[i],"server %127s",ntpserver);
		if (ret != 1) {
			fprintf(fp,"%s\n",ntp_array[i]);
			continue;
		}
		fprintf(fp,"#server %s\n",ntpserver);
	}
	fclose(fp);
	g_strfreev(ntp_array);
	free(ntpline);
	return TRUE;
}

/*
  overwrites the first entry in /etc/ntp.conf with the new 
  ntp server entry
*/

gboolean set_ntp_server(gchar *ntp_ptr) {
	gchar **ntp_array = NULL;
	gchar *ntpline = NULL;
	gint ntp_len, i, ret, written;
	FILE *fp = NULL;
	if (!g_file_get_contents(NTPCONF,&ntpline,&ntp_len,NULL)) {
		fp = fopen(NTPCONF,"w");
		if (fp == NULL) {
			debug("Error: Can't open /etc/ntp.conf, aborting\n");
			return FALSE;
		}
		fprintf(fp,"server %s",ntp_ptr);
		fclose(fp);
		return TRUE;
	}
	
	ntp_array = g_strsplit(ntpline,"\n",0);
	if (ntp_array == NULL) {
		free(ntpline);
		return FALSE;
	}
	written = 0;
	fp = fopen(NTPCONF,"w");
	if (fp == NULL) {
			debug("Error: Can't open /etc/ntp.conf, aborting\n");
			return FALSE;
	}
	for (i = 0; ntp_array[i] != NULL; i++) {
		ret = sscanf(ntp_array[i],"server %*s");
		if (ret != 1 || written == 1) {
			fprintf(fp,"%s\n",ntp_array[i]);
			continue;
		}
		fprintf(fp,"server %s\n",ntp_ptr);
		written = 1;
	}
	fclose(fp);
	g_strfreev(ntp_array);
	free(ntpline);
	return TRUE;
}
/*
  read zone information,
  saves in timezones[] 
  returns if succeded */

gboolean read_zone_info() {
	gchar **zone_array = NULL;
	gchar *zones = NULL;
	gint zones_len;
	gint i, j, ret;
	
	if (!g_file_get_contents(ZONETAB,&zones,&zones_len,NULL)) {
		return FALSE;
	}
	
	zone_array = g_strsplit(zones,"\n",0);
	if (zone_array == NULL || zones == NULL) {
		debug("Error: unable to read zone info\n");
		return FALSE;
	}
	i = 0;
	while (zone_array[i] != NULL) {
		if (zone_array[i][0] != '#' && zone_array[i][0] != '\0') 
			timezones_count++;
		i++;
	}
	j = 0;
	timezones = (struct timezone*) malloc(sizeof(tz_struct) * timezones_count);
	debug("size of struct: %d\n",sizeof(tz_struct));
	for (i = 0; zone_array[i] != NULL; i++) {
		gchar tz[64];
		gchar comment[255];
		gchar code[3];
		gchar plusminlat, plusminlon;
		gchar blaat[36];
		gchar lat[12], lon[12];
		gchar lat2[13], lon2[13];
		if (zone_array[i][0] == '#')
			continue;
		strcpy(comment,"");
		// valid zone entry... we hope
		ret = sscanf(zone_array[i],"%2s\t%[+-]%11[0-9]%[+-]%11[0-9]\t%63s\t%254[^\n]",code,&plusminlat,&lat,&plusminlon,&lon,tz,&comment);
		if (ret <= 5) {
			debug("code: %s, ret: %d\n",code,ret);
			continue;
		}
		strcpy(timezones[j].code,code);

		sprintf(lat2,"%c%s",plusminlat,lat);
		sprintf(lon2,"%c%s",plusminlon,lon);
		
		timezones[j].lat = convert_coord_lat(lat2);
		timezones[j].lon = convert_coord_lon(lon2);

		strcpy(timezones[j].tz,tz);
		if (ret == 5 || strcmp(comment,"") == 0) {
			strcpy(timezones[j].comment,"");
		}
		else {
			strcpy(timezones[j].comment,comment);
		}
		j++;
	}	
	g_strfreev(zone_array);
//	free(zones); /* think something of zones isn't copied, segfaults when uncommented, need to run splint on this... */
	return TRUE;
}

/*
  free's timezones 
*/

int free_zone_info() {
	free(timezones); // FIXME
	return TRUE;
}

/*
  returns a struct of type tm
  with the current date and time information
*/

struct tm* get_current_date_time() {
	struct tm *dt = (struct tm *)malloc(sizeof(const struct tm));
	time_t time_s;
	time(&time_s);
	dt = localtime(&time_s);
	return dt;		 
}

/*
  sets the given date/time information
*/

gboolean write_date_time(struct tm *dt) {
	gchar cmdline[256];
	sprintf(cmdline,"/bin/date %02d%02d%02d%02d%04d.%02d",dt->tm_mon+1,dt->tm_mday,dt->tm_hour,dt->tm_min,dt->tm_year,dt->tm_sec);
	exec_command(cmdline);
	return TRUE;
}

/*
  sync's the hardware clock, either in local or UTC time
*/

gboolean sync_hardware_clock(gboolean utc) {
	gchar cmdline[256];
	debug("Sycing hardware clock, utc: %d\n",utc);
	if (utc == TRUE) {
		sprintf(cmdline,"/sbin/hwclock --systohc --utc");
	}
	else {
		sprintf(cmdline,"/sbin/hwclock --systohc");
	}
	exec_command(cmdline);

	return TRUE;
}

gboolean check_system_utc() {
	gchar **utc_array = NULL;
	gchar *utc_string = NULL;
	gint utc_len, i;
	gboolean utc = FALSE;

	if (!g_file_get_contents(BOOT_SCRIPT_DEFAULTS,&utc_string,&utc_len,NULL)) {
		return FALSE;
	}
	
	/* generate a modules script */
	utc_array = g_strsplit(utc_string,"\n",0);
	if (utc_array == NULL || utc_string == NULL) {
		debug("Error: unable to read default bootscript info\n");
		return FALSE;
	}
	for (i = 0; utc_array[i] != NULL; i++) {
		if (strcmp(utc_array[i],"UTC=no") == 0) {
			utc = FALSE;
			break;
		}
		if (strcmp(utc_array[i],"UTC=yes") == 0) {
			utc = TRUE;
			break;
		}
	}
	g_strfreev(utc_array);
	free(utc_string);

	debug("parsed bootscript defaults, utc: %d\n",utc);
	
	return utc;
}

gboolean set_system_utc(gboolean utc) {
	gchar **utc_array = NULL;
	gchar *utc_string = NULL;
	gint utc_len, i;

	FILE *fp = NULL;
	if (!g_file_get_contents(BOOT_SCRIPT_DEFAULTS,&utc_string,&utc_len,NULL)) {
		return FALSE;
	}
	
	/* generate a modules script */
	utc_array = g_strsplit(utc_string,"\n",0);
	if (utc_array == NULL || utc_string == NULL) {
		debug("Error: unable to read default bootscript info\n");
		return FALSE;
	}
	fp = fopen(BOOT_SCRIPT_DEFAULTS,"w");
	for (i = 0; utc_array[i] != NULL; i++) {
		if (strncmp(utc_array[i],"UTC=",4) == 0) {
			if (utc == TRUE) {
				debug("Setting UTC to yes\n");
				fprintf(fp,"UTC=yes\n");
			}
			else {
				debug("Setting UTC to no\n");
				fprintf(fp,"UTC=no\n");
			}
		}
		else {
			fprintf(fp,"%s\n",utc_array[i]);
		}
	}
	fclose(fp);	
	g_strfreev(utc_array);
	free(utc_string);
	return TRUE;
}
	

void restart_ntp_client() {
	gchar cmdline[256];
	sprintf(cmdline,"/etc/init.d/ntpdate restart");
	exec_command(cmdline);
}

/*
  timezone functions
*/

/*
  returns the closest entry based on latitude/longitude
  can be called only after read_zone_tab has been called
  returns the nearest entry, else NULL
*/

tz_struct * find_nearest_entry(int lat, int lon) {
	tz_struct *nearest = NULL;
	int i, min = -1;
	for (i = 0; i < timezones_count; i++) {
		int dy, dx, dist;
		
		dx = timezones[i].lon - lon;
		dy = timezones[i].lat - lat;
		dist = (dy * dy) + (dx * dx);
		if (dist < min || min == -1) {
			min = dist;
			nearest = (tz_struct *)&timezones[i];
		}
	}
	return nearest;
}

/*
  can be called only after read_zone_tab has been called
  returns the first corresponding entry if found, NULL if not
*/

tz_struct * find_timezone_entry(gchar *timezone) {
	gint i;
	tz_struct *tz_p = NULL;
	for (i = 0; i < timezones_count; i++) {
		if (strncmp(timezones[i].tz,timezone,63) == 0) {
			tz_p = &timezones[i];
		}
	}
	return tz_p;
}

int convert_coord_lat(gchar *lat) {
	// with latitude, the first 3 numbers are the degrees,
	// the rest are the minutes

	gchar degrees[4];
	sscanf(lat,"%3s",degrees);
	gchar minutes[6];
	sscanf(lat,"%*3s%5s",minutes);
	if (atoi(degrees) > 0) {
		return atoi(degrees) + atoi(minutes)/(pow(10,strlen(minutes)));
	}
	else {
		return atoi(degrees) - atoi(minutes)/(pow(10,strlen(minutes)));
	}
}

/*
  write the given timezone to disk
*/

void write_timezone(tz_struct *tz) {
	FILE *fp = fopen(TIMEZONE_FILE,"w");
	if (tz->tz != NULL) {
		fprintf(fp,"%s\n",tz->tz);
	}
	fclose(fp);
	
}

/*
  read the current set timezone
  must be called after zonetab has been processed (read_zone_info())
*/

gboolean read_current_timezone() {
	FILE *fp = fopen(TIMEZONE_FILE,"r");
	if (fp != NULL) {
		fscanf(fp,"%63s",read_tz);
		fclose(fp);
	}
	else {
		return FALSE;
	}
	return TRUE;
}

int convert_coord_lon(gchar *lon) {
	// with longitude, the first 4 numbers are the degrees,
	// the rest are the minutes

	gchar degrees[5];
	sscanf(lon,"%4s",degrees);
	gchar minutes[6];
	sscanf(lon,"%*4s%5s",minutes);
	if (atoi(degrees) > 0) {
		return atoi(degrees) + atoi(minutes)/(pow(10,strlen(minutes)));
	}
	else {
		return atoi(degrees) - atoi(minutes)/(pow(10,strlen(minutes)));
	}
}

/*
  convertion functions for lat/longitude <-> x/y coordinates of the map
*/

int map2canvas_lat(int lat, int map_height) {
	// returns y
	return map_height / 2.0 - (map_height / 2.0) * lat / 90.0;
}

int map2canvas_lon(int lon, int map_width) {
	// returns x
	return map_width / 2.0 + (map_width / 2.0) * lon / 180.0;
}

int canvas2map_lat(int y, int map_height) {
	return (map_height / 2.0 - y) / (map_height / 2.0) * 90.0;
}

int canvas2map_lon(int x, int map_width) {
	return (x - map_width / 2.0) / (map_width / 2.0) * 180.0;
}
