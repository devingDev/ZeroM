

echo "[BUILD]"
echo "PluginReload"

cd "../PluginReload"

echo "Recreating build directory"
rm -rf build/
mkdir build
cd build
echo "cmake .."
cmake ..
echo "make"
make


echo "Build done."

