# bgen

[![Travis](https://img.shields.io/travis/limix/bgen.svg?style=flat-square)](https://travis-ci.org/limix/bgen)
[![Documentation Status](https://readthedocs.org/projects/bgen/badge/?style=flat-square&version=latest)](https://bgen.readthedocs.io/)

A [BGEN file format](http://www.well.ox.ac.uk/~gav/bgen_format/) reader.

It fully supports all the BGEN format specifications: 1.1, 1.2, and 1.3.

## Requirements

It makes use of the [Zstandard](http://facebook.github.io/zstd/) library.
You don't need to install it by yourself if you choose to install bgen
via [conda](http://conda.pydata.org/docs/index.html) but you do need it
installed before-hand if you choose to build bgen library by yourself.

## Install

You can install it via
[conda](http://conda.pydata.org/docs/index.html)

```bash
conda install -c conda-forge bgen
```

or by building it

```bash
wget https://github.com/limix/bgen/archive/0.1.9.tar.gz
tar xzf 0.1.9.tar.gz
cd bgen-0.1.9
mkdir build
cd build
cmake ..
make
make test
sudo make install
```

## Documentation

Refer to [documentation](https://bgen.readthedocs.io/) for usage and API
description.

## Authors

* **Danilo Horta** - [https://github.com/horta](https://github.com/horta)

## License

This project is licensed under the MIT License - see the
[LICENSE](LICENSE) file for details
