# README

## Project Title: PA01 C Program

### Description

This project contains a C program designed for encrypting a plaintext file using the Hill cipher algorithm. The code is structured to follow standard C programming practices and implements efficient array and string handling.

### Project Structure

- **pa01.c**: The main source code file containing the C program. It includes functions for reading input files, parsing key matrices, processing plaintext, and performing Hill cipher encryption.
- **README.md**: Documentation for understanding the structure, functionality, and usage of the project.

### Key Features

- **Modular Code**: The program is divided into functions for better readability and maintainability.
- **Error Handling**: Includes checks to handle potential issues during execution.
- **Comments**: Thoroughly commented code for easier understanding.
- **Encryption of Large Text**: Capable of handling plaintext input up to a maximum of 100,000 characters.

### Requirements

- **Compiler**: Ensure that you have `gcc` or any compatible C compiler installed.
- **Libraries**: Standard C libraries are used. Additional libraries, if any, will be mentioned in the code.

### Compilation and Execution

1. **Compilation**:
   ```bash
   gcc -o pa01 pa01.c
   ```
2. **Execution**:
   ```bash
   ./pa01 kX.txt pX.txt
   ```
   - **kX.txt**: A key text file containing the encryption matrix.
   - **pX.txt**: A plaintext file to be encrypted.

### Usage

To use the program, provide two input files as command-line arguments:

- ``: The key text file containing the encryption matrix.
- ``: The plaintext file that will be encrypted.

The program reads these files, encrypts the plaintext using the Hill cipher method, and outputs the encrypted text to the console or a specified output location.

### Potential Enhancements

- **Improved User Interface**: Adding a user-friendly interface for better interaction.
- **Additional Features**: Future enhancements could include support for different data formats or decryption capabilities.

### Contact

For any inquiries or suggestions regarding the project, please reach out via GitHub or through the contact information provided in this repository.

---

**Note**: Remember to update this README as changes are made to the project or new features are added.

