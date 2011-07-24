#/bin/bash

declare -l bt=$1

export PROJECT_TOP_DIR=$(cd "$(dirname "$0")"; pwd)

export INSTALL_PREFIX=${HOME}/devel/linux-sdk/

pushd ${PROJECT_TOP_DIR}
case $bt in
	debug)
		mkdir Debug
		pushd Debug
		cmake  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} ..
		make
		make install
		make clean
		popd
		rm -rf Debug		
		;;
	*)
		mkdir Release
		pushd Release
		cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} ..
		make
		make install release
		make clean
		popd
		rm -rf Release
		;;
esac
popd

