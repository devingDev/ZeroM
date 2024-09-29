
# Change this mygamemod to your own unique mod name
# It should be unique among all other existing/installed mods!
your_mod_name="mygamemod"
















# The rest under here you probably don't need to change.
echo "[BUILD]"


rm CMakeLists.txt
cp CMakeLists.txt.default CMakeLists.txt
sed -i "s/uniquemodnamehere/${your_mod_name}/g" CMakeLists.txt

rm gamemodexports.yml
cp gamemodexports.yml.default gamemodexports.yml
sed -i "s/uniquemodnamehere/${your_mod_name}/g" gamemodexports.yml





echo "Build done."

