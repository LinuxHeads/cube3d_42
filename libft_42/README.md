# Libft – A Custom C Standard Library

Libft is a personal implementation of over 50 standard C library functions along with additional utility functions that I found useful. This library serves as a foundational toolkit for C development, offering a deeper understanding of memory management, string manipulation, and data structures.

### 🔧 Features

* String manipulation functions (`ft_strlen`, `ft_strdup`, etc.)
* Memory management functions (`ft_memset`, `ft_calloc`, etc.)
* Character classification and conversion (`ft_isalpha`, `ft_tolower`, etc.)
* Integer and math-related utilities
* A complete linked list implementation (`t_list` and related functions)

All functions are compiled into a static archive called `libft.a`, which can be easily linked to any C project. You are free to edit the source code to fit your project needs and rebuild it.

---

## 📦 Installation & Usage

### 🧱 Cloning and Building

```bash
# Clone the repository into your project
$ git clone https://github.com/Abusalah0/libft_42.git

# Navigate to the library folder
$ cd libft_42

# Build the library
$ make
```

### 🔗 Linking Libft in Your Code

```bash
# Compile your program with libft (replace 'libft_location' with the actual path)
$ cc main.c -Llibft_location/ -lft
```

---

## ✏️ Modifying the Library

Feel free to modify any function as needed. After making your changes, simply run:

```bash
$ make re
```

This will rebuild the library with your modifications.

---

## 📚 Notes

* All code follows the [42 Norm](https://github.com/42School/norminette) coding standard.
* This project was developed as part of the [42 School](https://42.fr) curriculum.
