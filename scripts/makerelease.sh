

rm -rf tmp
mkdir -p tmp/zerom_release/ux0/zerom
mkdir -p tmp/zerom_release/ur0/tai

cp ../ZeroM-base/build/ZeroM.suprx ./tmp/zerom_release/ur0/tai/
cp ../ZeroM-base/sample/plugin/build/mygamemod.suprx ./tmp/zerom_release/ux0/zerom/

cp ../INSTALL.txt ./tmp/zerom_release/

cd ./tmp/

zip -r zerom_release.zip ./zerom_release

cd ..



#rm -rf tmp
