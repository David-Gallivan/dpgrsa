#JMJ

# Runs the keysetup, encryption, and decryption
# Stores the results

./bin/keysetup  $1 # Default seed will be used unless specified
./bin/encrypt data/message.txt public_key.txt
./bin/decrypt ciphertext.txt public_key.txt private_key.txt
mv *.txt results/  
cp data/message.txt results/

