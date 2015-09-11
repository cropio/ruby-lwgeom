#include <ruby.h>
#include <liblwgeom.h>

double EARTH_MAJOR_AXIS_RADIUS = 6378137.0;
double EARTH_MINOR_AXIS_RADIUS = 6356752.314245179498;

LWGEOM *lwg;
SPHEROID s;

static VALUE get_area(VALUE self, VALUE geom_wkt)
{
  lwg = lwgeom_from_wkt(RSTRING_PTR(geom_wkt), 0);
  double area = lwgeom_area_spheroid(lwg, &s);
  lwgeom_free(lwg);

  return rb_float_new(area);
}

VALUE get_length(VALUE self, VALUE geom_wkt)
{
  lwg = lwgeom_from_wkt(RSTRING_PTR(geom_wkt), 0);
  double length = lwgeom_length_spheroid(lwg, &s);
  lwgeom_free(lwg);

  return rb_float_new(length);
}

void Init_lwgeom()
{
  /* define module */
  VALUE mLwGeom = rb_define_module("LwGeom");

  /* define class */
  VALUE cSpheroid = rb_define_class_under(mLwGeom, "Spheroid", rb_cObject);

  rb_define_module_function(cSpheroid, "get_area", get_area, 1);
  rb_define_module_function(cSpheroid, "get_length", get_length, 1);

  spheroid_init(&s, EARTH_MAJOR_AXIS_RADIUS, EARTH_MINOR_AXIS_RADIUS);
}

