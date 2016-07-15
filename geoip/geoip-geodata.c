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

#include "geoip-geodata.h"

/* Private structure definition */
typedef struct {
    GMutex m ;
    gboolean is_loaded ;
    gchar * filename ;
    GeoIP * data ;
} GeoipGeodataPrivate ;

struct _GeoipGeodata {
    GObject parent_instance ;
} ;

G_DEFINE_TYPE_WITH_PRIVATE (GeoipGeodata, geoip_geodata, G_TYPE_OBJECT);

static void geoip_geodata_unload_data(GeoipGeodataPrivate * priv) {
    if( priv->is_loaded == TRUE ){
        GeoIP_delete (priv->data) ;
        g_free (priv->filename) ;
        priv->filename = NULL ;
        priv->is_loaded = FALSE ;
    }
}

static void geoip_geodata_dispose(GObject * gobject) {
    GeoipGeodataPrivate * priv = geoip_geodata_get_instance_private (GEOIP_GEODATA (gobject)) ;
    g_mutex_lock (&priv->m) ;
    geoip_geodata_unload_data (priv) ;
    g_mutex_unlock (&priv->m) ;

    G_OBJECT_CLASS (geoip_geodata_parent_class)->dispose (gobject) ;
}

static void geoip_geodata_finalize(GObject * gobject) {
    G_OBJECT_CLASS (geoip_geodata_parent_class)->finalize (gobject) ;
}

static void geoip_geodata_class_init(GeoipGeodataClass * klass) {
    GObjectClass * object_class = G_OBJECT_CLASS (klass) ;

    object_class->dispose = geoip_geodata_dispose ;
    object_class->finalize = geoip_geodata_finalize ;
}

G_DEFINE_QUARK (geoip-geodata-error-quark, geoip_geodata_error)

static void geoip_geodata_init(GeoipGeodata * self) {
    GeoipGeodataPrivate * priv = geoip_geodata_get_instance_private (self) ;

    g_mutex_init (&priv->m) ;
    priv->data = NULL ;
    priv->filename = NULL ;
    priv->is_loaded = FALSE ;
}

GeoipGeodata * geoip_geodata_new() {
    return g_object_new (GEOIP_TYPE_GEODATA, NULL) ;
}

/**
 * geoip_geodata_load_from_file
 * @geodata: #Geodata instance
 * @filename: GeoIP data file to open
 *
 * Loads GeoIP data file to use with Geodata instance.
 *
 * Returns: %TRUE if data was loaded Successfully, %FALSE otherwise.
 */
gboolean
geoip_geodata_load_from_file(GeoipGeodata * geodata,
                             const char *   filename)
{
    GeoipGeodataPrivate * priv = geoip_geodata_get_instance_private (geodata) ;

    gboolean v ;

    g_mutex_lock (&priv->m) ;
    geoip_geodata_unload_data (priv) ;

    priv->data = GeoIP_open (filename, GEOIP_MEMORY_CACHE) ;
    if( priv->data != NULL ){
        priv->filename = g_strdup (filename) ;
        priv->is_loaded = TRUE ;
    }
    v = priv->is_loaded ;
    g_mutex_unlock (&priv->m) ;

    return v ;
}

/**
 * geoip_geodata_country_code_by_addr
 * @geodata: #Geodata instance
 * @addr: IP address to look up
 * @error: return location for a #GError or %NULL
 *
 * Returns ISO code of the country where IP address is located.
 *
 * Returns: country code or %NULL if an error occurred.
 */
gchar *
geoip_geodata_country_code_by_addr(GeoipGeodata * geodata,
                                   const char *   addr,
                                   GError **      error)
{
    GeoipGeodataPrivate * priv = geoip_geodata_get_instance_private (geodata) ;

    if (!priv->is_loaded) {
        g_set_error_literal (error, GEOIP_GEODATA_ERROR, GEOIP_GEODATA_ERROR_DATA_NOT_LOADED, "Geodata is empty.") ;
        return NULL ;
    }

    return g_strdup (GeoIP_country_code_by_addr (priv->data, addr)) ;
}

/**
 * geoip_geodata_country_code_by_name
 * @geodata: #Geodata instance
 * @name: Hostname to look up
 * @error: return location for a #GError or %NULL
 *
 * Resolves hostname and returns ISO code of the country where IP address is located.
 *
 * Returns: country code or %NULL if an error occurred.
 */
gchar *
geoip_geodata_country_code_by_name(GeoipGeodata * geodata,
                                   const char *   name,
                                   GError **      error)
{
    GeoipGeodataPrivate * priv = geoip_geodata_get_instance_private (geodata) ;

    if (!priv->is_loaded) {
        g_set_error_literal (error, GEOIP_GEODATA_ERROR, GEOIP_GEODATA_ERROR_DATA_NOT_LOADED, "Geodata is empty.") ;
        return NULL ;
    }

    return g_strdup (GeoIP_country_code_by_name (priv->data, name)) ;
}

void
geoip_geodata_print_status(GeoipGeodata * self)
{
    GeoipGeodataPrivate * priv = geoip_geodata_get_instance_private (self) ;

    if( priv->is_loaded == TRUE ){
        printf ("Successfully loaded GeoIP database file: %s.\n", priv->filename) ;
    } else {
        printf ("No GeoIP data loaded.\n") ;
    }
}
