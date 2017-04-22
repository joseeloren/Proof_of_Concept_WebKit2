default: proof

FLAGS=`pkg-config webkit2gtk-4.0 javascriptcoregtk-4.0 --cflags --libs`

proof: webkit.cc
	gcc $< $(FLAGS) -g -o $@

clean:
	-rm -f proof

