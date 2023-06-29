#!/bin/bash

BINARYNAME=astral
IMAGENAME=web-${BINARYNAME}-compile

docker build -f compile.Dockerfile -t $IMAGENAME .

id=$(docker create $IMAGENAME)
docker cp $id:/app/target/release/$BINARYNAME - > dist/$BINARYNAME.tar
docker rm -v $id

cd dist
tar -xvf $BINARYNAME.tar
rm $BINARYNAME.tar
cd ..