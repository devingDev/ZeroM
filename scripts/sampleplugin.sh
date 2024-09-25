

echo "[BUILD]"


echo "sample plugin"
cd "../ZeroM-base/sample/plugin"
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


echo "Build done."

lftp -u anonymous,anonymous ftp://192.168.178.32:1337 <<EOF

cd ux0:/zerom

put ./gamemod.suprx

bye

EOF

