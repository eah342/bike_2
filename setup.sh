#!/bin/bash

cd /sys/class/pwm/pwmchip0
echo 0 > export
cd ../pwm-0\:0

sudo sh -c "echo normal > polarity"
