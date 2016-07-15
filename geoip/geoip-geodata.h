/*
 * This file is part of geoip-gobject.
 *
 * https://github.com/skybon/geoip-gobject
 * Copyright (C) 2016 Artem Vorotnikov
 *
 * geoip-gobject is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * geoip-gobject is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with geoip-gobject. If not, see <http://www.gnu.org/licenses/>.
 */

/* inclusion guard */
#ifndef __GEOIP_GEODATA_H__
#define __GEOIP_GEODATA_H__

#include <glib-object.h>

#include <GeoIP.h>

G_BEGIN_DECLS

#define GEOIP_TYPE_GEODATA geoip_geodata_get_type ()
G_DECLARE_FINAL_TYPE(GeoipGeodata, geoip_geodata, GEOIP, GEODATA, GObject)

typedef enum
{
  GEOIP_GEODATA_ERROR_DATA_NOT_LOADED,
  GEOIP_GEODATA_ERROR_INVALID_ADDR
} GeoipGeodataError;

/**
 * GEOIP_GEODATA_ERROR:
 *
 * Error domain for Geodata.
 *
 * Since: 1.0
 */
#define GEOIP_GEODATA_ERROR geoip_geodata_error_quark()

GQuark geoip_geodata_error_quark ();

GeoipGeodata * geoip_geodata_new () ;
gboolean geoip_geodata_load_from_file(GeoipGeodata * geodata, const char * filename) ;
gchar * geoip_geodata_country_code_by_addr(GeoipGeodata * geodata, const char * addr, GError ** error) ;
gchar * geoip_geodata_country_code_by_name(GeoipGeodata * geodata, const char * name, GError ** error) ;
void geoip_geodata_print_status(GeoipGeodata *) ;

G_END_DECLS

#endif
