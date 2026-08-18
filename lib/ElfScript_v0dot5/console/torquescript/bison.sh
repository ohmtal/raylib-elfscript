#!/bin/sh
# bison -d -v -p CMD -o CMDgram.cpp CMDgram.y
flex --nounput -o CMDscan.cpp -P CMD CMDscan.l

bison -d -v -p CMD -o CMDgram.cpp -HCMDgram.h CMDgram.y

