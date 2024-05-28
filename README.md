# USAssembler 1.0 Debian Installation Guide
This is a project for the Caltech 150 class. This assembler is designed for the PIC16 family of chips.
This guide explains how to install the `USAssembler_1.0.deb` package on your computer.

## Step 1: Transfer the Package to Your Computer

First, transfer the `USAssembler_1.0.deb` file to your computer. Download it from this github repository.

You can use any of the following methods to put the file onto your computer:

- **USB Drive**: Copy the file to a USB drive and then to your computer.
- **Email**: Attach the file to an email and download it on your computer.
- **Cloud Storage**: Upload the file to a cloud storage service (e.g., Google Drive, Dropbox) and download it on your computer.
- **Secure Copy (scp)**: Transfer the file over a network using `scp`

## Step 2: Install the Package

1. **Open a terminal on your computer.**

2. **Navigate to the directory containing the `.deb` file.** For example, if the file is in the `Downloads` directory:
    ```bash
    cd ~/Downloads
    ```

3. **Install the package using `dpkg`:**
    ```bash
    sudo dpkg -i USAssembler_1.0.deb
    ```

    If dpkg is not installed, you can install it using apt-get:
    ```bash
    sudo apt-get update
    sudo apt-get install dpkg
    ```

4. **Fix any dependency issues:**
    ```bash
    sudo apt-get install -f
    ```

## Step 3: Run the Executables

After installation, you can run the executables `menu` and `terminal` from the terminal:

```bash
menu
```

or

```bash
terminal
```

### Using the Full Path

If the executables do not run, you can use the full path:

```bash
/usr/local/bin/menu
/usr/local/bin/terminal
```

## Troubleshooting

### Missing Dependencies: 

If there are any missing dependencies, the `sudo apt-get install -f` command will attempt to fix them.

### Executable Not Found: 

Ensure that /usr/local/bin is in your PATH. You can check this by running:
```bash
echo $PATH | tr ':' '\n'
```

If /usr/local/bin is not listed, you can add it by adding the following line to your ~/.bashrc or ~/.zshrc file:
```bash
export PATH=$PATH:/usr/local/bin
```

Then, reload your shell configuration:

```bash
source ~/.bashrc  # For Bash shell
```

or

```bash
source ~/.zshrc  # For Zsh shell
```

***If you encounter any issues or have any questions, please contact the package maintainer at `gore@caltech.edu`.***
