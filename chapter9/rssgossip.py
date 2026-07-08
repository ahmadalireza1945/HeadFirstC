# Copyright (C) 2011 by D+D Griffiths
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
import urllib.request  # Diperbaiki untuk Python 3
import os
import re
import sys
import unicodedata
import getopt
from xml.dom import minidom

def usage():
    print("Usage:\npython rssgossip.py [-uh] <search-regexp>")

try:
    opts, args = getopt.getopt(sys.argv[1:], "uh", ["urls", "help"])
except getopt.GetoptError as err:  # Diperbaiki sintaksis 'as'
    print(str(err))  # Diperbaiki tanda kurung print
    usage()
    sys.exit(2)

include_urls = False
for o, a in opts:
    if o == "-u":
        include_urls = True
    elif o in ("-h", "--help"):
        usage()
        sys.exit()
    else:
        assert False, "unhandled option"

# Pastikan argumen pencarian diisi
if not args:
    usage()
    sys.exit(2)

searcher = re.compile(args[0], re.IGNORECASE)

# Pastikan variabel lingkungan RSS_FEED ada
if 'RSS_FEED' not in os.environ:
    print("Error: Variabel lingkungan 'RSS_FEED' belum diatur.")
    sys.exit(1)

for url in os.environ['RSS_FEED'].split():  # Diperbaiki menggunakan .split() bawaan string
    try:
        feed = urllib.request.urlopen(url)  # Diperbaiki untuk Python 3
        dom = minidom.parse(feed)
        for node in dom.getElementsByTagName('title'):
            if node.firstChild:
                txt = node.firstChild.wholeText
                if searcher.search(txt):
                    # Normalisasi karakter unicode agar aman dicetak
                    txt = unicodedata.normalize('NFKD', txt).encode('ascii', 'ignore').decode('ascii')
                    print(txt)
                    if include_urls:
                        p = node.parentNode
                        links = p.getElementsByTagName('link')
                        if links and links[0].firstChild:
                            link = links[0].firstChild.wholeText
                            print("\t%s" % link)
    except Exception as e:
        print(f"Gagal memproses URL {url}: {e}")
        sys.exit(1)
