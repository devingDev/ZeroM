
echo "[FTP UPLOAD]"

echo "Starting FTP connection."

lftp -u anonymous,anonymous ftp://192.168.178.32:1337 <<EOF

cd ur0:/tai

put ../ZeroM-base/build/ZeroM.suprx

bye

EOF

echo "FTP Upload done."

