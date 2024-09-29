

sh build_pluginreload.sh && sh build_zerom.sh && sh build_gamemod.sh


rm -rf tmp
mkdir -p tmp/zerom_release/ux0/zerom
mkdir -p tmp/zerom_release/ur0/tai

cp ../ZeroM-base/build/ZeroM.suprx ./tmp/zerom_release/ur0/tai/
cp ../GameMod/build/mygamemod.suprx ./tmp/zerom_release/ux0/zerom/
cp ../PluginReload/build/PluginReload.suprx ./tmp/zerom_release/ur0/tai/

cp ../INSTALL.txt ./tmp/zerom_release/

cd ./tmp/

zip -r zerom_release.zip ./zerom_release

cd ..



#rm -rf tmp
