# opus-php

Opus bindings for PHP.

## Requirements

- Rust.
- PHP 8.0.
- Linux or Darwin based operating system.
- [ext-php-rs](https://github.com/davidcole1340/ext-php-rs#requirements) requirements.
- [libopus 1.3.1 or later](https://opus-codec.org/downloads/).

## Installation

```sh
$ git clone git@github.com:davidcole1340/opus-php.git
$ cd opus-php
$ cargo build --release
```

This will produce a PHP extension file at `target/release/libopusphp.{so|dylib}`.
You can then install this like any other PHP extension by adding it to your `php.ini` file.

## License

The contents of this repository are licensed under the MIT license:

```
MIT License

Copyright (c) 2021 David Cole

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```