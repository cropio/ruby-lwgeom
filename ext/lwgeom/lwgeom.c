#include <ruby.h>
#include <liblwgeom.h>

double EARTH_MAJOR_AXIS_RADIUS = 6378137.0;
double EARTH_MINOR_AXIS_RADIUS = 6356752.314245179498;

LWGEOM *lwg;
SPHEROID s;

static VALUE cSpheroid;

double get_area_for_lwg()
{
  double area = lwgeom_area_spheroid(lwg, &s);
  lwgeom_free(lwg);
  return area;
}

static VALUE get_area_from_wkb(VALUE self, VALUE geom_wkb)
{
  int wkb_size_a;
  wkb_size_a = RSTRING_LEN(geom_wkb);
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
  int wkb_size_a;
  wkb_size_a = RSTRING_LEN(geom_wkb);
  lwg = lwgeom_from_wkb(RSTRING_PTR(geom_wkb), wkb_size_a, 0);
  double area = get_length_for_lwg();
  return rb_float_new(area);
}

static VALUE get_length_from_hexwkb(VALUE self, VALUE geom_hexwkb)
{
  size_t wkb_size_a;
  lwg = lwgeom_from_hexwkb(RSTRING_PTR(geom_hexwkb), 0);
  double length = get_length_for_lwg();
  return rb_float_new(length);
}

// trying to make polygon to be valid
// accept only string-polygon in wkb format
static VALUE make_valid(VALUE self, VALUE geom_wkb)
{
  VALUE result;
  LWGEOM *valid_lwg;
  
  int wkb_size_a;
  wkb_size_a = RSTRING_LEN(geom_wkb);
  
  lwg = lwgeom_from_wkb(RSTRING_PTR(geom_wkb), wkb_size_a, 0);
  
  valid_lwg = lwgeom_make_valid(lwg);
  //make multi
  valid_lwg = lwgeom_as_multi(valid_lwg);

  char *wkb_str = (char*)lwgeom_to_wkb(valid_lwg, WKB_HEX, NULL);
  

  return rb_str_new2(wkb_str);
}

void Init_lwgeom()
{
  /* define module */
  VALUE mLwGeom = rb_define_module("LwGeom");

  /* define class */
  cSpheroid = rb_define_class_under(mLwGeom, "Spheroid", rb_cObject);

  rb_define_module_function(cSpheroid, "get_area_from_hexwkb",  get_area_from_hexwkb, 1);
  rb_define_module_function(cSpheroid, "get_area_from_wkb",     get_area_from_wkb,    1);
  rb_define_module_function(cSpheroid, "get_area_from_wkt",     get_area_from_wkt,    1);
  rb_define_module_function(cSpheroid, "get_length_from_wkt",   get_length_from_wkt,  1);
  rb_define_module_function(cSpheroid, "get_length_from_wkb",   get_length_from_wkb,  1);
  rb_define_module_function(cSpheroid, "get_length_from_hexwkb",get_length_from_hexwkb,1);
  rb_define_module_function(cSpheroid, "make_valid", make_valid, 1);

  spheroid_init(&s, EARTH_MAJOR_AXIS_RADIUS, EARTH_MINOR_AXIS_RADIUS);
}

