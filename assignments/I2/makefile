FILES:=src
ROOT:=../..

all:
	pdflatex report.tex

pack:
	cp -r $(ROOT)/src .
	zip fvx507.zip -r $(FILES)

clean:
	rm -f *.{aux,log,out,toc} .*.*.{swp,swo}

.PHONY: clean
