#!/usr/bin/expect -f

set prompt "#"
set address "D2:B5:F2:A5:69:47"

#send_user "\nRestarting bluetooth service.\r"
#spawn sudo service bluetooth restart

spawn sudo bluetoothctl
expect -re $prompt
send "remove $address\r"
sleep 1
expect -re $prompt
send "scan on\r"
sleep 8
send "pair $address\r"
sleep 4
send_user "Connect\n\r"
send "connect $address\r"
sleep 1
send "quit\r"
expect eof