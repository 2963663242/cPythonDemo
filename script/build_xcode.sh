WORKSPACE=$(dirname ${0})/..

mkdir $WORKSPACE/build

cmake -S $WORKSPACE -B $WORKSPACE/build -G Xcode