
echo "[FTP UPLOAD]"

echo "Starting FTP connection."

lftp -u anonymous,anonymous ftp://192.168.178.32:1337 <<EOF

cd ur0:/tai

put ../PluginReload/build/PluginReload.suprx

bye

EOF

echo "FTP Upload done."

