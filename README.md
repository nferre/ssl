# 🔐 Mini ssl

C implementation of md5 and sha256 hash functions.

## How to use

```
make
./ssl {md5/sha256} file1 file2 ...
```
```./ssl {md5/sha256}```  will read from stdin

Exemple :

```
echo -n "ez" | ./ssl md5 hello hey

md5 - (hello)	 81dc9bdb52d04dc20036dbd8313ed055
md5 - (hey)	 23db6982caef9e9152f1a5b2589e6ca3
md5 - (stdin)	 0cbab7e743096d327e14367134b9873a
```




