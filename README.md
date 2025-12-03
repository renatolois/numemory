# numemory

> An old project of mine from back when I was learning C, C++, and ncurses, so the code might be a little messy

**numemory** is an application designed to improve your memory and cognitive skills, helping you train to memorize numbers, dates, addresses, names, and other types of information. For now, though, it only works with simple number sequences, and doesn’t yet cover everything described in its goals. It's especially useful for improving forensic memory skills, enabling you to increase your ability to recall data quickly and accurately.

## How to Use

### Requirements
- Unix-like operating systems (Linux, macOS, etc.)
- `ncurses` library installed on your system

### Compiling the Code

1. Clone the repository:

   ```bash
   git clone https://github.com/RLois4/numemory.git
   cd numemory
   ```

2. Compile the code:

   ```bash
   make
   ```

3. Run the program:

   ```bash
   ./numemory
   ```

### Command-Line Arguments

- `-t <time>`: Sets the time (in seconds) that the numbers stay on the screen. The default is **3 seconds**.
- `-q <quantity>`: Sets the number of digits to be memorized. The value must be between **1 and 8** (default is **7**).

### Example Usage

```bash
./numemory -t 5 -q 4
```

This command runs numemory with a display time of **5 seconds** and a **4-digit** number to memorize.

## Contributing

If you'd like to contribute to numemory, feel free to fork the repository and submit a pull request. Contributions are welcome!

## License

numemory is open-source software released under the MIT License. See the LICENSE file for more details.
