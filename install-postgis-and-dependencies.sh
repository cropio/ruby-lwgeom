# libxml2
wget ftp://xmlsoft.org/libxml2/libxml2-2.9.2.tar.gz
tar xfz libxml2-2.9.2.tar.gz
cd libxml2-2.9.2
./configure --without-python --with-zlib=/usr/local --with-lzma=/usr/local
make
sudo make install-strip
cd ..

# geos
wget http://download.osgeo.org/geos/geos-3.5.0.tar.bz2
tar xvf geos-3.5.0.tar.bz2
cd geos-3.5.0
./configure
make
sudo make install-strip
cd ..

# proj4
wget http://download.osgeo.org/proj/proj-4.9.2.tar.gz
tar xfz proj-4.9.2.tar.gz
cd proj-4.9.2
./configure
make
sudo make install-strip
cd ..

# postgis
wget http://download.osgeo.org/postgis/source/postgis-2.2.0.tar.gz
tar xfz postgis-2.2.0.tar.gz
cd postgis-2.2.0
./configure --without-gui --without-raster --silent --without-pgconfig
sudo make --silent
sudo make install --silent
sudo ldconfig