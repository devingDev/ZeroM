

rm -rf build
mkdir build
cd build

cmake ..
make

cd ../GameMod/
sh build_step3.sh
