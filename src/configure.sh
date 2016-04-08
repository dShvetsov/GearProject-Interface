qmake ./console/consoleApplication.pro -o ../bin/console/Makefile -spec linux-g++
qmake ./gui/GuiRepairMechanism.pro -o ../bin/Gui/Makefile -spec linux-g++
cd ../bin/console
make
cd ../Gui
make
cd ../
mkdir plugins -p
cd ../src
g++ ./plugins/Gaussian.cpp -o ../bin/plugins/Gaussian.o -I include/ -I externals/EasyBMP/include/ -c -fPIC -std=c++0x
g++ ./plugins/Median.cpp -o ../bin/plugins/Median.o -I include/ -I externals/EasyBMP/include/ -c -fPIC -std=c++0x
g++ ./plugins/BoxFilter.cpp -o ../bin/plugins/BoxFilter.o -I include/ -I externals/EasyBMP/include/ -c -fPIC -std=c++0x 
g++ ./plugins/inverse.cpp -o ../bin/plugins/inverse.o -I include/ -I externals/EasyBMP/include/ -c -fPIC -std=c++0x 
cd ../bin/plugins
g++ -shared -o Gaussian.so Gaussian.o
g++ -shared -o Median.so Median.o
g++ -shared -o BoxFilter.so BoxFilter.o
g++ -shared -o inverse.so inverse.o
