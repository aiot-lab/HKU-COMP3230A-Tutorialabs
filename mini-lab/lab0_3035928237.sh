#!/bin/bash

cat auth.log | grep Failed | grep -oE "[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+" >> suspicious_ips.txt;
