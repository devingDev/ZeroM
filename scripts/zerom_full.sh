
echo "Steps: 1. [BUILD] -> 2. [FTP UPLOAD]"


sh build_zerom.sh
if [ $? -ne 0 ]; then
  echo "Build failed. Stopping script."
  exit 1
fi

sh upload_zerom.sh # && sh netcat_listen.sh # switched to psmusblog

echo "End of zerom_full.sh";
