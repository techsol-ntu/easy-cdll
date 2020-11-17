# easy-cdll

Boost the transaction formatting and development between python and c languages

## Requirements

* Linux, maxOS
* Python 3.8
* pip3

## Installation

```bash
pip3 install easy-cdll
python3
```

## Usage

```python
import ezdll
lib = ezdll.cstyles.Cdll('./libxxx.so')
raw_data = {'a': [1,], 'b': [2, 3], ...}
results = lib.call_function('api', raw_data)
```
