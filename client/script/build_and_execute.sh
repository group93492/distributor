#!/bin/bash
qmake ../distributor-client.pro
make -j3
./distributor-client
