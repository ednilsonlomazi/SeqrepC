## Description
SeqrepC is a Python module writed in C language for fundamental operations related to numerical representations of genomic sequences.

## Instalation
SeqrepC is not yet available in PyPI, but when it is, it can be installed as follows:
```
pip install seqrepc
```

## Usage
With SeqrepC installed, you can: load genomic sequences from disk, apply some numerical representation into it and store the results on disk.
After that, it is possible load the results from disk. 
I wrote some code examplifying the SeqrepC functionalities: 

```
import seqrepc as sc

# Load (collect) fasta sequences from disk
seqs_data, seqs_info = sc.collect_fasta("/directory/for/file.fasta")

# So, lets supose that your fasta file has 3 sequences and you want encode the # second sequence:
second_seq = ''.join(seqs_data[1]) # seqs_data comes from disk line by line.
seq_encoded = sc.encode("dna_walk", second_seq)

# If you want, you can store and collect this seq_encoded too:
dst_dir = "/directory/for/store/dna_walk.txt"
sc.store((seq_encoded,), (bytes(seqs_info[1], "utf-8"),), "dna_walk", dst_dir))
seqs_data, seqs_info = sc.collect_encodings("dna_walk", dst_dir)
   
```

I know, the storage and collect encodings from disk it is a little bit tricky. If you really think that, you can try installing Seqreppy. 
The module Seqreppy talks to SeqrepC for you, so you don't have to.
Seqreppy uses SeqrepC and promote to you tuns of others functionalities related to numerical representation of genomic sequences. Take a look at Seqreppy repository [here](https://github.com/ednilsonlomazi/seqreppy) 

Currently, SeqrepC has 16 numerical representation methods identified by the signatures below:

* atomic
* cgr
* imaginary
* dna_walk
* liao
* eiip
* binary2b
* binary4b
* integer
* icgr
* molecular_mass
* paired_numeric
* real
* tetrahedron
* voss
* zcurve

if you wanna numerical representations details, you can read [a short summary here](https://github.com/ednilsonlomazi/seqreppy/blob/main/nr_summary.pdf)

## Contributing
If you have some new numerical representation developed by you or that is not present on Seqreppy, please, contribute! If you see some code that can be writed in a more efficient way, great! Let me know! 
If you saw interpretation erros in methods implementation, please, tell me, and i will make the corrections as soon as possible!

## Licences
#### Python

1. This LICENSE AGREEMENT is between the Python Software Foundation ("PSF"), and
   the Individual or Organization ("Licensee") accessing and otherwise using Python
   3.9.1rc1 software in source or binary form and its associated documentation.

2. Subject to the terms and conditions of this License Agreement, PSF hereby
   grants Licensee a nonexclusive, royalty-free, world-wide license to reproduce,
   analyze, test, perform and/or display publicly, prepare derivative works,
   distribute, and otherwise use Python 3.9.1rc1 alone or in any derivative
   version, provided, however, that PSF's License Agreement and PSF's notice of
   copyright, i.e., "Copyright © 2001-2020 Python Software Foundation; All Rights
   Reserved" are retained in Python 3.9.1rc1 alone or in any derivative version
   prepared by Licensee.

3. In the event Licensee prepares a derivative work that is based on or
   incorporates Python 3.9.1rc1 or any part thereof, and wants to make the
   derivative work available to others as provided herein, then Licensee hereby
   agrees to include in any such work a brief summary of the changes made to Python
   3.9.1rc1.

4. PSF is making Python 3.9.1rc1 available to Licensee on an "AS IS" basis.
   PSF MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.  BY WAY OF
   EXAMPLE, BUT NOT LIMITATION, PSF MAKES NO AND DISCLAIMS ANY REPRESENTATION OR
   WARRANTY OF MERCHANTABILITY OR FITNESS FOR ANY PARTICULAR PURPOSE OR THAT THE
   USE OF PYTHON 3.9.1rc1 WILL NOT INFRINGE ANY THIRD PARTY RIGHTS.

5. PSF SHALL NOT BE LIABLE TO LICENSEE OR ANY OTHER USERS OF PYTHON 3.9.1rc1
   FOR ANY INCIDENTAL, SPECIAL, OR CONSEQUENTIAL DAMAGES OR LOSS AS A RESULT OF
   MODIFYING, DISTRIBUTING, OR OTHERWISE USING PYTHON 3.9.1rc1, OR ANY DERIVATIVE
   THEREOF, EVEN IF ADVISED OF THE POSSIBILITY THEREOF.

6. This License Agreement will automatically terminate upon a material breach of
   its terms and conditions.

7. Nothing in this License Agreement shall be deemed to create any relationship
   of agency, partnership, or joint venture between PSF and Licensee.  This License
   Agreement does not grant permission to use PSF trademarks or trade name in a
   trademark sense to endorse or promote products or services of Licensee, or any
   third party.

8. By copying, installing or otherwise using Python 3.9.1rc1, Licensee agrees
   to be bound by the terms and conditions of this License Agreement.


#### Python/C API

1. This LICENSE AGREEMENT is between the Python Software Foundation ("PSF"), and
   the Individual or Organization ("Licensee") accessing and otherwise using Python
   3.9.1rc1 software in source or binary form and its associated documentation.

2. Subject to the terms and conditions of this License Agreement, PSF hereby
   grants Licensee a nonexclusive, royalty-free, world-wide license to reproduce,
   analyze, test, perform and/or display publicly, prepare derivative works,
   distribute, and otherwise use Python 3.9.1rc1 alone or in any derivative
   version, provided, however, that PSF's License Agreement and PSF's notice of
   copyright, i.e., "Copyright © 2001-2020 Python Software Foundation; All Rights
   Reserved" are retained in Python 3.9.1rc1 alone or in any derivative version
   prepared by Licensee.

3. In the event Licensee prepares a derivative work that is based on or
   incorporates Python 3.9.1rc1 or any part thereof, and wants to make the
   derivative work available to others as provided herein, then Licensee hereby
   agrees to include in any such work a brief summary of the changes made to Python
   3.9.1rc1.

4. PSF is making Python 3.9.1rc1 available to Licensee on an "AS IS" basis.
   PSF MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.  BY WAY OF
   EXAMPLE, BUT NOT LIMITATION, PSF MAKES NO AND DISCLAIMS ANY REPRESENTATION OR
   WARRANTY OF MERCHANTABILITY OR FITNESS FOR ANY PARTICULAR PURPOSE OR THAT THE
   USE OF PYTHON 3.9.1rc1 WILL NOT INFRINGE ANY THIRD PARTY RIGHTS.

5. PSF SHALL NOT BE LIABLE TO LICENSEE OR ANY OTHER USERS OF PYTHON 3.9.1rc1
   FOR ANY INCIDENTAL, SPECIAL, OR CONSEQUENTIAL DAMAGES OR LOSS AS A RESULT OF
   MODIFYING, DISTRIBUTING, OR OTHERWISE USING PYTHON 3.9.1rc1, OR ANY DERIVATIVE
   THEREOF, EVEN IF ADVISED OF THE POSSIBILITY THEREOF.

6. This License Agreement will automatically terminate upon a material breach of
   its terms and conditions.

7. Nothing in this License Agreement shall be deemed to create any relationship
   of agency, partnership, or joint venture between PSF and Licensee.  This License
   Agreement does not grant permission to use PSF trademarks or trade name in a
   trademark sense to endorse or promote products or services of Licensee, or any
   third party.

8. By copying, installing or otherwise using Python 3.9.1rc1, Licensee agrees
   to be bound by the terms and conditions of this License Agreement.
