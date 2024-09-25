

echo "[BUILD]"

echo "vita-rss-libdl"
cd "../vita-rss-libdl"
rm -rf build/
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
if [ $? -ne 0 ]; then
  echo "cmake vita-rss-libdl failed."
  exit 1
fi
make && make install
if [ $? -ne 0 ]; then
  echo "make vita-rss-libdl failed."
  exit 1
fi


echo "ZeroM-base"
cd "../../ZeroM-base"
echo "Recreating build directory"
rm -rf build/
mkdir build
cd build
echo "cmake .."
cmake ..
if [ $? -ne 0 ]; then
  echo "cmake ZeroM-base failed."
  exit 1
fi
echo "make"
make
if [ $? -ne 0 ]; then
  echo "make failed."
  exit 1
fi


echo "Build done."

