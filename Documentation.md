# Documentation

## Style

Code style is compatible with Google C++ Style Guide. Cpplint and clang-format was used to ensure compatibility:

```bash
clang-format -i sources/*
```

Memory leak check:

```bash
valgrind --leak-check=full ./main <options>
```
