FILES:=report.pdf

all:
	pdflatex sigproc-sp.tex

pack:
	zip fvx507.zip -r $(FILES)

clean:
	rm -f *.{aux,log,out,toc}

.PHONY: clean
