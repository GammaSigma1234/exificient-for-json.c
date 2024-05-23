# Exificient For JSON - Experiments by GS

Attempt to use this library to decode an existing EXI file into a JSON string or JSON file.

# `test_GS/simple_example.c`

This example is an adaptation from the [Demo Program](https://github.com/GammaSigma1234/exificient-for-json.c#demo-program) in the official repository.

- The program reads string literal `JSON_STRING_IN` which is the "serialised" (copy-pasted and adapted by hand) version of JSON file `EXI_sample_2.json`.
- The string is encoded to an `uint8_t` buffer with `encodeEXIforJSON` (it's not the same as the EXI stream used in the OpenV2G example, or in the `V2G_Wrapper` class in ZeroMQ_experiments).
- The program prints the buffer to the terminal: the raw bytes are different from `EXI_sample_2.exi`, which demonstrates that `buffer` does not correspond to `EXI_sample_2.exi` (this can be seen by opening `EXI_sample_2.exi` with a hex editor and comparing it to the print to the terminal).
- The buffer is then encoded / serialised back to a JSON string.
- The JSON string is printed to the terminal. Apart from the whitespace characters, the contents are the same as the original string literal.

# `test_GS/test.c`

This test is inspired from the previous one, with a difference: we do not want to provide a string literal to the CoDec, but an already existing EXI file instead. We want the EXI to be converted into a serialised JSON string.

- Call the program passing the path to an EXI file as an argument.
- The EXI file is opened in binary mode.
- The raw contents of the EXI file are printed to the terminal.
- The raw contents of the EXI file are read into an `uint8_t buffer`.
- The raw contents of the EXI file are printed again to the terminal, but reading from `buffer` this time, to verify the correctness of `buffer`.
- An attempt is made to convert / serialise the raw contents of the EXI file (i.e., `buffer`) to a JSON string by calling `decodeEXIforJSON` and passing `buffer` as an argument.
- The new JSON string is printed to the terminal, but it is does not coincide with the original JSON file.

As said before, the content of the original EXI file and the data buffer created by `decodeEXIforJSON` are not identical. In `simple_example`, creating a string literal from `EXI_sample_2.json` and passing it as an argument to `encodeEXIforJSON`, yields the following binary sequence, stored in `uint8_t buffer`

```
80 40 03 55 8C 91 D7 D3 59 5C DC D8 59 D9 40 04
24 32 B0 B2 32 B9 20 5A 9B 2B 9B 9B 4B 7B 72 4A
20 92 21 A1 C1 8A 31 9A 29 B2 0A 31 C2 11 91 91
BA 08 00 E4 E6 F7 46 96 66 96 36 17 46 96 F6 E4
0B 46 61 75 6C 74 43 6F 64 65 0E 50 61 72 73 69
6E 67 45 72 72 6F 72 40 A4 66 17 56 C7 44 D7 36
74 25 76 56 C6 46 96 E6 74 46 57 46 56 37 46 96
F6 E5 26 57 12 72 06 E6 F7 42 06 16 36 36 57 07
46 56 42 06 96 E2 07 37 46 17 46 52 03 C6 97 36
F3 13 53 13 13 82 E7 36 56 36 32 E7 37 46 17 42
E2 EF C0 03 21 37 B2 3C 80 15 57 65 6C 64 69 6E
67 44 65 74 65 63 74 69 6F 6E 52 65 73 40 E5 26
57 37 06 F6 E7 36 54 36 F6 46 51 64 64 14 94 C4
54 45 F5 36 57 17 56 56 E6 36 54 57 27 26 F7 20
01 E8 88 6B E8 AA CA 68 AA 6E 8C 2E 8E AE 6C 2C
9C DE E8 D2 CC D2 C6 C2 E8 D2 DE DC 9A C2 F0 88
CA D8 C2 F2 00 00 20 92 2A B2 9A 2A 73 7B A3 4B
33 4B 1B 0B A3 4B 7B 70 32 73 7B 73 2A 0A A2 AB
29 A2 A4 B9 B7 B6 30 BA 34 B7 B7 29 BA 30 BA 3A
B9 83 AB 30 B6 34 B2 20 82 2A B2 9A 2A 9B A3 0B
A3 AB 9A 1B 7B 23 28 62 2A B2 9A 2A FA 93 2B 0B
23 CF 00 28 8A AC A6 8A A0 E4 CA E6 CA DC E8 AC
DE D8 E8 C2 CE CA C0 EA CC 2D 8E AC AE 60 10 03
06 26 BA B6 3A 34 B8 36 34 B2 B9 00 00 08 0C AA
DC D2 E8 06 AD FF FC
```

However, the actual content of `EXI_sample_2.exi` (which is the EXI version of `EXI_sample_2.json`) is this:

```
80 98 02 35 20 7C F9 AB E2 C8 9E 80 02 12 BB 2B
63 23 4B 73 3A 23 2B A3 2B 1B A3 4B 7B 72 93 2B
89 39 03 73 7B A1 03 0B 1B 1B 2B 83 A3 2B 21 03
4B 71 03 9B A3 0B A3 29 01 E3 4B 9B 79 89 A9 89
89 C1 73 9B 2B 1B 19 73 9B A3 0B A1 71 70 A2 0A
00 00 02 04 0C 40 E6 01 00
```

Apart from the first byte, the two representations are completely different, which demonstrates that `encodeEXIforJSON` creates a data buffer containing data which are not comparable to the original EXI file.

The conversion to JSON string does not fail, but it gives an incorrect result. Maybe this is because the EXI file is read as raw bytes instead of using the `readBytesFromFile` from OpenV2G, which creates an `uint8_t` buffer? Or maybe because Exificient For JSON is not intended to convert from an actual EXI file?