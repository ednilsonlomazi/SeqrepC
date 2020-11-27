from distutils.core import setup, Extension

def main():
    setup(name="seqrepc",
          version="1.0.0",
          description="Python interface for SeqRepC C module",
          author="<Ednilson Lomazi>",
          author_email="ednilsonlmz@gmail.com",
          ext_modules=[Extension("seqrepc", ["./src/seqrepc.c"])])

if __name__ == "__main__":
    main()
