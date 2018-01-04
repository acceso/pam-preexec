#!/bin/sh

# A password with a fixed string and the date

echo fixed`date | cut -d':' -f2`

