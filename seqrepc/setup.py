from distutils.core import setup, Extension
 
def main():
    setup(name="seqrepc",
          version="beta1.0",
          description="SeqrepC is a module for fundamental operations related to numerical representations of genomic sequences.",
          author="Ednilson Lomazi",
          author_email="ednilson.lomazi.gt@gmail.com",
          url="https://github.com/ednilsonlomazi/SeqrepC",
          license="BSD 3-Clause License",
          ext_modules=[Extension("seqrepc", ["./src/seqrepc.c"])])

if __name__ == "__main__":
    main()
