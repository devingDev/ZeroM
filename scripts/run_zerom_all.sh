
echo "Steps: [BUILD] -> [FTP UPLOAD] -> netcat listen to printf"

sh zerom_build.sh && sh upload_zerom.sh && nc -kl 9999

echo "End of run_zerom_all.sh";
