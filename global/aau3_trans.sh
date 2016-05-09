# Update folder
# ssh 192.168.7.2 -l root rm -rf "~/aau3/*"
cp ./src/main ./
echo "Moved main program to ./"

scp -r ./*  root@192.168.7.2:~/aau3/
echo "Transfered the stuff from '~/workspace/AAU3/' to '~/aau3/'!"

# SSH into the beagle
# ssh 192.168.7.2 -l root
