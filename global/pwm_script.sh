echo am33xx_pwm > /sys/devices/bone_capemgr.9/slots
echo bone_pwm_P8_13 > /sys/devices/bone_capemgr.9/slots
echo bone_pwm_P9_14 > /sys/devices/bone_capemgr.9/slots
echo bone_pwm_P9_16 > /sys/devices/bone_capemgr.9/slots
sleep 0.5
echo 0 > /sys/devices/ocp.3/pwm_test_P8_13.15/run
echo 0 > /sys/devices/ocp.3/pwm_test_P9_14.16/run
echo 0 > /sys/devices/ocp.3/pwm_test_P9_16.17/run

echo 2 > /sys/class/gpio/export
echo 113 > /sys/class/gpio/export
echo 114 > /sys/class/gpio/export
echo 60 > /sys/class/gpio/export
echo 15 > /sys/class/gpio/export

echo cape-bone-iio > /sys/devices/bone_capemgr.*/slots
