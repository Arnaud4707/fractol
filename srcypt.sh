#!/bin/bash

wget https://github.com/libsndfile/libsndfile/releases/download/1.2.2/libsndfile-1.2.2.tar.xz

tar -xvf libsndfile-1.2.2.tar.xz

cd libsndfile-1.2.2

./configure --prefix=$HOME/.local

make

make install

cd ..

rm libsndfile-1.2.2.tar.xz

wget http://software-dl.ti.com/processor-sdk-mirror/sources/fftw-3.3.4.tar.gz

tar xvf fftw-3.3.4.tar.gz

cd fftw-3.3.4

./configure --prefix=$HOME/.local --enable-shared

make

make install

cd ..

rm fftw-3.3.4.tar.gz

