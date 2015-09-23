#include <ruby.h>
#include <liblwgeom.h>

double EARTH_MAJOR_AXIS_RADIUS = 6378137.0;
double EARTH_MINOR_AXIS_RADIUS = 6356752.314245179498;

LWGEOM *lwg;
SPHEROID s;

/// methods for calculating area
double get_area_for_lwg()
{
  double area = lwgeom_area_spheroid(lwg, &s);
  lwgeom_free(lwg);
  return area;
}

static VALUE get_area_from_wkb(VALUE self, VALUE geom_wkb)
{
  size_t wkb_size_a;
  lwg = lwgeom_from_wkb(RSTRING_PTR(geom_wkb), wkb_size_a, 0);
  double area = get_area_for_lwg();
  return rb_float_new(area);
}

static VALUE get_area_from_hexwkb(VALUE self, VALUE geom_wkb)
{
  lwg = lwgeom_from_hexwkb(RSTRING_PTR(geom_wkb), 0);
  double area = get_area_for_lwg();
  return rb_float_new(area);
}

static VALUE get_area_from_wkt(VALUE self, VALUE geom_wkt)
{
  lwg = lwgeom_from_wkt(RSTRING_PTR(geom_wkt), 0);
  double area = lwgeom_area_spheroid(lwg, &s);
  return rb_float_new(area);
}

// methods for calculating length
double get_length_for_lwg()
{
  double length = lwgeom_length_spheroid(lwg, &s);
  lwgeom_free(lwg);
  return length;
}

static VALUE get_length_from_wkt(VALUE self, VALUE geom_wkt)
{
  lwg = lwgeom_from_wkt(RSTRING_PTR(geom_wkt), 0);
  double length = get_length_for_lwg();
  return rb_float_new(length);
}

static VALUE get_length_from_wkb(VALUE self, VALUE geom_wkb)
{
  size_t wkb_size_a;
  lwg = lwgeom_from_wkb(RSTRING_PTR(geom_wkb), wkb_size_a, 0);
  double length = get_length_for_lwg();
  return rb_float_new(length);
}

static VALUE get_length_from_hexwkb(VALUE self, VALUE geom_hexwkb)
{
  size_t wkb_size_a;
  lwg = lwgeom_from_hexwkb(RSTRING_PTR(geom_hexwkb), 0);
  double length = get_length_for_lwg();
  return rb_float_new(length);
}

void Init_lwgeom()
{
  /* define module */
  VALUE mLwGeom = rb_define_module("LwGeom");

  /* define class */
  VALUE cSpheroid = rb_define_class_under(mLwGeom, "Spheroid", rb_cObject);

  rb_define_module_function(cSpheroid, "get_area_from_hexwkb",  get_area_from_hexwkb, 1);
  rb_define_module_function(cSpheroid, "get_area_from_wkb",     get_area_from_wkb,    1);
  rb_define_module_function(cSpheroid, "get_area_from_wkt",     get_area_from_wkt,    1);
  rb_define_module_function(cSpheroid, "get_length_from_wkt",   get_length_from_wkt,  1);
  rb_define_module_function(cSpheroid, "get_length_from_wkb",   get_length_from_wkb,  1);
  rb_define_module_function(cSpheroid, "get_length_from_hexwkb",get_length_from_hexwkb,1);

  spheroid_init(&s, EARTH_MAJOR_AXIS_RADIUS, EARTH_MINOR_AXIS_RADIUS);
}

