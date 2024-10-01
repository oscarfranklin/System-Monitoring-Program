NAME: Oscar Franklin 
DATE: 4/24/2024
PROJECT NAME: C Program with Bash Script Modification

#!/bin/bash

REFRESH_RATE=$1

echo "System Resource Monitor"
echo "-----------------------"
echo "CPU Usage:"
top -bn$REFRESH_RATE | grep "Cpu(s)"
echo "Memory Usage:"
free -m | grep "Mem"
echo "Disk Usage:"
df -h / | grep -E '^Filesystem|^/'
