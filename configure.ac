AC_INIT([geoip-gobject],
        [1.0],
        [https://github.com/skybon/geoip-gobject/issues],
        [geoip-gobject],
        [https://github.com/skybon/geoip-gobject])

AM_INIT_AUTOMAKE([-Wno-portability])

AC_CONFIG_MACRO_DIR([m4])

LT_INIT

GOBJECT_INTROSPECTION_CHECK([1.30.0])

VAPIGEN_CHECK

m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.25],[--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
])

PKG_CHECK_MODULES(GEOIP_GOBJECT, [
  glib-2.0
  gobject-2.0
  geoip
])

AC_CONFIG_FILES([
  Makefile
  geoip/Makefile
  geoip/geoip-gobject-1.0.pc
  docs/Makefile
  docs/reference/Makefile
  docs/reference/geoip/Makefile
])

AC_OUTPUT
