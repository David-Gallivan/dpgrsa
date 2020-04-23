#JMJ

# Runs the keysetup, encryption, and decryption
# Stores the results

./bin/keysetup  # Default seed will be used
./bin/encrypt data/message.txt public_key.txt
./bin/decrypt ciphertext.txt public_key.txt private_key.txt
mv *.txt results/  
cp data/message.txt results/

