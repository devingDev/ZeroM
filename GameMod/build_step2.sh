echo "Recreating build directory"
rm -rf build/
mkdir build
cd build
echo "cmake .."
cmake ..
if [ $? -ne 0 ]; then
  echo "cmake sample plugin failed."
  exit 1
fi
echo "make"
make
if [ $? -ne 0 ]; then
  echo "make sample plugin failed."
  exit 1
fi

