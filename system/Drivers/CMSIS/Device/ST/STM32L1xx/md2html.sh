#!/bin/bash

# How to use Pandoc
# To convert your existing HTML release notes into Markdown (useful to build your history), type the following command in your bash window:
  # pandoc --from html --to markdown Release_Notes.html > Release_Notes.md
# To convert a .md file into an HTML one, type the following command in your bash window:
  # pandoc -s -r markdown -t html5 -c "_htmresc/mini-st.css" Release_Notes.md > Release_Notes.html

pandoc -s -r markdown -t html5 -c "_htmresc/mini-st.css" Release_Notes.md > Release_Notes.html

read -n1 -r -p "Press any key to continue..." key
