

lftp -u anonymous,anonymous ftp://192.168.178.32:1337 <<EOF

cd ux0:/zerom

put ../GameMod/build/mygamemod.suprx

bye

EOF

echo "Upload done!"

