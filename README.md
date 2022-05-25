# xanadu-posix

*A cross-platform C language wrapper Library*



## Explain
This project is mainly used to resolve the differences in function names and types under different systems.
Solve some functions that are not provided due to platform differences, and add easy-to-call versions of some functions.
This project library is the basis of the pure C language of the X-Series.




## Note
If you want to commit any changes, write the code in the following format.

set encoding=utf-8 with BOM

set tabstop=8

set shiftwidth=8




## Comment format

```shell
/// Function description
/// \param _Value : Parameter explanation
/// \return : Return value description
```



## Installation

### Linux

First install all required dependencies and build tools:
```shell
sudo apt install git
sudo apt install autoconf
sudo apt install automake
sudo apt install libtool-bin
sudo apt install cmake
```

Then clone the actual project repository:
```shell
git clone https://github.com/libxanadu/xanadu-posix.git
svn checkout https://github.com/libxanadu/xanadu-posix/trunk
cd xanadu-posix
```

Now you can build and install it:
```shell
cmake .
make
sudo make install
```



## License

This library is licensed under the [GNU Lesser General Public License v2.1](https://www.gnu.org/licenses/lgpl-2.1.en.html),
also included in the repository in the `LICENSE` file.
