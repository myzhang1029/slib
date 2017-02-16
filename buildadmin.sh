
cp ../slib/src/slib.h ./src
cp ../slib/build/slib.so ./build
cd build
gcc ../src/admin.c ./slib.so -o admin

