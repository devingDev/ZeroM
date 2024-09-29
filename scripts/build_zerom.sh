


echo "[BUILD]"



echo "ZeroM-base"
cd "../ZeroM-base"
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

