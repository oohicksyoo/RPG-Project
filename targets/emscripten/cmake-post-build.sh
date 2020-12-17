#!/bin/bash

# Copy our 'template.html' into the output folder as 'index.html'.
cp template.html out/index.html

# Navigate into the output folder then start a simple server and open it.
pushd out
	MYPORT=20000; 
	kill -9 `ps -ef |grep SimpleHTTPServer |grep $MYPORT |awk '{print $2}'`

	python -m SimpleHTTPServer 20000 & open http://localhost:20000
popd