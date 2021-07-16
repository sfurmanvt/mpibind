#######################################################
# mpibind python bindings
#######################################################

# copy bindings, example, readme, and setup to the install tree
if HAVE_CFFI
data_DATA = mpibind.py mpibind_example.py setup.py README.md 

# create mpibind.py by subbing install location into mpibind.py.in
mpibind.py: mpibind.py.in
	sed 's|\@mpibindlib\@|$(libdir)/libmpibind.so|g' mpibind.py.in > $@

endif

clean-local:
	rm mpibind.py