mkdir arm_jsoncpp
cp include/ arm_jsoncpp/ -r
cp src/lib_json/* arm_jsoncpp/
cd arm_jsoncpp/
===========================================================================
C++编译静态库:

arm-arago-linux-gnueabi-g++ -c *.cpp -I./include -fPIC
ar cr libjsoncpp.a *.o


C++编译动态库:

arm-arago-linux-gnueabi-g++ -shared -fPIC *.cpp -I./include -o libjsoncpp.so
---------------------------------------------------------------------------

