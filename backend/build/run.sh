#!/bin/bash

echo "Compiling binaries..."
cd ../auth && go build -o auth && cd ../kscore && go build -o kscore
