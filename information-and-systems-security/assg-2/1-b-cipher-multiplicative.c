#include <stdio.h>  // printf, scanf
#include <stdlib.h> // abs

#include "utils.h"
#define MOD 26

/*
 * Cipher multiplicative encrypts (in place) all characters of a string w.r.t a key.
 *
 * s: the string
 * key: cipher key
 */
void encrypt(char *s, int key)
{
    printf("    for key = %d\n\n", key);
    for (int i = 0; s[i] != '\0'; i++)
    {
        char enc_char = 'A' + mod_26((s[i] - 'A') * key);
        printf(
            "    %c (%2d)  ->  [(%2d × %d) mod %d] = [%2d mod %d]  %c (%2d)\n",
            s[i],
            s[i] - 'A',
            s[i] - 'A',
            key,
            MOD,
            (s[i] - 'A') * key,
            MOD,
            enc_char,
            enc_char - 'A');
        s[i] = enc_char;
    }
}

/*
 * Cipher multiplicative decrypts (in place) all characters of a string w.r.t a key.
 *
 * s: the string
 * key: cipher key
 */
void decrypt(char *s, int key)
{
    int key_inv = mod_26_mul_inv(key);
    printf("    for key = %d\n    key multiplicative inverse (mod %d) = %d\n\n", key, MOD, key_inv);
    for (int i = 0; s[i] != '\0'; i++)
    {
        char dec_char = 'A' + mod_26((s[i] - 'A') * key_inv);
        printf(
            "    %c (%2d)  ->  [(%2d × %d) mod %d] = [%3d mod %d]  %c (%2d)\n",
            s[i],
            s[i] - 'A',
            s[i] - 'A',
            key_inv,
            MOD,
            (s[i] - 'A') * key_inv,
            MOD,
            dec_char,
            dec_char - 'A');
        s[i] = dec_char;
    }
}

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    char s[256];
    int key;
    printf("\nImplementation of Multiplicative Cipher\n--------\n");
    int repeat;
    do
    {
        printf("Enter a string (A-Z) to encrypt: ");
        scanf("%s", s);
        repeat = 0;
        for (int i = 0; s[i] != '\0'; i++)
        {
            if (s[i] < 'A' || s[i] > 'Z')
            {
                printf("  Invalid string, retry\n");
                repeat = 1;
                break;
            }
        }
    } while (repeat);
    do
    {
        printf("Enter cipher multiplicative key: ");
        scanf("%d", &key);
        repeat = 0;
        if (mod_26_mul_inv(key) == -1)
        {
            printf("  Invalid key, retry\n");
            repeat = 1;
        }
    } while (repeat);
    printf("\nEncryption:\n");
    encrypt(s, key);
    printf("\nEncrypted string: %s\n", s);
    printf("\nDecryption:\n");
    decrypt(s, key);
    printf("\nDecrypted string: %s\n", s);
    printf("\n");
}
