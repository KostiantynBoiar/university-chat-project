#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//  Function to check if a number is prime
int is_prime(int n) {
    if (n <= 1) {
        return 0;
    }
    if (n <= 3) {
        return 1;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return 0;
    }
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

// Function to generate a random prime number
int generate_prime() {
    int prime;
    srand(time(NULL));
    while (1) {
        prime = rand() % 100 + 50;  // We generate a random number from 50 to 149
        if (is_prime(prime)) {
            return prime;
        }
    }
}

// Function to calculate the greatest common divisor (gcd)
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Function to generate public and private RSA keys
void generate_rsa_keys(int* public_key, int* private_key) {
    int p, q, n, phi_n, e, d;

    // Generation of prime numbers p and q
    p = generate_prime();
    q = generate_prime();

    // Calculation of the value of n and the Euler function phi(n)
    n = p * q;
    phi_n = (p - 1) * (q - 1);

    // Public key selection e
    for (e = 2; e < phi_n; e++) {
        if (gcd(e, phi_n) == 1) {
            break;
        }
    }

    // Private key calculation d
    d = 1;
    while (((d * e) % phi_n) != 1) {
        d++;
    }

    *public_key = e;
    *private_key = d;
}

// Function to encrypt data using RSA public key
void rsa_encrypt(int public_key, const unsigned char* plain_text, size_t plain_text_length, unsigned char** encrypted_text, size_t* encrypted_text_length) {
    int n = 127;  // The value of n, the modulus of the public key
    int e = public_key;  // The value of e, the public key index

    *encrypted_text = (unsigned char*)malloc(plain_text_length * sizeof(unsigned char));
    if (*encrypted_text == NULL) {
        printf("Error allocating memory for encrypted text.\n");
        return;
    }

    *encrypted_text_length = 0;
    for (size_t i = 0; i < plain_text_length; i++) {
        // Encrypt each flat text character with the RSA public key
        unsigned char encrypted_char = (unsigned char)fmod(pow(plain_text[i], e), n);
        (*encrypted_text)[i] = encrypted_char;
        (*encrypted_text_length)++;
    }
}

// Function to decrypt data using RSA private key
void rsa_decrypt(int private_key, const unsigned char* encrypted_text, size_t encrypted_text_length, unsigned char** decrypted_text, size_t* decrypted_text_length) {
    int n = 127;  // The value of n, the modulus of the private key
    int d = private_key;  // The value of n, the modulus of the private key
    *decrypted_text = (unsigned char*)malloc(encrypted_text_length * sizeof(unsigned char));
    if (*decrypted_text == NULL) {
        printf("Error allocating memory for decrypted text.\n");
        return;
    }

    *decrypted_text_length = 0;
    for (size_t i = 0; i < encrypted_text_length; i++) {
        // Decrypt each character of the ciphertext using the RSA private key
        unsigned char decrypted_char = (unsigned char)fmod(pow(encrypted_text[i], d), n);
        (*decrypted_text)[i] = decrypted_char;
        (*decrypted_text_length)++;
    }
}

int main() {
    // Example of using key generation, encryption and decryption functions
    int public_key, private_key;
    const unsigned char* plain_text = (unsigned char*)"Hello, RSA!";
    size_t plain_text_length = strlen((const char*)plain_text);
    unsigned char* encrypted_text;
    size_t encrypted_text_length;
    unsigned char* decrypted_text;
    size_t decrypted_text_length;

    // Key generation
    generate_rsa_keys(&public_key, &private_key);

    // Encryption
    rsa_encrypt(public_key, plain_text, plain_text_length, &encrypted_text, &encrypted_text_length);

    // Decryption
    rsa_decrypt(private_key, encrypted_text, encrypted_text_length, &decrypted_text, &decrypted_text_length);

    // Output results
    printf("Plain Text: %s\n", plain_text);
    printf("Encrypted Text: ");
    for (size_t i = 0; i < encrypted_text_length; i++) {
        printf("%02x", encrypted_text[i]);
    }
    printf("\n");
    printf("Decrypted Text: ");
    for (size_t i = 0; i < decrypted_text_length; i++) {
        printf("%c", decrypted_text[i]);
    }
    printf("\n");

    // Free memory
    free(encrypted_text);
    free(decrypted_text);

    return 0;
}
