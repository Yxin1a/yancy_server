#!/bin/bash

CLEANDESK_PATH=$(dirname "$(realpath "$0")")
echo $CLEANDESK_PATH

cd $CLEANDESK_PATH/bin

sudo ./server -s