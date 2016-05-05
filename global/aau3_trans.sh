# Update folder
ssh 192.168.7.2 -l root rm -rf "~/aau3/*"
scp -r ~/workspace/AAU3/  root@192.168.7.2:~/aau3/

echo "Transfered the stuff from '~/workspace/AAU3/' to '~/aau3/'!"

# SSH into the beagle
ssh 192.168.7.2 -l root
