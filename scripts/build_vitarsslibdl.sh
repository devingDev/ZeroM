
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
