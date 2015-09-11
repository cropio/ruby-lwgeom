#!/usr/bin/env ruby
require 'mkmf'

# checking is postgis/lwgeom installed
if have_library("lwgeom")
  create_header
  create_makefile 'lwgeom'
else
  puts "Oops..."
end

