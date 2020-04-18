gcc -g -Wall -O0 ../math/eea.h eea.c -o eea -lgmp
echo "running eea"
./eea $1 $2
echo "running eea.py"
python3 eea.py $1 $2
