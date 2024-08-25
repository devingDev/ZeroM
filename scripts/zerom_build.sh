

echo "[BUILD]"
echo "ZeroM-base"

cd "../ZeroM-base"

echo "Recreating build directory"
rm -rf build/
mkdir build
cd build
echo "cmake .."
cmake ..
echo "make"
make


echo "Build done."

