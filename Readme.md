# fredPresser
## a text compressor written by an idiot.

### build:

can be build using make
notice, this code is *only tested on linux*
so honestly i don't think it would even work on windows.

```{bash}

git clone -||-
cd -||-
make

```

### installation
put the "fredPresser" binary output from the ´´´make´´´ command within any folder within you $PATH


### usage:

´´´{bash}
# To compress a file
fredPresser -C inputFile.txt compressedFile.fred
# To uncompress it again
fredPresser -U compressedFile.fred outputFile.txt
´´´

# TODO

- [ ] put code in some neat classes.
- [ ] write more efficient sorting functions.
- [ ] world domination.

