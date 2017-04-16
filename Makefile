default: proof

FLAGS=`pkg-config webkit2gtk-4.0 --cflags --libs`

proof: webkit.cc
	gcc $< $(FLAGS) -o $@

clean:
	-rm -f proof

