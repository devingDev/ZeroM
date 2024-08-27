
echo "Steps: [BUILD] -> [FTP UPLOAD] -> netcat listen to printf"


sh zerom_build.sh
if [ $? -ne 0 ]; then
  echo "Build failed. Stopping script."
  exit 1
fi

sh upload_zerom.sh && sh netcat_listen.sh

echo "End of run_zerom_all.sh";
