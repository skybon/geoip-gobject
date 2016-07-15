geoip_gobjectdir = $(includedir)/geoip-gobject-1.0
geoip_gobject_HEADERS = geoip-gobject.h \
                        geoip-geodata.h  \
                        $(NULL)

lib_LTLIBRARIES = libgeoip-gobject-1.0.la

libgeoip_gobject_1_0_la_SOURCES =        \
                        geoip-gobject.h  \
                        geoip-geodata.h  \
                        geoip-geodata.c  \
                        $(BUILT_SOURCES) \
                        $(NULL)

libgeoip_gobject_1_0_la_CFLAGS =                \
                        $(GEOIP_GOBJECT_CFLAGS) \
                        $(NULL)

libgeoip_gobject_1_0_la_LIBADD =              \
                        $(GEOIP_GOBJECT_LIBS) \
                        $(LIBS)               \
                        $(NULL)


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = geoip-gobject-1.0.pc

CLEANFILES =
EXTRA_DIST =

include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION
introspection_sources = $(libgeoip_gobject_1_0_la_SOURCES)

Geoip-1.0.gir: libgeoip-gobject-1.0.la
Geoip_1_0_gir_FILES = $(introspection_sources)
Geoip_1_0_gir_LIBS = libgeoip-gobject-1.0.la
Geoip_1_0_gir_INCLUDES = GObject-2.0
Geoip_1_0_gir_CFLAGS = $(INCLUDES)
Geoip_1_0_gir_NAMESPACE = Geoip
Geoip_1_0_gir_VERSION = 1.0
INTROSPECTION_GIRS += Geoip-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

if ENABLE_VAPIGEN
-include $(VAPIGEN_MAKEFILE)

geoip-gobject-1.0.vapi: Geoip-1.0.gir

VAPIGEN_VAPIS = geoip-gobject-1.0.vapi

geoip_gobject_1_0_vapi_METADATADIRS = $(srcdir)
geoip_gobject_1_0_vapi_FILES = Geoip-1.0.gir

vapidir = $(datadir)/vala/vapi
vapi_DATA = $(VAPIGEN_VAPIS)

EXTRA_DIST += Geoip-1.0.metadata
endif

CLEANFILES += $(gir_DATA) $(typelib_DATA)
endif
