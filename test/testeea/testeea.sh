gcc -g -Wall -O0 ../math/eea.h eea.c -o eea.exe -lgmp
echo "running eea"
./eea.exe $1 $2
echo "running eea.py"
python3 eea.py $1 $2
