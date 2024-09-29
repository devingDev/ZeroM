
# Change this mygamemod to your own unique mod name
# It should be unique among all other existing/installed mods!
your_mod_name="mygamemod"
















# The rest under here you probably don't need to change.
echo "[BUILD]"


rm CMakeLists.txt
cp CMakeLists.txt.default CMakeLists.txt
sed -i "s/uniquemodnamehere/${your_mod_name}/g" CMakeLists.txt

rm exports.yml
cp exports.yml.default exports.yml
sed -i "s/uniquemodnamehere/${your_mod_name}/g" exports.yml




echo "Recreating build directory"
rm -rf build/
mkdir build
cd build
echo "cmake .."
cmake ..
if [ $? -ne 0 ]; then
  echo "cmake sample plugin failed."
  # remove to avoid confusion
  cd ..
  rm CMakeLists.txt
  rm exports.yml
  exit 1
fi
echo "make"
make
if [ $? -ne 0 ]; then
  echo "make sample plugin failed."
  # remove to avoid confusion
  cd ..
  rm CMakeLists.txt
  rm exports.yml
  exit 1
fi

# remove to avoid confusion
cd ..
rm CMakeLists.txt
rm exports.yml

echo "Build done."


cd build
lftp -u anonymous,anonymous ftp://192.168.178.32:1337 <<EOF

cd ux0:/zerom

put ./${your_mod_name}.suprx

bye

EOF

echo "Upload done!"
